/* am29lv64xdMtd.c - MTD for Am29Lv64Xd */

/*
 * Copyright (c) 2003-2005 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved
 * by Wind River.
 */

#include "copyright_wrs.h"

/* FAT-FTL Lite Software Development Kit
 * Copyright (C) M-Systems Ltd. 1995-2001       */

/*
modification history
--------------------
01d,24mar05,mdo  Documentation changes for apigen
01c,22mar05,dtr  Typo fixes.
01b,18nov04,jln  fix compiler warning
01a,22oct04,jln  modified from 01l/cfiamd.c 
*/

/*
DESCRIPTION
This library provides a MTD for Am29Lv641D on cds8541/cds8555 reference boards.
It only supports 16 bit bus access to flash chips.  

INCLUDE FILES:
 
\NOMANUAL
*/

#include <stdio.h>
#include "tffs/flflash.h"
#include "tffs/backgrnd.h"

#define 	MAXSECTORS	128	/* should work with any value */

typedef enum
    {
    BOOTBLOCK_NONE,
    BOOTBLOCK_TOP,
    BOOTBLOCK_BOTTOM
    }BOOTBLOCK;

typedef union
    {
    UCHAR uchar[4];
    UINT32 uint32;
    } CFI_DWORD;

typedef union
    {
    UCHAR uchar[2];
    USHORT ushort;
    } CFI_WORD;

/* Instance specific CFI data so that a system may have more than one CFI
 * device. */
typedef struct
    {

    unsigned         commandSetId;            /* id of a specific command set. */
    unsigned         altCommandSetId;         /* id of alternate command set.  */
    FLBoolean        wordMode;                /* TRUE - word mode.             */
    /* FALSE - byte mode.            */
    int              multiplier;              /* the number of bytes between   */
    /* 1st Q and 1st R in query	     */
    int          interleaveWidth;     /* 1 - byte 2 - word interleaved */ 
    unsigned         maxBytesWrite;           /* maximum number of bytes       */
    /* in multi-byte write.          */
    FLBoolean        vpp;                     /* if = TRUE, need vpp.          */
    long             optionalCommands;        /* optional commands supported   */
    /* (1 = yes, 0 = no):            */
    /* bit 0 - chip erase.           */
    /* bit 1 - suspend erase.        */
    /* bit 2 - suspend write         */
    /* bit 3 - lock/unlock.          */
    /* bit 4 - queued erase.         */
    unsigned         afterSuspend;            /* functions supported after     */
    /* suspend (1 = yes, 0 = no):    */
    /* bit 0 - write after erase     */
    /*         suspend.              */
    int          sectorDefs;          /* Number of sector definitions  */
    struct
        {                  /* sector descriptions as found  */
        long     secSize;         /* in CFI query. 		     */
        int      numSecs;         /*				     */
        }secDesc[8];                  /* assume 8 is enough	     */
    struct
        {                  /*				     */
        long     sectorSize;          /* sector size 		     */
        UINT32       sectorBaseAdrs;      /* base address of sector	     */
        } secInfo[MAXSECTORS];            /* per sector info		     */
    UINT32 unlockAddr1;               /* offset for first unlock	     */
    UINT32 unlockAddr2;               /* offset for 2nd unlock	     */
    int sectorsInCFI;             /* sector count for device	     */
    int bootBlockSectors;             /* sectors that makeup boot block*/
    BOOTBLOCK bootBlockType;          /* Top, Bottom or None	     */

    } CFI;

LOCAL CFI mtdVars[DRIVES];

/* defines */

/* Save the last erase block on each device discovered in the array 
 * for NVRAM */
#undef SAVE_NVRAM_REGION

/* disable debugging */
#undef CFI_DEBUG

#ifdef CFI_DEBUG
    #define DEBUG_PRINT    printf
#else
    #undef DEBUG_PRINT
#endif

#ifndef _BYTE_ORDER
    #error "Error: _BYTE_ORDER needs to be #define'd.  Try #include \"vxWorks.h\" "
#endif

