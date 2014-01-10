/* sysMotTsecEnd.c - system configuration module for motTsecEnd driver */

/* Copyright (c) 2003-2004 Wind River Systems, Inc. */

/*
modification history
--------------------
01a,03may06,dtr  SPR#120513 - check enet address.
01a 16feb06,dtr  created from cds85xx/sysMotTsecEnd.c/01j
*/

/*
DESCRIPTION
This is the WRS-supplied configuration module for the VxWorks
motTsecEnd END driver.

*/

#include "vxWorks.h"
#include "config.h"
#include "vmLib.h"
#include "stdio.h"
#include "sysLib.h"
#include "logLib.h"
#include "stdlib.h"
#include "string.h"
#include "end.h"
#include "cacheLib.h"
#include "intLib.h"
#include "lstLib.h"
#include "miiLib.h"
#include "drv/end/motTsecEnd.h"

/* defines */
#define MOT_TSEC_PHY_ADDRS_DEV_1    0
#define MOT_TSEC_PHY_ADDRS_DEV_2    1

/* PHY's default operating mode */
#define MOT_TSEC_DEF_PHY_MODE      MII_PHY_TBL /* use auto-negotiation table */

/* imports */

IMPORT END_OBJ * motTsecEndLoad (char *);
IMPORT STATUS    sysL2ExtWriteBufferAlloc(char *adrs,UINT size,BOOL lock);

/* globals */

/* locals */

/* forward declarations */

LOCAL STATUS sysMiiPhyInit(PHY_INFO *);
LOCAL STATUS sysMiiPhyStatusGet (PHY_INFO *,MOT_TSEC_PHY_STATUS *);
extern STATUS sysMotTsecEnetAddrGet (int, UCHAR *);
LOCAL STATUS sysMotTsecEnetEnable (UINT32, UINT32);
LOCAL STATUS sysMotTsecEnetDisable (UINT32, UINT32);

/*
 * this table may be customized by the user to force a
 * particular order how different technology abilities may be
 * negotiated by the PHY. Entries in this table may be freely combined
 * and even OR'd together.
 */

UINT32 sysMotTsecNumByUnit[MOT_TSEC_MAX_DEVS] = {MOT_TSEC_DEV_1, MOT_TSEC_DEV_2};

LOCAL INT16 sysMotTsecAnOrderTbl [] =
    {
    MII_TECH_100BASE_TX,    /* 100Base-T */
    MII_TECH_100BASE_T4,    /* 10Base-T */
    MII_TECH_10BASE_T,      /* 100Base-T4 */
    MII_TECH_10BASE_FD,     /* 100Base-T FD*/
    MII_TECH_100BASE_TX_FD, /* 10Base-T FD */
    -1                      /* end of table */
    };

/* PhyParms table indexed by unit number */
LOCAL MOT_TSEC_PHY_PARAMS sysMotTsecPhyParms[MOT_TSEC_MAX_DEVS] =
    {
        {
        MOT_TSEC_PHY_ADDRS_DEV_1,
        MOT_TSEC_DEF_PHY_MODE,
        MII_PHY_DEF_DELAY,
        1,
        (MII_AN_ORDER_TBL *) sysMotTsecAnOrderTbl,
        },
        {
        MOT_TSEC_PHY_ADDRS_DEV_2,
        MOT_TSEC_DEF_PHY_MODE,
        MII_PHY_DEF_DELAY,
        1,
        (MII_AN_ORDER_TBL *) sysMotTsecAnOrderTbl
        }
    };

LOCAL MOT_TSEC_FUNC_TABLE sysMotTsecFuncs =
    {
    sysMiiPhyInit,      /* bsp MiiPhy init function */
    NULL,               /* Interrupt End Driver function called by BSP */
    sysMiiPhyStatusGet, /* status call back */
    NULL,               /* BSP BYTE Read function called by BSP */
    NULL,               /* BSP BYTE Write function called by BSP */
    sysMotTsecEnetAddrGet,    /* Driver call back to get the Ethernet address */
    NULL,    /* Driver call back to set the Ethernet address */
    sysMotTsecEnetEnable,     /* Driver call back to enable the ENET interface */
    sysMotTsecEnetDisable,     /* Driver call back to disable the ENET interface */
    NULL
    };

