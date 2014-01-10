/* sysMpc85xxI2c.c - I2C Driver Source Module */

/* Copyright (c) 2005-2006 Wind River Systems, Inc. */

/*
modification history
--------------------
01c,27jan06,dtr  Fix EepromShow and tidyup.
01b,04apr05,mdo  Documentation fixes for apigen
01a,28feb05,dtr  created.
*/

/*
DESCRIPTION

I2C Driver Source (Low Level Routines) Module
Mpc85xx Memory Controller (PowerPlus Architecture)

Notes:
   1. GREAT care must be made when sending commands to the 
      MPC85XX(Mpc85xx).  Several "i2cCycleMpc85xxDelay" calls are made
      in order to not overwhelm the I2C interface.  If commands
      are sent too fast, the I2C interface will lockup and the I2C
      bus may become unusable without a powercycle.  Generally, if
      you cause a I2C bus cycle, you should wait for "a while".
      A possible cause is that the caches were turned on when this
      driver was written.

INCLUDE FILES:   sysMpc85xxI2c.h
*/

/* includes */

#include <vxWorks.h>        /* vxWorks generics */
#include "config.h"
#include "sysMotI2c.h"
#include "sysMpc85xxI2c.h"  /* low level definitions, specific */
#include <stdio.h>
#include <string.h>
#include <logLib.h>
#include <stdlib.h>
#include <taskLib.h>
#include <arch/ppc/vxPpcLib.h>

/* externals */

IMPORT I2C_DRV_CTRL * pI2cDrvCtrl[2] ;
IMPORT void sysMsDelay(UINT);

/* forward declarations */

void sysMpc85xxMsDelay (UINT mSeconds);
void i2cCycleMpc85xxDelay (int mSeconds);
void i2cInit();

/* debug declarations */

#define SPD_SIZE        256
#define REAL_SPD_SIZE   256
char defaultSPD[SPD_SIZE];


/* Global flag */

int I2CDoRepeatStart = 0;   /* indicates if a "Repeat Start" is requested */


/******************************************************************************
* 
* i2cCycleMpc85xxStart - perform I2C "start" cycle
* 
* This function's purpose is to perform an I2C start cycle.
* 
* RETURNS:
*   zero        = operation successful
*   non-zero    = operation failed
*
* ERRNO: N/A
*/
int i2cCycleMpc85xxStart 
    (
    int unit
    ) 
    {
    unsigned int timeOutCount;
    UINT8 statusReg = 0;


    if (pI2cDrvCtrl[unit] == NULL)
        return -1 ;

    /* 
     * if this is a repeat start, then set the required bits and return.
     *
     * NOTE:
     * this driver ONLY supports one repeat start between the start
     * stop and cycles.
     */

    if ( I2CDoRepeatStart == 1 )
        {
        i2cIoctl(I2C_IOCTL_RMW_OR, 
                    (UINT32)(pI2cDrvCtrl[unit]->baseAdrs+MPC85XX_I2C_CONTROL_REG), 
                    (MPC85XX_I2C_CONTROL_REG_RSTA |
                     MPC85XX_I2C_CONTROL_REG_MSTA |
                     MPC85XX_I2C_CONTROL_REG_MTX),0);
        I2CDoRepeatStart = 0;  /* one repeat start only, so clear this bit */
        return(0);
        }

    /* 
     * wait until the I2C bus is free.  if it doesn't become free
     * within a *reasonable* amount of time, exit with an error.
     */

    for ( timeOutCount = 100; timeOutCount; timeOutCount-- )
        {
        statusReg = i2cIoctl(I2C_IOCTL_RD, 
                            (UINT32)(pI2cDrvCtrl[unit]->baseAdrs+MPC85XX_I2C_STATUS_REG), 0, 0);

        if ( !(statusReg & MPC85XX_I2C_STATUS_REG_MBB) )
            {
            break;
            }
	sysMpc85xxMsDelay(1);

        }

    if ( !timeOutCount )
        {
        return(-1); 
        }

    /*
     * since this is the first time through, generate a START(MSTA) and
     * place the I2C interface into a master transmitter mode(MTX).
     */

    i2cIoctl(I2C_IOCTL_RMW_OR, 
            (UINT32)(pI2cDrvCtrl[unit]->baseAdrs+MPC85XX_I2C_CONTROL_REG), 
            (MPC85XX_I2C_CONTROL_REG_MTX |
             MPC85XX_I2C_CONTROL_REG_MSTA),0);

    /* 
     * The first time through, set "I2CDoRepeatStart".  If this function
     * is called again BEFORE a STOP is sent, then we are doing a 
     * "dummy write", which sets the devices internal byte pointer 
     * to the byte we intend to read.
     */

    I2CDoRepeatStart = 1;

    return(0);

    }