#if (_BYTE_ORDER == _BIG_ENDIAN)

    #define CFI_LONGSWAP(x)	LONGSWAP(x)	/* swap everything in a long word */
    #define CFI_WORDSWAP(x) WORDSWAP(x)	/* swap the shorts in a long */
    #define CFI_BYTESWAP(x) ( ( (x & 0xff) << 8) | ( (x >> 8) & 0xff) )  /* Swap bytes in a short */

#else

    #define CFI_LONGSWAP(x)	(x)		/* pass it as is */
    #define CFI_WORDSWAP(x) (x)		/* pass it as is */
    #define CFI_BYTESWAP(x) (x)		/* pass it as is */

#endif /* _BYTE_ORDER == _BIG_ENDIAN */

#define CFI_LONG_WRITE(addr, data)  (*(ULONG *)addr = (ULONG)(CFI_WORDSWAP(data)))
#define CFI_WORD_WRITE(addr, data)  (*(USHORT *)addr = (USHORT)(CFI_BYTESWAP(data)))
#define CFI_WORD_READ(addr)         (CFI_BYTESWAP(*(USHORT *)addr))
#define CFI_LONG_READ(addr)         (CFI_WORDSWAP(*(ULONG *)addr))

/* command set IDs */

#define INTEL_COMMAND_SET      0x0001
#define AMDFUJ_COMMAND_SET     0x0002
#define INTEL_ALT_COMMAND_SET  0x0001
#define AMDFUJ_ALT_COMMAND_SET 0x0004
#define ALT_NOT_SUPPORTED      0x0000


/* CFI identification strings */

#define ID_STR_LENGTH      3
#define QUERY_ID_STR       "QRY"
#define PRIMARY_ID_STR     "PRI"
#define ALTERNATE_ID_STR   "ALT"


/* commands */

#define AMD_SETUP_ERASE		0x80
#define AMD_SETUP_WRITE		0xa0
#define AMD_READ_ID 		0x90
#define AMD_SUSPEND_ERASE	0xb0
#define AMD_SECTOR_ERASE	0x30
#define AMD_RESUME_ERASE	0x30
#define AMD_READ_ARRAY		0xf0

#define AMD_NO_UNLOCK_ADDR 0xffffffffL

#define AMD_UNLOCK_1		0xaa
#define	AMD_UNLOCK_2		0x55

#define AMD_WW_UNLOCK_ADDR1	0x555u	/* Word wide devices */
#define	AMD_WW_UNLOCK_ADDR2	0x2aau  /* Word wide devices */
#define AMD_BW_UNLOCK_ADDR1	0xaaau  /* Byte wide devices */
#define	AMD_BW_UNLOCK_ADDR2	0x555u  /* Byte wide devices */

#define	AMD_D2		4	/* Toggles when erase suspended */
#define AMD_D5		0x20	/* Set when programming timeout */
#define	AMD_D6		0x40	/* Toggles when programming */


/* optional commands support */

#define CHIP_ERASE_SUPPORT           0x0001
#define SUSPEND_ERASE_SUPPORT        0x0002
#define SUSPEND_WRITE_SUPPORT        0x0004
#define LOCK_SUPPORT                 0x0008
#define QUEUED_ERASE_SUPPORT         0x0010

#define QUERY	0x98

/* supported functions after suspend */

#define WRITE_AFTER_SUSPEND_SUPPORT  0x0001

#define thisCFI   ((CFI *)vol.mtdVars)

/******************************************************************************
* cfiAmdChipCountGet - return the number of chips in this array
*
* Leave the first chip (or set of interleaved chips) in READ_ARRAY
* mode and move forward by chip size (or interleaved chip size) until
* address wrap around is detected. The chip count is updated in 
* vol.noOfChips.
*
* RETURNS:
*
* ERRNO
*
* \NOMANUAL
*/