LOCAL MOT_TSEC_PARAMS sysMotTsecParms =
    {
    NULL,  /* Buffer pointer for allocated buffer space */
    0,     /* Buffer pool size */
    NULL,  /* Descriptor Base Address */
    0,     /* Descriptor Size */
    32,    /* Number of Receive Buffer Descriptors  */
    32    /* Number of Transmit Buffer Descriptors */
    };

#if 0
/* TSEC hardware defaults */
LOCAL MOT_TSEC_EXT_PARAMS sysMotTsecExtParms =
    {
    0, /* TSEC specific user bit flags */
    0, /* TSEC specific user reg flags */
    0, /* Ethernet Minimum Frame Length */
    0, /* Ethernet Maximum Frame Length */

       /* TSEC Specific Device Parameters */
    0, /* ext + pause time value */
    0, /* Ten Bit Interface physical address */

        /* Tx FIFO Manipulation */
    0,  /* UINT32 fifoTxTheshold; */
    0,  /* UINT32 fifoTxStarve; */
    0,  /* UINT32 fifoTxStarveShutOff; */

        /* MAC specific Parameters */
    {0,0,0,0,0,0,0,0}, /* initial individual addresses [8] */
    {0,0,0,0,0,0,0,0}, /* initial group addresses [8] */

    0,  /* UINT32 macPreambleLength; */
    0,  /* UINT32 macIfMode; */

    0,  /* UINT32 macIpgifgNbbipg1; */
    0,  /* UINT32 macIpgifgNbbipg2; */
    0,  /* UINT32 macIpgifgMifge; */
    0,  /* UINT32 macIpgifgBbipg; */

        /* MAC half duplex specific parameters */
    0,  /* UINT32 macHalfDuplexAltBebTruncation; */
    0,  /* UINT32 macHalfDuplexRetryMaximum; */
    0,  /* UINT32 macHalfDuplexCollisionWindow; */
    0,  /* UINT32 miiMgmtClockSelect; */
    0,  /* UINT32 phyAddress; */

        /* Misc */
    0,  /* UINT32 extL2Cache; */
    0,  /* UINT32 bdL2Cache;  */
    0,  /* UINT32 dmaExtLength; */
    0   /* UINT32 dmaExtIndex; */
    };
#endif
/***********************************************************************
*
* sysMotTsecEndLoad - load an instance of the motTsecEnd driver
*
* This routine loads the motTsecEnd driver with proper parameters. It also
*
* The END device load string formed by this routine is in the following
* format.
* <unit>:<tsecAddrs>:<tsecNum>:<MAC Address>:<MOT_TSEC_FUNC_TABLE>:
* <MOT_TSEC_PARAMS>:<MOT_TSEC_EXT_PARAMS>
*
* .IP <unit>
* The unit number passed by the Mux.
* .IP <CCSBAR>
* The MPC85xx Internal memory base address. eg.0xfe000000
* .IP <tsecNum>
* This Tsec's physical port, 0 or 1. Not the same as the unit number.
* .IP <MAC ADDRESS>
* This TSEC's MAC address eg. 00-0a-1e-12-34-56
* .IP <usrFlags>
* User Init Flags
* .IP <MOT_TSEC_PHY_PARAMS>
* PHY Init parameters
* .IP <MOT_TSEC_FUNC_TABLE>
* Structure Address of external and driver functions
* .IP <MOT_TSEC_PARAMS>
* Structure Address of Buffer Allocation Parameters
* .IP <MOT_TSEC_EXT_PARAMS>
* Structure Address of TSEC specific parameters
*
* This routine only loads and initializes one instance of the device.
* If the user wishes to use more than one motTsecEnd devices, this routine
* should be changed.
*
* RETURNS: pointer to END object or NULL.
*
* SEE ALSO: motTsecEndLoad ()
*/

