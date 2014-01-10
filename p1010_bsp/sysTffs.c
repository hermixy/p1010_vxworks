/* sysTffs.c - TrueFFS socket driver */

/*
 * Copyright (c) 2003-2005 Wind River Systems, Inc.
 *
 * The right to copy, distribute or otherwise make use of this software
 * may be licensed only pursuant to the terms of an applicable Wind River
 * license agreement. No license to Wind River intellectual property rights
 * is granted herein. All rights not licensed by Wind River are reserved
 * by Wind River.
 */

/*
modification history
--------------------
01d,22jun05,pcm  removed #include "dosFsLib.h"
01c,24mar05,mdo  Documentation changes for apigen
01b,19nov04,jln  fix compiler warning
01a,18oct04,jln  Modify from 01i/sysTffs.c/ads8560
*/

/*
DESCRIPTION
This library provides board-specific hardware access routines for TrueFFS.
In effect, these routines comprise the socket component driver (or drivers)
for your flash device hardware.  At socket registration time, TrueFFS stores
pointers to the functions of this socket component driver in an 'FLSocket'
structure.  When TrueFFS needs to access the flash device, it uses these
functions.
 
Because this file is, for the most part, a device driver that exports its
functionality by registering function pointers with TrueFFS, very few of the
functions defined here are externally callable.  For the record, these
external functions are flFitInSocketWindow() and flDelayLoop().  You should
never have any need to call these functions.
 
However, one of the most import functions defined in this file is neither
referenced in an 'FLSocket' structure, nor is it externally callable.  This
function is sysTffsInit().  TrueFFS calls this function at initialization
time to register socket component drivers for all the flash devices attached
to your target.  It is this call to sysTffs() that results in assigning
drive numbers to the flash devices on your target hardware.  Drive numbers
are assigned by the order in which the socket component drivers are registered.
The first to be registered is drive 0, the second is drive 1, and so on up to
4.  As shipped, TrueFFS supports up to five flash drives.
 
After registering socket component drivers for a flash device, you may
format the flash medium even though there is not yet a block device driver
associated with the flash (see the reference entry for the tffsDevCreate()
routine).  To format the flash medium for use with TrueFFS,
call tffsDevFormat() or, for some BSPs, sysTffsFormat().

The sysTffsFormat() routine is an optional but BSP-specific externally
callable helper function.  Internally, it calls tffsDevFormat() with a
pointer to a 'FormatParams' structure initialized to values that leave a
space on the flash device for a boot image. This space is outside the
region managed by TrueFFS.  This special region is necessary for boot
images because the normal translation and wear-leveling services of TrueFFS
are incompatible with the needs of the boot program and the boot image it
relies upon.  To write a boot image (or any other data) into this area,
use tffsBootImagePut().
 
Finally, this file also contains define statements for symbolic constants
that determine which MTDs, translation layer modules, and other utilities
are ultimately included in TrueFFS.  These defines are as follows:
 
\is
\i INCLUDE_TL_NFTL
To include the NAND-based translation layer module.
\i INCLUDE_TL_FTL
To include the NOR-based translation layer module.
\i INCLUDE_TL_SSFDC
To include the SSFDC-appropriate translation layer module.
\i INCLUDE_MTD_I28F016
For Intel 28f016 flash devices.
\i INCLUDE_MTD_I28F008
For Intel 28f008 flash devices.
\i INCLUDE_MTD_I28F008_BAJA
For Intel 28f008 flash devices on the Heurikon Baja 4700.
\i INCLUDE_MTD_AMD
For AMD, Fujitsu: 29F0{40,80,16} 8-bit flash devices.
\i INCLUDE_MTD_CDSN
For Toshiba, Samsung: NAND CDSN flash devices.
\i INCLUDE_MTD_DOC2
For Toshiba, Samsung: NAND DOC flash devices.
\i INCLUDE_MTD_CFISCS
For CFI/SCS flash devices.
\i INCLUDE_MTD_WAMD
For AMD, Fujitsu 29F0{40,80,16} 16-bit flash devices.
\i INCLUDE_TFFS_BOOT_IMAGE
To include tffsBootImagePut() in TrueFFS for Tornado.
\ie

To exclude any of the modules mentioned above, edit sysTffs.c and undefine
its associated symbolic constant.

INCLUDE FILES: flsocket.h
*/

/* defines */


#include "vxWorks.h"
#include "config.h"
#include "tffs/flsocket.h"
#include "taskLib.h"
#include "intLib.h"
#include "logLib.h"

#if defined(INCLUDE_TFFS)

/* defines */