LOCAL FLStatus cfiAmdChipCountGet
    (
    FLFlash vol    /* Pointer identifying drive */
    )
    {
    UINT32 cmdBuffer;
    int ix;
    char queryIdStr[ID_STR_LENGTH + 1] = QUERY_ID_STR;

    FlashPTR flashPtr = (FlashPTR) flMap(vol.socket, 0);

    /* Switch first (interleaved) chip set to QUERY mode */
    cmdBuffer = 0x0;
    for (ix = 0; ix < thisCFI->multiplier; ix++)
        cmdBuffer |= QUERY << (8 * ix);
    flashPtr[0x55 * thisCFI->multiplier] = cmdBuffer;

    /* NOTE: The address wrap around technique used here works only if the flash
     * size was declared correctly in the socket driver. At some point the MTD
     * should be discovering flash size and exporting it to the socket driver. 
     */

    for (vol.noOfChips = 1 * vol.interleaving;       /* Scan the chips */
        vol.noOfChips < 2000;  /* Big enough ? */
        vol.noOfChips += vol.interleaving)
        {
#ifdef SAVE_NVRAM_REGION

        /* Reinstate the NVRAM region */
        flashPtr = (FlashPTR) flMap(vol.socket, vol.noOfChips * 
                                    (vol.chipSize + (vol.erasableBlockSize / vol.interleaving)));
#else
        flashPtr = (FlashPTR) flMap(vol.socket, vol.noOfChips * vol.chipSize);
#endif

#ifdef DEBUG_PRINT
        DEBUG_PRINT("Debug: Looking for Flash device at base 0x%x\n", (UINT32) flashPtr);
#endif
        if ((flashPtr[0x10 * thisCFI->multiplier]) 
            == (unsigned char)queryIdStr[0] &&
            (flashPtr[0x11 * thisCFI->multiplier]) 
            == (unsigned char)queryIdStr[1] &&
            (flashPtr[0x12 * thisCFI->multiplier]) 
            == (unsigned char)queryIdStr[2])
            {
            goto noMoreChips;      /* Wrapped around */
            }

        /* Confirm this is also a CFI part */
        *(UCHAR *)(flashPtr + (0x55 * thisCFI->multiplier))
        = (UCHAR)(QUERY);
        if (flashPtr[0x10 * thisCFI->multiplier]
            != (unsigned char)queryIdStr[0] ||
            flashPtr[0x11 * thisCFI->multiplier]
            != (unsigned char)queryIdStr[1] ||
            flashPtr[0x12 * thisCFI->multiplier]
            != (unsigned char)queryIdStr[2])
            {
            /* Should not happen !! */
            goto noMoreChips;   /* Not a CFI Flash part */
            }

        flashPtr[0x55 * thisCFI->multiplier] 
        = (UCHAR)(AMD_READ_ARRAY);
        }
    /* We should never get here. */
#ifdef DEBUG_PRINT
    DEBUG_PRINT("Debug: Device count overflow\n");
#endif  /* DEBUG_PRINT */
    return flGeneralFailure;

    noMoreChips:
    flashPtr = (FlashPTR) flMap(vol.socket, 0);
    /* Switch to READ_ARRAY mode */
    cmdBuffer = 0x0;
    for (ix = 0; ix < thisCFI->multiplier; ix++)
        cmdBuffer |= AMD_READ_ARRAY << (8 * ix);
    flashPtr[0x55 * thisCFI->multiplier] = cmdBuffer;

    return flOK;
    }

/******************************************************************************
* cfiAmdWrite - Write a block of bytes to Flash
*
* This routine will be registered as the MTD vol.write routine. 
* Given a pointer to a buffer that must be written, the write width 
* determined from the identification process is used the stepping stone 
* to iterate through the buffer.
*							                                                                    
* RETURNS:                                                           
*	FLStatus	: 0 on success, failed otherwise	
*
* ERRNO
*/