END_OBJ * sysMotTsecEndLoad
    (
    char * pParamStr,   /* ptr to initialization parameter string */
    void * unused       /* unused optional argument */
    )
    {
    END_OBJ * pEnd;
    char   paramStr [300];
    UINT32 unit, usrFlags;
    char *  tok;             /* an initString token */
    char *  holder = NULL;   /* points to initString fragment beyond tok */
    char  enet[MAC_ADRS_LEN+2];

    /*
    * <CCSBAR>:
    * <tsecNum>:
    * <MAC Address>:
    * <UsrFlags>:
    * <MOT_TSEC_PHY_PARAMS>:
    * <MOT_TSEC_FUNC_TABLE>:
    * <MOT_TSEC_PARAMS>:
    * <MOT_TSEC_EXT_PARAMS>
    * Note that unit string is prepended by the mux, so we
    * don't put it here.
    */

#ifdef INCLUDE_L2_CACHE
    sysMotTsecFuncs.extWriteL2AllocFunc = sysL2ExtWriteBufferAlloc;
#endif

    if (strlen (pParamStr) == 0)
        {
        /*
        * muxDevLoad() calls us twice.  If the string is
        * zero length, then this is the first time through
        * this routine.
        */

        pEnd = (END_OBJ *) motTsecEndLoad  (pParamStr);
        }
    else
        {
        /*
        * On the second pass through here, we actually create
        * the initialization parameter string on the fly.
        * Note that we will be handed our unit number on the
        * second pass and we need to preserve that information.
        * So we use the unit number handed from the input string.
        */

        /* extract the unit number */
        tok = strtok_r (pParamStr, ":", &holder);
        if (tok == NULL)
           return (NULL);

        unit = (int) strtoul (tok, NULL, 16);

        if (unit > MOT_TSEC_MAX_DEVS )
            return (NULL);

        /* enable stats and put into GMII mode */
        usrFlags = MOT_TSEC_USR_STAT_ENABLE |
                   MOT_TSEC_USR_MODE_GMII;


	if (sysNetMacNVRamAddrGet ("mottsec", unit, enet, MAC_ADRS_LEN) == ERROR)
	    {
	    logMsg ("Error: motTsecEndLoad  illegal MAC address - use M command\n", 0, 0, 0, 0, 0, 0);
	    return(NULL);
	    }

        /* finish off the initialization parameter string */
        sprintf (paramStr, "%d:0x%x:0x%x:%02x-%02x-%02x-%02x-%02x-%02x:0x%x:0x%x:0x%x:0x%x:0x%x:0x%x:0x%x",
                 unit,
                 CCSBAR,
                 sysMotTsecNumByUnit[unit],
		 enet[5],enet[4],enet[3],enet[2],enet[1],enet[0],
                 usrFlags,
                 (UINT32)&sysMotTsecPhyParms[unit],
                 (UINT32)&sysMotTsecFuncs,
                 (UINT32)&sysMotTsecParms,
                 (UINT32)NULL,
		 (UINT32)NULL,
		 (UINT32)NULL
                 );

        if ((pEnd = (END_OBJ *) motTsecEndLoad  (paramStr)) == (END_OBJ *)NULL)
            logMsg ("Error: motTsecEndLoad  failed to load driver\n", 0, 0, 0, 0, 0, 0);
#if 0
        else
            logMsg ("Load successful: 0x%08x\n", (int)pEnd, 0, 0, 0, 0, 0);
#endif

        }

    return pEnd;
    }

/***********************************************************************
*
* sysMiiPhyStatusGet - Return Status for all PHY attributes that are
* hardware dependent.
*
*
* RETURNS: ERROR or OK.
*/