/******************************************************************************
* 
* i2cCycleMpc85xxStop - perform I2C "stop" cycle
* 
* This function's purpose is to perform an I2C stop cycle.
* 
* RETURNS:
*   zero        = operation successful
*   non-zero    = operation failed
*
* ERRNO: N/A
*/
int i2cCycleMpc85xxStop 
    (
    int unit
    )
    {

    if (pI2cDrvCtrl[unit] == NULL)
        return -1 ;

    /*
     * turn off MSTA bit(which will generate a STOP bus cycle)
     * turn off MTX bit(which places the MPC85XX interface into receive mode
     * turn off TXAK bit(which allows 9th clock cycle acknowledges)
     */
    sysMpc85xxMsDelay(1);

    i2cIoctl(I2C_IOCTL_RMW_AND, 
            (UINT32)(pI2cDrvCtrl[unit]->baseAdrs+MPC85XX_I2C_CONTROL_REG), 
            ((UINT8)~(MPC85XX_I2C_CONTROL_REG_MTX  |
               MPC85XX_I2C_CONTROL_REG_MSTA |
               MPC85XX_I2C_CONTROL_REG_TXAK)), 0);

    /* 
     * Clear the global I2C "Repeat Start" flag.
     */

    I2CDoRepeatStart = 0;

    return(0);

    }


/******************************************************************************
* 
* i2cCycleMpc85xxRead - perform I2C "read" cycle
* 
* This function's purpose is to perform an I2C read cycle.
* 
* RETURNS:
*   zero        = operation successful
*   non-zero    = operation failed
*
* ERRNO: N/A
*/
int i2cCycleMpc85xxRead
    (
    int unit,
    unsigned char *pReadDataBuf,    /* pointer to read data buffer */
    int ack    /* 0 = don't ack, 1 = ack */
    )
    {
    unsigned int readData = 0;

    if (pI2cDrvCtrl[unit] == NULL)
        return -1 ;
    
    /*
     * place the I2C interface into receive mode(MTX=0) and set the interface
     * to NOT acknowledge(TXAK=1) the incoming data on the 9th clock cycle.
     * this is required when doing random reads of a I2C device.
     */

    if (!ack)
        {
        /* Don't send master ack. */
        i2cIoctl(I2C_IOCTL_RMW_AND_OR, 
            (UINT32)(pI2cDrvCtrl[unit]->baseAdrs+MPC85XX_I2C_CONTROL_REG),
            ((UINT8)~MPC85XX_I2C_CONTROL_REG_MTX),
              MPC85XX_I2C_CONTROL_REG_TXAK);
        }
    else
        {
        /* Send master ack. */
        i2cIoctl(I2C_IOCTL_RMW_AND_OR, 
            (UINT32)(pI2cDrvCtrl[unit]->baseAdrs+MPC85XX_I2C_CONTROL_REG),
            ((UINT8)~(MPC85XX_I2C_CONTROL_REG_MTX|MPC85XX_I2C_CONTROL_REG_TXAK)),
              0);
        }

    sysMpc85xxMsDelay(1);

    /* do a "dummy read".  this latches the data off the bus. */

    i2cIoctl(I2C_IOCTL_RD, 
            (UINT32)(pI2cDrvCtrl[unit]->baseAdrs+MPC85XX_I2C_DATA_REG), 
            0, 0);

    /* now do the actual read, make this one count */
    sysMpc85xxMsDelay(1);

    readData = i2cIoctl(I2C_IOCTL_RD, 
                       (UINT32)(pI2cDrvCtrl[unit]->baseAdrs+MPC85XX_I2C_DATA_REG), 
                       0, 0);

    *pReadDataBuf = (unsigned char)readData;

    return(0);

    }