LOCAL FLStatus cfiAmdWrite
    (
    FLFlash vol,                  /* Pointer identifying drive         */
    CardAddress address,          /* Card address to write to          */
    const void FAR1 *buffer,      /* Address of data to write          */
    int length,                   /* Number of bytes to write          */
    FLBoolean overwrite           /* Mode: TRUE overwrite;FALSE erased */
    )
    {
    /* Set timeout to 5 seconds from now */
    unsigned long writeTimeout = flMsecCounter + 5000;
    int cLength;
    CardAddress cAddr = address;
    FlashPTR base;
    FlashPTR flashPtr;
    UINT32 unlock1 = 0;
    UINT32 unlock2 = 0;
    UINT32 setup_write = 0;
    UINT32 read_array = 0;
    int i;
    CFI_WORD  tmpWord;

#define bFlashPtr  flashPtr
#define bBuffer ((const unsigned char FAR1 *) buffer)
#define wFlashPtr ((FlashWPTR) flashPtr)
#define wBuffer ((const unsigned short FAR1 *) buffer)
#define dFlashPtr ((FlashDPTR) flashPtr)
#define dBuffer ((const unsigned long FAR1 *) buffer)

    /* Setup the commands first */
    for (i = 0; i < thisCFI->multiplier; i++)
        {
        unlock1     |= AMD_UNLOCK_1 << (i * 8);
        unlock2     |= AMD_UNLOCK_2 << (i * 8);
        setup_write |= AMD_SETUP_WRITE << (i * 8);
        read_array  |= AMD_READ_ARRAY << (i * 8);
        }

    if (flWriteProtected(vol.socket))
        return flWriteProtect;

    i = 0; 
    while ((thisCFI->secInfo[i].sectorBaseAdrs <= address) && (i < thisCFI->sectorsInCFI))
        i++;
    i--;

    base = (FlashPTR)
           vol.map(&vol, thisCFI->secInfo[i].sectorBaseAdrs,
                   vol.interleaving * thisCFI->interleaveWidth);

    flashPtr = (FlashPTR)
               vol.map(&vol, address,
                       vol.interleaving * thisCFI->interleaveWidth);

    cLength = length;

    if (vol.interleaving * thisCFI->interleaveWidth == 1)
        {
        while (cLength >= 2)
            {
            *(USHORT *)(base + 
                        (thisCFI->unlockAddr1 * thisCFI->multiplier)) = unlock1;
            *(USHORT *)(base + 
                        (thisCFI->unlockAddr2 * thisCFI->multiplier)) = unlock2;
            *(USHORT *)(base + 
                        (thisCFI->unlockAddr1 * thisCFI->multiplier)) = setup_write;

            *wFlashPtr = *wBuffer;

            while ((wFlashPtr[0] != wBuffer[0]) && 
                   (flMsecCounter < writeTimeout))
                {
                if (((wFlashPtr[0] & AMD_D5) && 
                     ((wFlashPtr[0] ^ wBuffer[0]) &   0xff)))
                    {
                    wFlashPtr[0] = read_array;
#ifdef DEBUG_PRINT
                    DEBUG_PRINT("Debug: write failed in AMD MTD.\n");
#endif
                    return flWriteFault;
                    }
                }

            cLength -= 2;
            cAddr   += 2;
            buffer  = (const void FAR1 *)((UINT32)buffer+2);
            flashPtr += 2;
            }

        if (cLength > 0)
            {
            /* copy data from flash to tmpWord */
            tmpWord.ushort = wFlashPtr[0];

            /* now fill in the left over byte */
            tmpWord.uchar[0] = *(char *)buffer;

            *(USHORT *)(base + 
                        (thisCFI->unlockAddr1 * thisCFI->multiplier)) = unlock1;
            *(USHORT *)(base + 
                        (thisCFI->unlockAddr2 * thisCFI->multiplier)) = unlock2;
            *(USHORT *)(base + 
                        (thisCFI->unlockAddr1 * thisCFI->multiplier)) = setup_write;

            *wFlashPtr = tmpWord.ushort;

            while ((wFlashPtr[0] != tmpWord.ushort) && 
                   (flMsecCounter < writeTimeout))
                {
                if (((wFlashPtr[0] & AMD_D5) && 
                     ((wFlashPtr[0] ^ tmpWord.ushort) &   0xff)))
                    {
                    wFlashPtr[0] = read_array;
#ifdef DEBUG_PRINT
                    DEBUG_PRINT("Debug: write failed in AMD MTD.\n");
#endif
                    return flWriteFault;
                    }
                }
            cAddr += cLength;
            buffer = (const void FAR1 *)((UINT32)buffer + cLength);
            flashPtr = flashPtr + cLength;
            cLength = 0;
            }
        /* cfiAmdLeftoverBytesWrite(&vol, buffer, flashPtr, cLength); */
        }

    flashPtr -= length;
    buffer = (unsigned char *)buffer - length; /* bBuffer -= length; */

    if (tffscmp((void FAR0 *) flashPtr,buffer,length))
        {
#ifdef DEBUG_PRINT
        DEBUG_PRINT("Debug: write failed in AMD MTD on verification.\n");
#endif
        return flWriteFault;
        }

    return flOK;
    }