#undef	INCLUDE_MTD_I28F016		/* Intel: 28f016 */
#undef	INCLUDE_MTD_I28F008		/* Intel: 28f008 */
#undef 	INCLUDE_MTD_AMD			/* AMD, Fujitsu: 29f0{40,80,16} 8bit */
#undef	INCLUDE_MTD_CDSN		/* Toshiba, Samsung: NAND, CDSN */
#undef	INCLUDE_MTD_DOC2		/* Toshiba, Samsung: NAND, DOC */
#undef  INCLUDE_MTD_CFISCS		/* CFI/SCS */
#define INCLUDE_MTD_CFIAMD              /* AMD CFI compliant */
#undef	INCLUDE_MTD_WAMD		/* AMD, Fujitsu: 29f0{40,80,16} 16bit */
#undef	INCLUDE_TL_NFTL			/* NFTL translation layer */
#define	INCLUDE_TL_FTL			/* FTL translation layer */
#undef	INCLUDE_TL_SSFDC		/* SSFDC translation layer */
#undef  INCLUDE_TFFS_BOOT_IMAGE		/* include tffsBootImagePut() */

/* locals */

/* forward declarations */

static FLBoolean	rfaCardDetected (FLSocket vol);
static void		rfaVccOn (FLSocket vol);
static void		rfaVccOff (FLSocket vol);
#ifdef	SOCKET_12_VOLTS
static FLStatus		rfaVppOn (FLSocket vol);
static void		rfaVppOff (FLSocket vol);
#endif	/* SOCKET_12_VOLTS */
static FLBoolean	rfaGetAndClearCardChangeIndicator (FLSocket vol);
static FLBoolean	rfaWriteProtected (FLSocket vol);
static void		rfaSetWindow (FLSocket vol);
static void		rfaSetMappingContext (FLSocket vol, unsigned page);
static FLStatus		rfaSocketInit (FLSocket vol);
static FLStatus		rfaRegister (int);

/* globals */

char pcDriveNo[2] = {NONE, NONE};	/* drive number of the sockets */

#ifndef DOC
#include "tffs/tffsConfig.c"
#endif /* DOC */

/*******************************************************************************
*
* sysTffsBaseGet - get the flash base address
*
* This routine gets the base address of the flash.
*
* RETURNS: NONE or flash address 
*
* ERRNO
*/

UINT32 sysTffsBaseGet
    (
    int index 
    )
    {
    if (index == 0)
        return FLASH_BASE_ADRS; 
    else if (index == 1)
        return FLASH1_BASE_ADRS;
    else
        return (UINT32)NONE;

    }

/*******************************************************************************
*
* sysTffsInit - initialize TFFS flash socket interface routine
*
* This is the TFFS flash socket interface initialization routine.
*
* RETURNS: N/A
*
* ERRNO
*/

LOCAL void sysTffsInit (void)
    {
    rfaRegister (0);

#ifdef INCLUDE_CDS85XX_SECOND_TFFS_FLASH
    rfaRegister (1);
#endif
    }

/*******************************************************************************
*
* rfaRegister - install routines for the RFA
*
* This routine installs necessary functions for the RFA.
*
* RETURNS: flOK, or flTooManyComponents if there're too many drives
*
* ERRNO
*/

static FLStatus rfaRegister 
    (
    int devNo
    )
    {
    FLSocket vol = flSocketOf (noOfDrives);
    UINT32  adrs;

    if (noOfDrives >= DRIVES)
        return (flTooManyComponents);

    if (devNo == 0)
        tffsSocket[noOfDrives] = "RFA0";
    else
        tffsSocket[noOfDrives] = "RFA1";

    if ((adrs = sysTffsBaseGet(devNo)) == (UINT32)(NONE))
        return (flAdapterNotFound);

    noOfDrives++;

    vol.serialNo = devNo;
    vol.window.baseAddress = adrs >> 12;

    /* fill in function pointers */

    vol.cardDetected      = rfaCardDetected;
    vol.VccOn             = rfaVccOn;
    vol.VccOff            = rfaVccOff;
#ifdef SOCKET_12_VOLTS
    vol.VppOn             = rfaVppOn;
    vol.VppOff            = rfaVppOff;
#endif
    vol.initSocket        = rfaSocketInit;
    vol.setWindow         = rfaSetWindow;
    vol.setMappingContext = rfaSetMappingContext;
    vol.getAndClearCardChangeIndicator =
                          rfaGetAndClearCardChangeIndicator;
    vol.writeProtected    = rfaWriteProtected;

    return (flOK);
    }