/******************************************************************************
* 
* i2cCycleMpc85xxWrite - perform I2C "write" cycle
* 
* This function's purpose is to perform an I2C write cycle.
* 
* RETURNS:
*   zero        = operation successful
*   non-zero    = operation failed
*
* ERRNO: N/A
*/
int i2cCycleMpc85xxWrite
    (
    int             unit,
    unsigned char   writeData   /* character to write */
    )
    {
    if (pI2cDrvCtrl[unit] == NULL)
        return -1 ;

    /*
     * write the requested data to the data register, which will cause
     * it to be transmitted on the I2C bus.
     */

    i2cIoctl(I2C_IOCTL_WR, 
            (UINT32)(pI2cDrvCtrl[unit]->baseAdrs+MPC85XX_I2C_DATA_REG), 
            (UINT32)writeData, 0);

    return(0);
    }


/******************************************************************************
* 
* i2cCycleMpc85xxAckIn - perform I2C "acknowledge-in" cycle
* 
* This function's purpose is to perform an I2C acknowledge-in cycle.
* 
* RETURNS:
*   zero        = operation successful
*   non-zero    = operation failed
*
* ERRNO: N/A
*/
int i2cCycleMpc85xxAckIn 
    (
    int unit
    )
    {
    unsigned int statusReg = 0;
    unsigned int timeOutCount;

    if (pI2cDrvCtrl[unit] == NULL)
        return -1 ;

    /*
     * wait until an *internal* device interrupt has been generated, then
     * clear it.  if it is not received, return with an error.
     * we are polling, so NO processor interrupt is generated.
     */

    for ( timeOutCount = 10000; timeOutCount; timeOutCount-- )
        {
        statusReg = i2cIoctl(I2C_IOCTL_RD, 
                            (UINT32)(pI2cDrvCtrl[unit]->baseAdrs+MPC85XX_I2C_STATUS_REG), 0, 0);

        if ( statusReg & MPC85XX_I2C_STATUS_REG_MIF )
            {
            i2cIoctl(I2C_IOCTL_RMW_AND, 
                    (UINT32)(pI2cDrvCtrl[unit]->baseAdrs+MPC85XX_I2C_STATUS_REG), 
                    ((UINT8)~MPC85XX_I2C_STATUS_REG_MIF), 0);
            break;
            }
        }

    if ( !timeOutCount )
        {
        return(-1);
        }

    return(0);

    }


/******************************************************************************
* 
* i2cCycleMpc85xxAckOut - perform I2C "acknowledge-out" cycle
* 
* This function's purpose is to perform an I2C acknowledge-out cycle.
* 
* RETURNS:
*   zero        = operation successful
*   non-zero    = operation failed
*
* ERRNO: N/A
*/
int i2cCycleMpc85xxAckOut 
    (
    int unit
    )
    {
    if (pI2cDrvCtrl[unit] == NULL)
        return -1 ;

    return(0);
    }


/******************************************************************************
* 
* i2cCycleMpc85xxKnownState - initialize the I2C bus to a known state
* 
* This function's purpose is to initialize the I2C bus to a known state.
* 
* RETURNS:
*   zero        = operation successful
*   non-zero    = operation failed
*
* ERRNO: N/A
*/

int i2cCycleMpc85xxKnownState 
    (
    int unit
    )
    {
    STATUS status;
    UINT   timeOutCount;
    UINT   statusReg;

    status = OK;


    if (pI2cDrvCtrl[unit] == NULL)
        return ERROR ;
    
    /*
     * wait until the I2C bus is free.  if it doesn't become free
     * within a *reasonable* amount of time, exit with an error.
     */

    for ( timeOutCount = 1000; timeOutCount; timeOutCount-- )
        {
        statusReg = i2cIoctl(I2C_IOCTL_RD, 
                            (UINT32)(pI2cDrvCtrl[unit]->baseAdrs+MPC85XX_I2C_STATUS_REG), 0, 0);

        if ( !(statusReg & MPC85XX_I2C_STATUS_REG_MBB) )
            {
            status = OK;
            break;
            }

        /* 
         * re-initialize the I2C if the BUS BUSY does not clear
         * after trying half the *reasonable* amount of reads of the 
         * status register.
         */

        if ( !(timeOutCount % 50) )
            {
            status = i2cDrvInit(unit, I2C_DRV_TYPE);
            if ( status == OK )
                break;
            else
                return ERROR ;
            }
        }

    if ( !timeOutCount )
        status = ERROR;

    return(status);
    }


/******************************************************************************
* 
* i2cCycleMpc85xxDelay - perform interface's I2C delay routine 
* 
* This function's purpose is to perform whatever delay required for the device.
* 
* RETURNS:  N/A
*
* ERRNO: N/A
*/
void i2cCycleMpc85xxDelay
    (
    int mSeconds    /* time to delay in milliseconds */
    )
    {

    sysMpc85xxMsDelay(mSeconds);

    }