/*******************************************************************************
* cfiAmdErase - Erase one or more contiguous Flash erasable blocks	
*						
* This routine will be registered as the MTD vol.erase routine. Sector zero is 
* assumed to be the boot block anchor of the boot block on bottom boot devices,
* while the first sector of size not equal to vol.erasableBlockSize is assumed 
* to be the anchor for top boot devices.
*							
* RETURNS:                                                   
*	FLStatus	: 0 on success, failed otherwise
*
* ERRNO
*/

LOCAL  FLStatus cfiAmdErase
(
    FLFlash vol,                 /* Pointer identifying drive      */
    int firstErasableBlock,      /* Number of first block to erase */
    int numOfErasableBlocks      /* Number of blocks to erase      */
    )
    {
    int i;
    UINT32 unlock1 = 0;
    UINT32 unlock2 = 0;
    UINT32 erase_setup = 0;
    UINT32 erase_sector = 0;
    int thisSector = firstErasableBlock;
    int sectorsToErase = numOfErasableBlocks;
    UINT32 * unlockAddr1;
    UINT32 * unlockAddr2;

    if (flWriteProtected(vol.socket))
        return flWriteProtect;

    /* Setup the commands first */

    for (i = 0; i < thisCFI->multiplier; i++)
        {
        unlock1      |= AMD_UNLOCK_1 << (i * 8);
        unlock2      |= AMD_UNLOCK_2 << (i * 8);
        erase_setup  |= AMD_SETUP_ERASE << (i * 8);
        erase_sector |= AMD_SECTOR_ERASE << (i * 8);
        }

    for ( ; thisSector < firstErasableBlock + sectorsToErase; thisSector++)
        {
        int i;
        FLBoolean finished;
        FlashPTR flashPtr;

#ifdef DEBUG_PRINT 
        DEBUG_PRINT("Clearing sector %d\n", thisSector);
#endif 

        /* we know we are on a unit boundary so mapBase is not necessary */
        flashPtr = (FlashPTR)
                   vol.map(&vol, thisCFI->secInfo[thisSector].sectorBaseAdrs, 0);

        unlockAddr1 = (UINT32 *)((long)flashPtr + (thisCFI->unlockAddr1 *thisCFI->multiplier));
        unlockAddr2 = (UINT32 *)((long)flashPtr + (thisCFI->unlockAddr2 *thisCFI->multiplier));

        *(UINT16 *)unlockAddr1 = unlock1;
        *(UINT16 *)unlockAddr2 = unlock2;
        *(UINT16 *)unlockAddr1 = erase_setup;
        *(UINT16 *)unlockAddr1 = unlock1;
        *(UINT16 *)unlockAddr2 = unlock2;
        *(UINT16 *)flashPtr = erase_sector;

        do 
            {
            finished = TRUE;

            for (i = 0;i < thisCFI->multiplier;i += thisCFI->interleaveWidth)
                {
                if (flashPtr[i] != 0xff)
                    {
                    if ((flashPtr[i] & AMD_D5) && flashPtr[i] != 0xff)
                        {
                        int x;
                        UINT32 c;

                        for (x = 0, c = 0; x < thisCFI->multiplier; x++)
                            c |= AMD_READ_ARRAY << (x * 8);
                        flashPtr[i] = c;
#ifdef DEBUG_PRINT
                        DEBUG_PRINT("Debug: erase failed in AMD MTD.\n");
#endif
                        return flWriteFault;
                        }
                    finished = FALSE;
                    }
                }
            } while (!finished);
        }

    return flOK;
    }