LOCAL STATUS sysMiiPhyStatusGet
    (
    PHY_INFO            * pPhyInfo,
    MOT_TSEC_PHY_STATUS * pStatus
    )
    {
    UINT16 miiStat;
    int    retVal = 0;

    if (sysMotTsecFuncs.miiPhyRead != NULL)
        {
        retVal = sysMotTsecFuncs.miiPhyRead(pPhyInfo->phyAddr,17,&miiStat);
        if (retVal != OK)
            return ERROR;

        pStatus->duplex = (miiStat&0x2000)?0:1;
        pStatus->speed  = (miiStat&0xc000)>>13;
        }
    return retVal;
    }

#if 0
/***********************************************************************
*
* sysMiiInt - MII interrupt service routine
*
* This routine checks if the link up or down and update a flag
*
* RETURNS: None.
*/

LOCAL void sysMiiInt
    (
    PHY_INFO * pPhyInfo
    )
    {
    UINT16 miiIntStatusReg;
    UINT32 event;

    /* Clear MII interrupt by reading Int status reg */
    if (sysMotTsecFuncs.miiPhyRead != NULL)
        {
        sysMotTsecFuncs.miiPhyRead (pPhyInfo->phyAddr,20,&miiIntStatusReg);
        event = miiIntStatusReg;
        if (sysMotTsecFuncs.miiPhyInt != NULL)
            {
            sysMotTsecFuncs.miiPhyInt (pPhyInfo->pDrvCtrl, event);
            }
        }
    return;
    }
#endif
/***********************************************************************
*
* sysMiiPhyInit - initialize and configure the PHY devices
*
* This routine scans, initializes and configures the PHY device.
*
* RETURNS: OK, or ERROR.
*/

LOCAL STATUS sysMiiPhyInit
    (
    PHY_INFO * pPhyInfo
    )
    {
    int    retVal=OK;

    /* Initialisation of Phy performed in driver */

    return (retVal);
#if 0
    if (retVal == OK)
        {
        if (sysMotTsecFuncs.miiPhyRead != NULL)
            {
            tmp = sysMotTsecFuncs.miiPhyRead(pPhyInfo->pDrvCtrl,
                                             pPhyInfo->phyAddr,18,
                                             &miiIntEnableReg);

            if (tmp == OK)
                {

 /*             intConnect (INUM_TO_IVEC(INUM_IRQ6),sysMiiInt,(int)pPhyInfo); */
                miiIntEnableReg = 0x12;
                if (sysMotTsecFuncs.miiPhyWrite != NULL)
                    {
                    tmp = sysMotTsecFuncs.miiPhyWrite(pPhyInfo->pDrvCtrl,
                                                      pPhyInfo->phyAddr, 18, 
                                                      miiIntEnableReg);
                    if (tmp == OK)
                        {
                    /*    intEnable (INUM_IRQ6);  */
                        }
                    retry = 4;
                    while (retry--)
                        {
                        tmp = sysMotTsecFuncs.miiPhyRead(pPhyInfo->pDrvCtrl,
                                                         pPhyInfo->phyAddr, 
                                                         18, &value);
                        if (value == miiIntEnableReg)
                            break;
                        }

                    }
                }
            }
        }

    return OK;
#endif
    }

/***********************************************************************
*
* sysMotTsecEnetEnable - enable the MII interface to the TSEC controller
*
* This routine is expected to perform any target specific functions required
* to enable the Ethernet device and to connect the MII interface to the TSEC.
*
* RETURNS: OK, or ERROR if the TSEC controller cannot be enabled.
*/

LOCAL STATUS sysMotTsecEnetEnable
    (
    UINT32  immrVal,    /* base address of the on-chip RAM */
    UINT32  tsecNum     /* TSEC being used */
    )
    {
    return(OK);
    }

/***********************************************************************
*
* sysMotTsecEnetDisable - disable MII interface to the TSEC controller
*
* This routine is expected to perform any target specific functions required
* to disable the Ethernet device and the MII interface to the TSEC
* controller.  This involves restoring the default values for all the Port
* B and C signals.
*
* RETURNS: OK, always.
*/

LOCAL STATUS sysMotTsecEnetDisable
    (
    UINT32  immrVal,    /* base address of the on-chip RAM */
    UINT32  tsecNum  /* TSEC being used */
    )
    {
    return(OK);
    }