/******************************************************************************
*
* sysMpc85xxMsDelay - delay for the specified amount of time (MS)
*
* This routine will delay for the specified amount of time by counting
* decrementer ticks.
*
* This routine is not dependent on a particular rollover value for
* the decrementer, it should work no matter what the rollover
* value is.
*
* A small amount of count may be lost at the rollover point resulting in
* the sysMpc85xxMsDelay() causing a slightly longer delay than requested.
*
* This routine will produce incorrect results if the delay time requested
* requires a count larger than 0xffffffff to hold the decrementer
* elapsed tick count.  For a System Bus Speed of 67 MHz this amounts to
* about 258 seconds.
*
* RETURNS: N/A
*
* ERRNO: N/A
*/
void sysMpc85xxMsDelay
    (
    UINT        delay            /* length of time in MS to delay */
    )
    {
    sysMsDelay(delay);
    }



/** DEBUG FUNCTIONS **/



/******************************************************************************
*
* i2cProgramSPD - Demonstration function to program an SPD EEPROM
*
* This routine programs an SPD EEPROM with the contents of
* defaultSPD.  This program is enabled by defining DEBUG_I2C.
*
* RETURNS: OK/ERROR
*
* ERRNO: N/A
*/

int i2cProgramEeprom
    (
    int unit,
    int deviceAddress   /* address of I2C device - 0xa0, 0xa2 */
    )
    {
    int index = 0;
    char verifyData[REAL_SPD_SIZE];

    for ( index=0;index<REAL_SPD_SIZE;index++ )
        defaultSPD[index] = index ;

    i2cWrite (unit, 
              deviceAddress, 
              I2C_DEVICE_TYPE_EEPROM_AT24C256, 
              0, 
              REAL_SPD_SIZE, 
              defaultSPD);

    if ( i2cRead (unit, 
                  deviceAddress, 
                  I2C_DEVICE_TYPE_EEPROM_AT24C256, 
                  0, 
                  REAL_SPD_SIZE, 
                  verifyData) == OK )
        {
        for ( index=0;index<REAL_SPD_SIZE;index++ )
            {
            if ( verifyData[index] != defaultSPD[index] )
                {
                logMsg("SPD programming Failed: %d: %x != %x\r\n", 
                       index, verifyData[index], defaultSPD[index],0,0,0);
                return(ERROR);
                }
            }
        }
    return(OK);
    }


/******************************************************************************
*
* i2cShowEeprom - Dump i2c device
*
* This routine prints the number "size" bytes of EEPROM addresses at
* "deviceAddress".  Valid addresses for the prpmc600 are 0xa0 
* for SPD SDRAM banks and VPD_BRD_EEPROM_ADRS for the board's VPD
* EEPROM. 
*
* RETURNS: OK/ERROR
*
* ERRNO: N/A
*/

int i2cShowEeprom
    (
    int unit,
    int deviceAddress,  /* address of I2C device - 0xa0, 0xa2 */
    int size        /* number of bytes to read/display */
    )
    {
    int i;
    char i2cBuff[REAL_SPD_SIZE] = {0};

    if ( size > REAL_SPD_SIZE )
        return(ERROR);

    memset(i2cBuff,0,REAL_SPD_SIZE);

    if ( i2cRead (unit, 
                  deviceAddress, 
                  I2C_DEVICE_TYPE_EEPROM_AT24C256, 
                  0, 
                  size, 
                  i2cBuff) == ERROR )
        {
        logMsg("%d : Driver returned error\n",__LINE__,0,0,0,0,0);
        return(ERROR);
        }

    for ( i=0;i<size;i++ )
        printf("%x ", i2cBuff[i]);

    printf("\r\n");

    return(0);
    }


/******************************************************************************
*
* i2cFill - block fill a i2c device
*
* This routine writes the number "size" bytes of EEPROM addresses at
* "deviceAddress" with the value "value".  Valid addresses for the prpmc600
* are 0xa0 for SPD SDRAM banks and VPD_BRD_EEPROM_ADRS for the board's VPD 
* EEPROM.  This will wipe out the existing data at the address. 
*
* RETURNS: OK/ERROR
*
* ERRNO: N/A
*/