/***************************************************************************
* cfiscsIdentify - Identification routine for devices conforming to CFI/SC
*
* Identifies media based on CFI and the AMD/Fujitsu command set and registers
* as an MTD for such. This routine should be placed on the MTD list in 
* flcustom.h. It must be an extern routine. On successful identification, the
* Flash structure is filled out and the write and erase routines registered. 
*
* RETURNS:
*      FLStatus        : 0 on positive identification, failed otherwise 
*
* ERRNO
*
* http://www.amd.com/us-en/FlashMemory/ProductInformation/0,,37_1447_1451_1780%5E1834%5E1955,00.html
*
* \NOMANUAL
*/
FLStatus cfiAmdIdentify
    (
    FLFlash vol              /* Pointer identifying drive */
    )
    {
    FlashPTR flashPtr = (FlashPTR) flMap(vol.socket, 0);
    FlashWPTR flashWPtr = (FlashWPTR) flashPtr;

    unsigned primaryTable, secondaryTable;
    FLBoolean eightBitMode = FALSE;
    int thisSector = 0;     /* running count of sectors for this CFI */
    CardAddress sectorBaseAdrs = 0; /* base address of this sector */
    int ix = 0;

#ifdef DEBUG_PRINT
    DEBUG_PRINT("Debug: entering CFIAMD identification routine.\n");
    DEBUG_PRINT("Debug: flash base addr = 0x%x\n", (UINT32)flashPtr);
#endif

    flSetWindowBusWidth(vol.socket, 16);/* use 16-bits */
    flSetWindowSpeed(vol.socket, 120);  /* 120 nsec. */
    flSetWindowSize(vol.socket, 2);       /* 8 KBytes */

    vol.mtdVars = &mtdVars[flSocketNoOf(vol.socket)];
    thisCFI->bootBlockSectors = 0;

    /* Is this an 8 bit device */
    flashPtr[0x55] = AMD_READ_ARRAY;
    flashPtr[0x55] = QUERY;

    if (flashPtr[0x10] == 0x51 && /* 'Q' */
        flashPtr[0x11] == 0x52 && /* 'R' */
        flashPtr[0x12] == 0x59)   /* 'Y' */
        {
#ifdef DEBUG_PRINT
        DEBUG_PRINT ("Debug: detected single 8 bit device\n");
#endif
        thisCFI->multiplier = 1;
        thisCFI->interleaveWidth = 1;
        vol.interleaving = 1;
        eightBitMode = TRUE;

        goto getCFI;
        }

    /* Reset to READ_ARRAY and retry. Maybe 16 bit addressing 
     */
    flashPtr[0x55] = AMD_READ_ARRAY;
    flashWPtr[0x55] = (USHORT) ((QUERY << 8) | QUERY); 

    /* Check for two interleaved 8 bit parts */
    if (flashPtr[0x20] == 0x51 && /* 'Q' */
        flashPtr[0x21] == 0x51 && /* 'Q' */
        flashPtr[0x22] == 0x52 && /* 'R' */
        flashPtr[0x23] == 0x52 && /* 'R' */
        flashPtr[0x24] == 0x59 && /* 'Y' */
        flashPtr[0x25] == 0x59)   /* 'Y' */
        {
        /* Let's try turning one off */
        CFI_WORD_WRITE((FlashWPTR)(&flashPtr[0x55]), AMD_READ_ARRAY);
        if (flashPtr[0x20] != 0x51) /* Turned off successfully */
            {
            thisCFI->multiplier = 2;
            thisCFI->interleaveWidth = 1;
            vol.interleaving =2;
#ifdef DEBUG_PRINT
            DEBUG_PRINT ("Debug: detected two 8 bit devices\n");
#endif
            eightBitMode = TRUE;
            goto getCFI;
            }
        }

    /* a 16 bit device in 16 bit mode */
    if (flashWPtr[0x10] == 'Q' && 
        flashWPtr[0x11] == 'R' &&
        flashWPtr[0x12] == 'Y')
        {
        thisCFI->multiplier = 2;
        thisCFI->interleaveWidth = 1;
        vol.interleaving = 1;
#ifdef DEBUG_PRINT
        DEBUG_PRINT ("Debug: detected one 16 bit device\n");
#endif
        goto getCFI;
        }

#ifdef DEBUG_PRINT
    DEBUG_PRINT ("Debug: No flash media detected!\n");
#endif

    return flUnknownMedia;

    getCFI:

    if (!eightBitMode)
        {
        thisCFI->wordMode = TRUE; /* limiting ourselves to 8 an 16 bit devs */
        thisCFI->unlockAddr1 = AMD_WW_UNLOCK_ADDR1;
        thisCFI->unlockAddr2 = AMD_WW_UNLOCK_ADDR2;
#ifdef DEBUG_PRINT
        DEBUG_PRINT("WORD MODE !!\n");
#endif
        }
    else
        {
        thisCFI->wordMode = FALSE;
        thisCFI->unlockAddr1 = AMD_BW_UNLOCK_ADDR1;
        thisCFI->unlockAddr2 = AMD_BW_UNLOCK_ADDR2;
#ifdef DEBUG_PRINT
        DEBUG_PRINT("WORD MODE !!\n");
#endif
        }

    /* check the command set ID */
    /* NOTE: Not swapped */
    thisCFI->commandSetId = *(USHORT *)(&flashPtr[0x13 * thisCFI->multiplier]);
#ifdef DEBUG_PRINT
    DEBUG_PRINT ("Debug: Commandset ID is 0x%x\n", thisCFI->commandSetId);
#endif

    /* Only support the AMD/Fujitsu Command set */
    if ( thisCFI->commandSetId != AMDFUJ_COMMAND_SET)
        {
#ifdef DEBUG_PRINT
        DEBUG_PRINT("Debug: did not recognize command set.\n");
#endif
        return flUnknownMedia;
        }

    /* get address for primary algorithm extended table. */
    primaryTable = CFI_WORD_READ(&flashPtr[0x15 * thisCFI->multiplier]);

    /* check alternate command set ID. */
    /* NOTE: not swapped */
    thisCFI->altCommandSetId = *(USHORT *)
                               (&flashPtr[0x17 * thisCFI->multiplier]);
    if (thisCFI->altCommandSetId != AMDFUJ_ALT_COMMAND_SET &&
        thisCFI->altCommandSetId != ALT_NOT_SUPPORTED)
        return flUnknownMedia;

    /* get address for secondary algorithm extended table. */
    secondaryTable = CFI_WORD_READ(&flashPtr[0x19 * thisCFI->multiplier]);

    thisCFI->vpp = flashPtr[0x1d * thisCFI->multiplier];

    /*Get the number of erase block descriptions for the CFI*/
    if (eightBitMode)
        thisCFI->sectorDefs = (int) (*(UCHAR *) 
                                     (&flashPtr[0x2c * thisCFI->multiplier]));
    else
        thisCFI->sectorDefs = (int) (*(USHORT *)
                                     (&flashPtr[0x2c * thisCFI->multiplier]));

    /* We should bail out if this is greater than 8 */
#ifdef DEBUG_PRINT
    DEBUG_PRINT ("Debug: Number of erase block descriptions is 0x%x\n", 
                 thisCFI->sectorDefs);
#endif

    vol.erasableBlockSize = 0;
    thisCFI->sectorsInCFI = 0;

    for ( ix = 0; ix < thisCFI->sectorDefs; ix++)
        {
        thisCFI->secDesc[ix].numSecs = (int) (*(USHORT *)
                                              (&flashPtr[(0x2d + (ix * 4)) * thisCFI->multiplier]));
        thisCFI->secDesc[ix].numSecs++;

#ifdef DEBUG_PRINT
        DEBUG_PRINT ("Debug: Num sectors in %d - %d\n", ix, thisCFI->secDesc[ix].numSecs);
#endif

        thisCFI->secDesc[ix].secSize = (long) ((*(USHORT *)
                                                (&flashPtr[(0x2f + (ix * 4)) * thisCFI->multiplier])) +
                                               (*(USHORT *)(&flashPtr[(0x30 + (ix * 4)) * 
                                                                      thisCFI->multiplier])) * 0x100L);
#ifdef DEBUG_PRINT
        DEBUG_PRINT ("Debug: Sector size is 0x%x\n",
                     (UINT32) thisCFI->secDesc[ix].secSize);
#endif

        /* TrueFFS does not support the flexible sector architecture so we 
         * take the largest sector size to be the erase block size.
         */ 
        if (vol.erasableBlockSize < thisCFI->secDesc[ix].secSize)
            vol.erasableBlockSize = thisCFI->secDesc[ix].secSize;

        /* Also track the number of sector on this device */
        thisCFI->sectorsInCFI += thisCFI->secDesc[ix].numSecs;
        }

    if (vol.erasableBlockSize == 0x00)
        vol.erasableBlockSize = 0x80L;
    else
        vol.erasableBlockSize *= 256;

    /* Get Device Size */   
    if (eightBitMode)
        vol.chipSize = (1L << flashPtr[0x27 * thisCFI->multiplier]);
    else
        vol.chipSize = (1L << *(USHORT*)(&flashPtr[0x27 * thisCFI->multiplier]));

    vol.erasableBlockSize *= vol.interleaving;

    vol.chipSize -= CDS85XX_FLASH_RESERVED_SIZE;

#ifdef SAVE_NVRAM_REGION

    /* Top boot block devices will loose their entire boot block to NVRAM. Since 
     * TrueFFS cares not about the subdivisions we reserve an entire erase block
     * on each of the interleaved devices. 
     */
    vol.chipSize -= vol.erasableBlockSize;
#endif

#ifdef DEBUG_PRINT
    DEBUG_PRINT("Debug: %d sectors on device\n", thisCFI->sectorsInCFI);
    DEBUG_PRINT("Debug: Erasable block size is 0x%lx\n", vol.erasableBlockSize);
    DEBUG_PRINT("Debug: Chip size is 0x%lx\n", vol.chipSize);
#endif

    thisCFI->bootBlockType = BOOTBLOCK_NONE;

    /* Simplest case is the uniform sector device. Has only one 
     * sector desc. 
     */
    for (; thisSector < thisCFI->secDesc[0].numSecs; thisSector++)
        {
        thisCFI->secInfo[thisSector].sectorSize = vol.erasableBlockSize;
        thisCFI->secInfo[thisSector].sectorBaseAdrs = sectorBaseAdrs;
        sectorBaseAdrs += (CardAddress) vol.erasableBlockSize;
        }

#ifdef DEBUG_PRINT
    DEBUG_PRINT("Debug: Number of boot block sectors is %d\n", thisCFI->bootBlockSectors);
#endif

    /* Make sure this comes at the end since the device is set to READ_ARRAY
     * mode prior to the return
     */
    if (cfiAmdChipCountGet(&vol) != flOK)
        return flUnknownMedia;

#ifdef DEBUG_PRINT
    DEBUG_PRINT ("Debug: No of chips detected is %d\n", vol.noOfChips);
#if 0
    for (ix = 0; ix < thisCFI->sectorsInCFI; ix++)
        DEBUG_PRINT ("%2d:0x%x	---  0x%lx\n", ix,
                     thisCFI->secInfo[ix].sectorBaseAdrs, 
                     thisCFI->secInfo[ix].sectorSize);
#endif
#endif

    vol.erase = cfiAmdErase;
    vol.write = cfiAmdWrite;

    /* Might have to do this on a bus width basis but for now it seems to
     * work with Intel devices.
     */
    flashPtr[0] = AMD_READ_ARRAY;
    flashPtr[1] = AMD_READ_ARRAY;
    flashPtr[2] = AMD_READ_ARRAY;
    flashPtr[3] = AMD_READ_ARRAY;

    return flOK;
    }