/*******************************************************************************
*
* rfaCardDetected - detect if a card is present (inserted)
*
* This routine detects if a card is present (inserted).
*
* RETURNS: TRUE, or FALSE if the card is not present.
*
* ERRNO
*/

static FLBoolean rfaCardDetected
    (
    FLSocket vol
    )
    {
    return (TRUE);
    }

/*******************************************************************************
*
* rfaVccOn - turn on Vcc (3.3/5 Volts)
*
* This routine turns on Vcc (3.3/5 Volts).  Vcc must be known to be good
* on exit.
*
* RETURNS: N/A
*
* ERRNO
*/

static void rfaVccOn 
    (
    FLSocket vol
    )
    {
    }

/*******************************************************************************
*
* rfaVccOff - turn off Vcc (3.3/5 Volts)
*
* This routine turns off Vcc (3.3/5 Volts). 
*
* RETURNS: N/A
*
* ERRNO
*/

static void rfaVccOff 
    (
    FLSocket vol
    )
    {
    }

#ifdef SOCKET_12_VOLTS

/*******************************************************************************
*
* rfaVppOn - turns on Vpp (12 Volts)
*
* This routine turns on Vpp (12 Volts). Vpp must be known to be good on exit.
*
* RETURNS: flOK always
*
* ERRNO
*/

static FLStatus rfaVppOn
    (
    FLSocket vol		/* pointer identifying drive */
    )
    {
    return (flOK);
    }

/*******************************************************************************
*
* rfaVppOff - turns off Vpp (12 Volts)
*
* This routine turns off Vpp (12 Volts).
*
* RETURNS: N/A
*
* ERRNO
*/

static void rfaVppOff 
    (
    FLSocket vol		/* pointer identifying drive */
    ) 
    {
    }

#endif	/* SOCKET_12_VOLTS */


/*******************************************************************************
*
* rfaSocketInit - perform all necessary initializations of the socket
*
* This routine performs all necessary initializations of the socket.
*
* RETURNS: flOK always
* 
* ERRNO
*/

static FLStatus rfaSocketInit
    (
    FLSocket vol		/* pointer identifying drive */
    ) 
    {
    vol.cardChanged = FALSE;

    /* enable memory window and map it at address 0 */
    rfaSetWindow (&vol);

    return (flOK);
    }

/*******************************************************************************
*
* rfaSetWindow - set current window attributes, Base address, size, etc
*
* This routine sets current window hardware attributes: Base address, size,
* speed and bus width.  The requested settings are given in the 'vol.window' 
* structure.  If it is not possible to set the window size requested in
* 'vol.window.size', the window size should be set to a larger value, 
* if possible. In any case, 'vol.window.size' should contain the 
* actual window size (in 4 KB units) on exit.
*
* RETURNS: N/A
* 
* ERRNO
*/

static void rfaSetWindow
    (
    FLSocket vol		/* pointer identifying drive */
    ) 
    {
    flSetWindowSize (&vol, FLASH_WINDOW_SIZE >> 12);
    }

/*******************************************************************************
*
* rfaSetMappingContext - sets the window mapping register to a card address
*
* This routine sets the window mapping register to a card address.
* The window should be set to the value of 'vol.window.currentPage',
* which is the card address divided by 4 KB. An address over 128MB,
* (page over 32K) specifies an attribute-space address.
*
* The page to map is guaranteed to be on a full window-size boundary.
*
* RETURNS: N/A
*
* ERRNO
*/

static void rfaSetMappingContext 
    (
    FLSocket vol,		/* pointer identifying drive */
    unsigned page		/* page to be mapped */
    )
    {
    }

/*******************************************************************************
*
* rfaGetAndClearCardChangeIndicator - return the hardware card-change indicator
*
* This routine returns the hardware card-change indicator and clears it if set.
*
* RETURNS: FALSE, or TRUE if the card has been changed
*
* ERRNO
*/

static FLBoolean rfaGetAndClearCardChangeIndicator
    (
    FLSocket vol		/* pointer identifying drive */
    ) 
    {
    return (FALSE);
    }

/*******************************************************************************
*
* rfaWriteProtected - return the write-protect state of the media
*
* This routine returns the write-protect state of the media
*
* RETURNS: FALSE, or TRUE if the card is write-protected
*
* ERRNO
*/

static FLBoolean rfaWriteProtected 
    (
    FLSocket vol		/* pointer identifying drive */
    ) 
    {
    return (FALSE);
    }

/*******************************************************************************
*
* flFitInSocketWindow - check whether the flash array fits in the socket window
*
* This routine checks whether the flash array fits in the socket window.
*
* RETURNS: A chip size guaranteed to fit in the socket window.
*
* ERRNO
*/