int i2cFillEeprom
    (
    int unit,
    int deviceAddress,  /* address of I2C device - 0xa0, 0xa2 */
    int size,       /* number of bytes to write */
    int value       /* value to fill */
    )
    {
    int ii;
    char ptr[1];

    if ( size > REAL_SPD_SIZE )
        return(ERROR);

    for ( ii=0;ii<size;ii++ )
        {
        ptr[0] = value;
        i2cWrite (unit, 
                  deviceAddress, 
                  I2C_DEVICE_TYPE_EEPROM_AT24C256, 
                  ii, 
                  1, 
                  ptr);
        }

    i2cShowEeprom (unit, deviceAddress, size);

    return(OK);
    }


#define I2C_TSENSOR_SEEKER_ADRS 0
/******************************************************************************
*
* i2cShowTemp - read temperature sensor
*
* This routine reads the temperature sensor on the I2C bus.
*
* RETURNS: ERROR; or 0
*
* ERRNO: N/A
*/

int i2cShowTemp
    (
    int unit,
    int deviceAddress   /* address of I2C device - 0xa0, 0xa2 */
    )
    {
    int i;
    char i2cBuff[REAL_SPD_SIZE] = {0};

    if ( deviceAddress != I2C_TSENSOR_SEEKER_ADRS )
        {
        printf("Bad I2C address 0x%x\n", deviceAddress);
        return -1 ;
        }

    memset(i2cBuff,0,REAL_SPD_SIZE);

    i2cBuff[0] = 0 ;

    i2cWrite (unit, 
              deviceAddress, 
              I2C_DEVICE_TYPE_TEMP_SENSOR_AD7417, 
              1, 
              1, 
              i2cBuff) ;

    taskDelay(1);

    if ( i2cRead (unit, 
                  deviceAddress, 
                  I2C_DEVICE_TYPE_TEMP_SENSOR_AD7417, 
                  0, 
                  2, 
                  i2cBuff) == ERROR )
        {
        logMsg("%d : Driver returned error\n",__LINE__,0,0,0,0,0);
        return(ERROR);
        }

    for ( i=0;i<2;i++ )
        printf("%x ", i2cBuff[i]);

    printf("\r\n");

    return(0);
    }


/******************************************************************************
*
* i2cShowAdc - read the ADC
*
* This routine reads the ADC sensor on the I2C bus.
*
* RETURNS: ERROR; or 0
*
* ERRNO: N/A
*/

int i2cShowAdc
    (
    int unit,
    int deviceAddress   /* address of I2C device - 0x28 */
    )
    {
    int i;
    char i2cBuff[REAL_SPD_SIZE] = {0};

    if ( deviceAddress != I2C_TSENSOR_SEEKER_ADRS )
        {
        printf("Bad I2C address 0x%x\n", deviceAddress);
        return -1 ;
        }

    memset(i2cBuff,0,REAL_SPD_SIZE);

    i2cBuff[0] = 0x60 ;
    i2cWrite (unit, 
              deviceAddress, 
              I2C_DEVICE_TYPE_TEMP_SENSOR_AD7417, 
              1, 
              1, 
              i2cBuff) ;
    i2cRead (unit, 
             deviceAddress, 
             I2C_DEVICE_TYPE_TEMP_SENSOR_AD7417, 
             1, 
             1, 
             i2cBuff) ;

    taskDelay(1);

    if ( i2cRead (unit, 
                  deviceAddress, 
                  I2C_DEVICE_TYPE_TEMP_SENSOR_AD7417, 
                  4, 
                  2, 
                  i2cBuff) == ERROR )
        {
        logMsg("%d : Driver returned error\n",__LINE__,0,0,0,0,0);
        return(ERROR);
        }


    for ( i=0;i<2;i++ )
        printf("%x ", i2cBuff[i]);

    printf("\r\n");

    i2cBuff[0] = 0x80 ;
    i2cWrite (unit, 
              deviceAddress, 
              I2C_DEVICE_TYPE_TEMP_SENSOR_AD7417, 
              1, 
              1, 
              i2cBuff) ;
    i2cRead (unit, 
             deviceAddress, 
             I2C_DEVICE_TYPE_TEMP_SENSOR_AD7417, 
             1, 
             1, 
             i2cBuff) ;

    taskDelay(1);

    if ( i2cRead (unit, 
                  deviceAddress, 
                  I2C_DEVICE_TYPE_TEMP_SENSOR_AD7417, 
                  4, 
                  2, 
                  i2cBuff) == ERROR )
        {
        logMsg("%d : Driver returned error\n",__LINE__,0,0,0,0,0);
        return(ERROR);
        }


    for ( i=0;i<2;i++ )
        printf("%x ", i2cBuff[i]);

    printf("\r\n");

    return(0);
    }


/******************************************************************************
*
* i2cTempRegRead - read the temperature sensor register
*
* This routine reads the temperature sensor register on the I2C.
*
* RETURNS: OK, or ERROR
*
* ERRNO: N/A
*/

int i2cTempRegRead
    (
    int unit,
    int deviceAddress,
    int reg,
    int size,
    UINT16 *data
    )
    {
    if ( i2cRead (unit,  
                  deviceAddress, 
                  I2C_DEVICE_TYPE_TEMP_SENSOR_AD7417, 
                  reg, 
                  size, 
                 (char*)data) == ERROR )
        {
        logMsg("%d : Driver returned error\n",__LINE__,0,0,0,0,0);
        return(ERROR);
        }
    if ( size == 1 )
        *data = *data>>8 ;

    return(OK);
    }


/******************************************************************************
*
* i2cTempRegWrite - write the temperature sensor register
*
* This routine writes the temperature sensor register on the I2C.
*
* RETURNS: OK, or ERROR
*
* ERRNO: N/A
*/

int i2cTempRegWrite
    (
    int unit,
    int deviceAddress,
    int reg,
    int size,
    UINT16 *data
    )
    {
    if ( size == 1 )
        *data <<= 8 ;

    if ( i2cWrite (unit, deviceAddress, 
                   I2C_DEVICE_TYPE_TEMP_SENSOR_AD7417, 
                   reg, 
                   size, 
                  (char*)data) == ERROR )
        {
        logMsg("%d : Driver returned error\n",__LINE__,0,0,0,0,0);
        return(ERROR);
        }

    return(OK);
    }


/******************************************************************************
*
* i2cIOPortRegWrite - write the IO Port register
*
* This routine writes the IO Port register on the I2C.
*
* RETURNS: OK, or ERROR
*
* ERRNO: N/A
*
* NOTES:
* Reg 0..7 
* Actual read and writes require accessing a pair of registers.
* command byte 0 : input port 0,1 
* command byte 2 : output port 0,1 
* command byte 4 : polarity inversion 0,1
* command byte 6 : config port 0,1 
* config port 0 = output, 1 = input, powerup all 1 
* so if config port 1.4 = 0 then output port 1.4 is applicable 
*/

int i2cIOPortRegWrite 
    (
    int unit,
    int deviceAddress,
    int reg,
    UINT32  data
    )
    {

    /* write register pair */
    if ( i2cWrite (unit, 
                   deviceAddress, 
                   I2C_DEVICE_TYPE_IOPORT_PCA9555,
                   reg, 
                   4, 
                   (char*)&data) == ERROR )
        {
        logMsg("%d : Driver returned error\n",__LINE__,0,0,0,0,0);
        return(ERROR);
        }


    return OK ;

    }



/******************************************************************************
*
* i2cIOPortRegRead - read the IO Port register
*
* This routine reads the IO Port register on the I2C.
*
* RETURNS: OK, or ERROR
*
* ERRNO: N/A
*/

int i2cIOPortRegRead
    (
    int unit,
    int deviceAddress,
    int reg,
    UINT32  *data
    )
    {

    /* read register pair */

    if ( i2cRead (unit,  
                  deviceAddress, 
                  I2C_DEVICE_TYPE_IOPORT_PCA9555,
                  reg, 
                  4,  /* 1 bytes */
                 (char*)data) == ERROR )
        {
        logMsg("%d : Driver returned error\n",__LINE__,0,0,0,0,0);
        return(ERROR);
        }

    return OK ;
    }

#ifdef DEBUG_I2C
void i2cInit (void)
    {
    int reg,addr;
    UINT32  data = 0xff  ;

    i2cDrvInit(0,0);

    for (addr=0x18;addr<0x20;addr++)
	{
	reg = 0;
	i2cIOPortRegRead(0, addr, reg, &data);
	data =0xff;
	}

    /* For configuration use port 1 */
    addr = 0x51;
    i2cShowEeprom(0,addr,256);
    addr = 0x50;
    i2cShowEeprom(0,addr,256);

    }
    
#endif