long int flFitInSocketWindow
    (
    long int chipSize,		/* size of single physical chip in bytes */
    int      interleaving,	/* flash chip interleaving (1,2,4 etc) */
    long int windowSize		/* socket window size in bytes */
    )
    {
    if (chipSize*interleaving > windowSize) /* doesn't fit in socket window */
        {
        int  roundedSizeBits;

        /* fit chip in the socket window */
        chipSize = windowSize / interleaving;

        /* round chip size at powers of 2 */
        for (roundedSizeBits = 0; (0x1L << roundedSizeBits) <= chipSize;
             roundedSizeBits++)
	    ;

        chipSize = (0x1L << (roundedSizeBits - 1));
        }

    return (chipSize);
    }

/*******************************************************************************
*
* sysTffsCpy - copy memory from one location to another
*
* This routine copies <size> characters from the object pointed
* to by <source> into the object pointed to by <destination>. If copying
* takes place between objects that overlap, the behavior is undefined.
*
* INCLUDE FILES: string.h
*
* RETURNS: A pointer to <destination>.
*
* ERRNO
*
* \NOMANUAL
*/

void * sysTffsCpy
    (
    void *       destination,   /* destination of copy */
    const void * source,        /* source of copy */
    size_t       size           /* size of memory to copy */
    )
    {
    bcopy ((char *) source, (char *) destination, (size_t) size);
    return (destination);
    }

/*******************************************************************************
*
* sysTffsSet - set a block of memory
*
* This routine stores <c> converted to an `unsigned char' in each of the
* elements of the array of `unsigned char' beginning at <m>, with size <size>.
*
* INCLUDE FILES: string.h
*
* RETURNS: A pointer to <m>.
*
* ERRNO
*
* \NOMANUAL
*/

void * sysTffsSet
    (
    void * m,                   /* block of memory */
    int    c,                   /* character to store */
    size_t size                 /* size of memory */
    )
    {
    bfill ((char *) m, (int) size, c);
    return (m);
    }


/*******************************************************************************
*
* flDelayLoop - consume the specified time
*
* This routine consumes the specified time.
*
* RETURNS: N/A
*
* ERRNO
*/

void flDelayLoop 
    (
    int cycles			/* loop count to be consumed */
    )
    {
      volatile int counter;
      for (counter = 0; counter < cycles; counter++);
    }

/*******************************************************************************
*
* sysTffsFormat - format the flash memory above an offset
*
* This routine formats the flash memory.  Because this function defines
* the symbolic constant, HALF_FORMAT, the lower half of the specified flash
* memory is left unformatted.  If the lower half of the flash memory was
* previously formated by TrueFFS, and you are trying to format the upper half,
* you need to erase the lower half of the flash memory before you format the
* upper half.  To do this, you could use:
* \cs
* tffsRawio(0, 3, 0, 8)
* \ce
* The first argument in the tffsRawio() command shown above is the TrueFFS
* drive number, 0.  The second argument, 3, is the function number (also
* known as TFFS_PHYSICAL_ERASE).  The third argument, 0, specifies the unit
* number of the first erase unit you want to erase.  The fourth argument, 8,
* specifies how many erase units you want to erase.
*
* RETURNS: OK, or ERROR if it fails.
*
* ERRNO
*/

STATUS sysTffsFormat 
    (
    int devNo
    )
    {
    STATUS status =0;
    int currentPriority;
    tffsDevFormatParams params = 
	{
#undef  HALF_FORMAT
#ifdef  HALF_FORMAT
	{0x100000l, 99, 1, 0x10000l, NULL, {0,0,0,0}, NULL, 2, 0, NULL},
#else
	{0x000000l, 99, 1, 0x10000l, NULL, {0,0,0,0}, NULL, 2 , 0, NULL},
#endif  /* HALF_FORMAT */
	FTL_FORMAT_IF_NEEDED 
	};

    if (devNo > 1)
       printf ("Maximum flash devices are 2, the devNo is %d\n", devNo); 

    /* Don't do this from an ISR, please. */
    if (INT_CONTEXT ())
        {
        logMsg("Can't call sysTffsFormat() from interrupt level!\n",1,2,3,4,5,6);
        return flIncomplete;
        }

    /* This takes a while -- lower our priority to let somebody else run */
    taskPriorityGet(taskIdSelf(), &currentPriority);
    taskPrioritySet(taskIdSelf(), 250);


    /* Format them */
    status = tffsDevFormat (devNo, (int)&params);

    /* Restore old priority */
    taskPrioritySet(taskIdSelf(), currentPriority);

    return (status);
    }


#endif /* INCLUDE_TFFS */


