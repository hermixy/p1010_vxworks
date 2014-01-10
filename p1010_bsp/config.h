/* config.h - Freescale MPC8548 BSP (8548) configuration file */

/*
 * Copyright (c) 2005-2007 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01y,21aug07,mmi  remove legacy power management define
01x,07aug07,dtr  Update for latest RIO driver.
01w,17jul07,vik  removed INCLUDE_AUX_CLK
01v,17jul07,vik  added vxBus Timer driver and Timer Library
01u,11jul07,d_l  Change AUX_CLK_RATE defines.(WIND00063974)
01t,03jul07,wap  Switch to VxBus TSEC drivers
01s,26jun07,pmr  change INCLUDE_PCI to INCLUDE_PCI_BUS
01r,30may07,vik  added INCLUDE_VXB_CMDLINE macro
01q,14may07,vik  added INCLUDE_DMA_SYS
01p,20apr07,pmr  VxBus PCI and intCtlr
01o,23mar07,pmr  fix bootapp support
01n,19dec06,rlg  Updates for NOR
01m,13dec06,pmr  compatibility with IPNET
01l,13dec06,pmr  shared memory cleanup, added CDS_SYSTEM1_2
01k,30aug06,dtr  Support latest silicon and board revisions.
01j,22nov06,d_c  Move MAX_MAC_DEVS and ENET_DEFAULT from sysNet.h to config.h
01i,24aug06,pmr  use CCSR driver
01h,01may06,dtr  Default boot device name changed. SPR#102448.
01g,21feb06,dtr  Use HEND drivers by default.
01f,03feb06,wap  Add INCLUDE_PARAM_SYS for VxBus
01e,26jan06,dtr  LBC_CS3_SIZE added.
01d,11jan06,dtr  define INCUDE_PCI_AUTOCONF.
01c,11aug05,pcm  TFFS no longer depends upon DosFs
01b,20jul05,dtr  Minor changes .
01a,04jun05,dtr  Modify from cds85xx/config.h/01b
*/

#ifndef	INCconfigh
#define	INCconfigh

#ifdef __cplusplus
    extern "C" {
#endif /* __cplusplus */

#define BSP_VER_1_1     1
#define BSP_VER_1_2     1
#define BSP_VERSION     "2.0"
#define BSP_REV         "/4"
           
/* Define Clock Speed and source  */

#define	FREQ_33_MHZ	 33333333
#define	FREQ_66_MHZ	 66666666
#define	FREQ_100_MHZ	 99999999
#define	FREQ_133_MHZ	133333333
#define	FREQ_266_MHZ	266666666
#define	FREQ_333_MHZ	333333333
#define	FREQ_533_MHZ	533333333


#undef CDS_SYSTEM2		/* Rev 2 silicon only tested in Arcadia 3.1 */
#undef  CDS_SYSTEM1_2		/* Rev 1 silicon in Arcadia 3.1 motherboard */

#ifdef CDS_SYSTEM2
# define REV2_SILICON
# define ARCADIA_X31
# define REV13_CARRIER
#else
# define REV1X_SILICON
# ifdef CDS_SYSTEM1_2
#  define ARCADIA_X31
# else
#  define ARCADIA_X3
# endif
# define REV12_CARRIER
#endif

#ifdef ARCADIA_X31
#error 66
#define	OSCILLATOR_FREQ	FREQ_66_MHZ
#else
			/*Old value is 33_MHZ*/
#define	OSCILLATOR_FREQ	FREQ_66_MHZ
#endif

/* DDR will work only for 400/533Mhz at the moment */
/* These ratios are tested in bootrom for correct init */
/* boot sector too small for 333 ddr init as well so ifdef'd out for now. */

#if (OSCILLATOR_FREQ == FREQ_33_MHZ)
#define PLAT_RATIO_533_MHZ 16
#define PLAT_RATIO_400_MHZ 12
#define PLAT_RATIO_333_MHZ 8 /* Unsupported */
#endif
#if (OSCILLATOR_FREQ == FREQ_66_MHZ)
#define PLAT_RATIO_533_MHZ 8
#define PLAT_RATIO_400_MHZ 6
#define PLAT_RATIO_333_MHZ 4 /* Unsupported */
#endif

/* possibly this is not supported check your DDR undefined for safety */
#define INCLUDE_DDR_ECC
#define DEFAULT_SYSCLKFREQ FREQ_66_MHZ

#undef FORCE_DEFAULT_FREQ /* Use to force freq used with DUART/Timers etc */

/* This value is the 60x bus-assigned SDRAM Refresh Timer PSRT setting */
#define	LSRT_VALUE	0x20

/*
 * This value is the setting for the MPTPR[PTP] Refresh timer prescaler.
 * The value is dependent on the OSCILLATOR_FREQ value.  For other values
 * a conditionally compiled term must be created here for that OSCILLATOR_FREQ
 * value.
 *
 * BRGCLK_DIV_FACTOR
 * Baud Rate Generator division factor - 0 for division by 1
 *					 1 for division by 16
 */

#define	DIV_FACT_1	0
#define	DIV_FACT_16	1

/* 
 * Assume 533MHz CCB with local bus clk ratio of 8 
 */
#define	TPR			0x0000

#include <configAll.h>

#include "cds8548.h"

    /* VxBus is required */

#define INCLUDE_VXBUS

#define INCLUDE_VXBUS_INIT
#define INCLUDE_HWMEM_ALLOC
#define INCLUDE_VXBUS_ACTIVATE
#define INCLUDE_PARAM_SYS
#define INCLUDE_PLB_BUS
/*#define INCLUDE_ETSEC_VXB_END*/
#define INCLUDE_DMA_SYS
#undef  INCLUDE_TSEC_VXB_END
/*#define INCLUDE_MII_BUS*/
#define INCLUDE_VXB_CMDLINE

#ifdef REV13_CARRIER
#define INCLUDE_MV88E1X11PHY
#else
/*#define INCLUDE_VSC82XXPHY*/
#endif /* REV13_CARRIER */

    /* RAPIDIO supports only point to point shared memory support
      This includes TIPC and SM objects */

#ifdef INCLUDE_RAPIDIO_BUS
#define INCLUDE_SM_COMMON
#define INCLUDE_M85XX_RAPIDIO
#define INCLUDE_M85XX_CPU
#define DRV_RESOURCE_M85XXCCSR
#define INCLUDE_M85XX_RIO_SM_CFG
#define INCLUDE_VXBUS_SM_SUPPORT
#define RAPIDIO_BUS_STATIC_TABLE
#define VXBUS_TABLE_CONFIG
#endif /* INCLUDE_RAPIDIO_BUS */

/* VxBus GEI driver */
#ifdef INCLUDE_GEI825XX_VXB_END
# define INCLUDE_PCI_BUS
# define INCLUDE_GENERICPHY
#endif /* INCLUDE_GEI825XX_VXB_END */

#define DRV_INTCTLR_EPIC
#define DRV_INTCTLR_PPC
#define INCLUDE_INTCTLR_LIB

/* Timer Driver */
#define INCLUDE_TIMER_SYS
#define DRV_TIMER_M85XX

#define DRV_SIO_NS16550
#define INCLUDE_SIO_UTILS
/*#undef NUM_TTY
#define NUM_TTY 1*/

/*#define INCLUDE_END*/
#define HWMEM_POOL_SIZE 50000

#define INCLUDE_SHELL
#ifdef  INCLUDE_SHELL
  #define INCLUDE_SYM_TABLE
  #define INCLUDE_STANDALONE_SYM_TABLE
  #define INCLUDE_LOADER
  #define INCLUDE_UNLOADER
  #define INCLUDE_ELF
  #define INCLUDE_STARTUP_SCRIPT
#endif /* INCLUDE_SHELL */

/* other useful includes
#define INCLUDE_IFMEDIA
#define INCLUDE_VXBUS_SHOW
#define INCLUDE_SHOW_ROUTINES
#define INCLUDE_PCI_CFGSHOW
#define INCLUDE_ISR_OBJECTS
*/ 

/* Need LINKHDR extension to support FCB in ETSEC to 
 * reduce FCB insertion requiring it's own BD */
#undef MAX_LINKHDR_CFG
#define MAX_LINKHDR_CFG       32

#define WDT_RATE_MIN         (sysTimerClkFreq / (1 << 29))
#define WDT_RATE_MAX         (sysTimerClkFreq / (1 << 21))

#define DEFAULT_BOOT_LINE \
"motetsec(0,0)host:vxWorks h=192.168.0.1 e=192.168.0.2 u=vxworks pw=vxworks f=0x0"
/*#define INCLUDE_END*/
#undef INCLUDE_END

#define MAX_MAC_DEVS         2          /* two network devices (fcc, scc) */
#define ENET_DEFAULT         0x1EA00000 /* WR fixed MAC addr; see WR_ENETx */


/* MMU and CACHE */

#define INCLUDE_MMU_BASIC
#define USER_I_MMU_ENABLE
#define USER_D_MMU_ENABLE

#undef E500_L1_PARITY_RECOVERY

#ifdef E500_L1_PARITY_RECOVERY
  /* *** NOTE FOR PROJECT FACILITY USERS ***
   * Needs to use WRITETHROUGH, building with Project Facility must also
   * change USER_D_CACHE_MODE and USER_I_CACHE_MODE in Project Facility.
   */

# define CACHE_LIBRARY_MODE     CACHE_WRITETHROUGH
# define CAM_DRAM_CACHE_MODE    _MMU_TLB_ATTR_W
# define TLB_CACHE_MODE         VM_STATE_CACHEABLE_WRITETHROUGH

#else  /* E500_L1_PARITY_RECOVERY */

# define CACHE_LIBRARY_MODE     (CACHE_COPYBACK | CACHE_SNOOP_ENABLE)
# define CAM_DRAM_CACHE_MODE    _MMU_TLB_ATTR_M
# define TLB_CACHE_MODE         VM_STATE_CACHEABLE | VM_STATE_MEM_COHERENCY

#endif

#define INCLUDE_CACHE_SUPPORT 
#define USER_D_CACHE_ENABLE
#undef  USER_D_CACHE_MODE
#define USER_D_CACHE_MODE  (CACHE_LIBRARY_MODE)
#define USER_I_CACHE_ENABLE
#undef  USER_I_CACHE_MODE
#define USER_I_CACHE_MODE (CACHE_LIBRARY_MODE)

#define  INCLUDE_L2_CACHE
#undef   INCLUDE_L2_SRAM

  /* If E500_L1_PARITY_RECOVERY is not efined, use local BSP handler.
   * Works for L1 instr cache but not data cache.  Writethrough not needed.
   */  
#ifdef E500_L1_PARITY_RECOVERY

# if defined(INCLUDE_CACHE_SUPPORT) && defined(USER_I_CACHE_ENABLE)
#   if (defined(_WRS_VXWORKS_MAJOR) && (_WRS_VXWORKS_MAJOR >= 6))
#     define INCLUDE_L1_IPARITY_HDLR              /* VxWorks 6.x */
#   else  /* _WRS_VXWORKS_MAJOR */
#     define INCLUDE_L1_IPARITY_HDLR_INBSP        /* VxWorks 5.5.x */
#   endif /* _WRS_VXWORKS_MAJOR */
# endif  /* INCLUDE_CACHE_SUPPORT && USER_I_CACHE_ENABLE */

#endif  /* E500_L1_PARITY_RECOVERY */

#define INCLUDE_BRANCH_PREDICTION

#if ((defined(INCLUDE_L2_CACHE)) && (defined(INCLUDE_L2_SRAM)))
#define L2_CACHE_SIZE      L2SIZ_256KB
#define L2_SRAM_SIZE       L2SIZ_256KB
#elif ((defined(INCLUDE_L2_CACHE)) && (!defined(INCLUDE_L2_SRAM)))
#define L2_CACHE_SIZE      L2SIZ_512KB
#define L2_SRAM_SIZE       0         /* Not Used */
#else
#define L2_SRAM_SIZE       L2SIZ_512KB
#define L2_CACHE_SIZE      0         /* Not Used */
#endif

#define L2SRAM_ADDR        0x7FF80000
#define L2SRAM_WINDOW_SIZE 0x80000 

#ifdef INCLUDE_NFS
/* Default NFS parameters - constants may be changed here, variables
 * may be changed in usrConfig.c at the point where NFS is included.
 */
#define NFS_USER_ID             2001            /* dummy nfs user id */
#define NFS_GROUP_ID            100             /* dummy nfs user group id */
#define NFS_MAXPATH             255             /* max. file path length */
#endif /* INCLUDE_NFS */

/* Disable Support for SPE 64bit registers */

#define INCLUDE_SPE

/* TSEC is included */

/*#define INCLUDE_MOT_TSEC_END*/

#ifdef INCLUDE_MOT_TSEC_END
#define INCLUDE_PRIMARY_TSEC_END
#define INCLUDE_SECONDARY_TSEC_END
#undef INCLUDE_TERTIARY_TSEC_END
#undef INCLUDE_QUARTINARY_TSEC_END    
#define INCLUDE_END                   
#endif /* INCLUDE_MOT_TSEC_END */

/* Clock rates */

#define	SYS_CLK_RATE_MIN	1	/* minimum system clock rate */
#define	SYS_CLK_RATE_MAX	8000	/* maximum system clock rate */
#define	AUX_CLK_RATE_MIN	((CCB_FREQ / 16) / (1 << FIT_DIVIDER_TAP_21))
				/* minimum auxiliary clock rate -- 11HZ*/
#define	AUX_CLK_RATE_MAX	((CCB_FREQ / 16) / (1 << FIT_DIVIDER_TAP_10))	
				/* maximum auxiliary clock rate -- 24414HZ*/
#define AUX_CLK_RATE		((CCB_FREQ / 16) / (1 << FIT_DIVIDER_TAP_18))
				/* default auxiliary clock rate -- 95HZ*/

/* TrueFFS flash support */
#define INCLUDE_SHOW_ROUTINES
#ifdef  INCLUDE_TFFS
#define INCLUDE_SHOW_ROUTINES	/* show routines for system facilities*/
#endif  /* INCLUDE_TFFS */

/* Although the support for point to point has been added it is untested 
   with Serial RIO. SImilar was tested on parallel RIO */

#ifdef INCLUDE_RAPIDIO_BUS
/* RapidIO information */
#define RAPIDIO_REG_BASE 0xc0000
#define RAPIDIO_BASE   (CCSBAR + RAPIDIO_REG_BASE)
#define RAPIDIO_ADRS   0xc0000000
#define RAPIDIO_SIZE   0x10000000
#define RAPIDIO_BUS_ADRS 0x80000000
#define RAPIDIO_BUS_SIZE 0x10000000
#endif

/* PCI support is available just not defined by default */

#ifdef  INCLUDE_PCI_BUS

#define INCLUDE_PCI_BUS_AUTOCONF
#define DRV_PCIBUS_M85XX
#define DRV_RESOURCE_M85XXCCSR

#define CDS85XX_PCI_1_BUS       1
#define CDS85XX_PCI_2_BUS       2
#define CDS85XX_PCIEX_BUS       3

/* define this MACRO to enable PCI 2 */

#undef INCLUDE_CDS85XX_SECONDARY_PCI

/* define this MACRO to enable PCI Express */

#define  INCLUDE_CDS85XX_PCIEX
/*  cds85xx support dual PCI controllers */

/*

CPU Addr                                  PCI Addr ( PCI1 or PCI2)
PCI_LOCAL_MEM_BUS        -------------------------- PCI_MSTR_MEM_BUS
                         -                        - 
                         -                        -
PCI_LOCAL_MEM_BUS +      -------------------------- PCI_MSTR_MEM_BUS +
PCI_LOCAL_MEM_SIZE       -                        - PCI_MSTR_MEM_SIZE
                         -                        - 
                         -                        ----- PCI Bridge (for PCI1 only)
                         -                        -     configuration regs
                         -                        - 
CPU_PCI_MEM_ADRS  (PCI1) -------------------------- PCI_MEM_ADRS
CPU_PCI_MEM_ADRS2 (PCI2) -                        - PCI_MEM_ADRS2
CPU_PCI_MEM_ADRS3(PCIEX) -------------------------- PCI_MEM_ADRS3
                         -                        - 
CPU_PCI_MEMIO_ADRS       -------------------------- PCI_MEMIO_ADRS
CPU_PCI_MEMIO_ADRS2      -                        - PCI_MEMIO_ADRS2
CPU_PCI_MEMIO_ADRS3      -                        - PCI_MEMIO_ADRS3
                         -                        - 
CPU_PCI_IO_ADRS  (PCI1)  -------------------------- PCI_IO_ADRS
CPU_PCI_IO_ADRS2 (PCI2)  -                        - PCI_IO_ADRS2
CPU_PCI_IO_ADRS3 (PCIEX) -                        - PCI_IO_ADRS3
                         -                        -
CPU_PCI_IO_ADRS  (PCI1)+ -------------------------- PCI_IO_ADRS +
CPU_PCI_IO_ADRS2 (PCI2)+                            PCI_IO_ADRS2 +
CPU_PCI_IO_ADRS2 (PCI3)                             PCI_IO_ADRS3
CPU_PCI_IO_SIZE          -                        - PCI_IO_SIZE
                         -                        -
*/

/* PCI based addresses */

#define PCI_LAW_BASE             0x50000000       /* PCI LAW window */
#define PCI_LAW_SIZE             0x10000000       /* PCI LAW size   */

#define PCI_MEM_SIZE             0x04000000        /* 64 MB */
#define PCI_MEMIO_SIZE           0x04000000        /* 64 MB */
#define PCI_IO_SIZE              0x04000000        /* 64 MB */

#define PCI_MEM_ADRS             (PCI_LAW_BASE)                     
#define PCI_MEMIO_ADRS           (PCI_MEM_ADRS   + PCI_MEM_SIZE)    
#define PCI_IO_ADRS              (PCI_MEMIO_ADRS + PCI_MEMIO_SIZE)  

#ifdef INCLUDE_CDS85XX_SECONDARY_PCI

#define PCI2_LAW_BASE            0x58000000       /* PCI LAW window */
#define PCI2_LAW_SIZE            0x08000000       /* PCI LAW size   */

#define PCI_MEM_ADRS2            (PCI2_LAW_BASE)                     
#define PCI_MEMIO_ADRS2          (PCI_MEM_ADRS2   + PCI_MEM_SIZE)    
#define PCI_IO_ADRS2             (PCI_MEMIO_ADRS2 + PCI_MEMIO_SIZE)  

#endif /* INCLUDE_CDS85XX_SECONDARY_PCI */

#ifdef INCLUDE_CDS85XX_PCIEX

#define PCIEX_LAW_BASE            0x60000000       /* PCI LAW window */
#define PCIEX_LAW_SIZE            0x10000000       /* PCI LAW size   */

#define PCI_MEM_ADRS3            (PCIEX_LAW_BASE)                     
#define PCI_MEMIO_ADRS3          (PCI_MEM_ADRS3   + PCI_MEM_SIZE)    
#define PCI_IO_ADRS3             (PCI_MEMIO_ADRS3 + PCI_MEMIO_SIZE)  

#endif /* INCLUDE_CDS85XX_PCIEX */

#if (PCI_LAW_SIZE == 0x10000000)
#define  PCI_LAW_WIN_SZ          LAWAR_SIZE_256MB
#endif

#if (PCI2_LAW_SIZE == 0x10000000)
#define  PCI2_LAW_WIN_SZ         LAWAR_SIZE_256MB
#endif

#if (PCIEX_LAW_SIZE == 0x10000000)
#define  PCIEX_LAW_WIN_SZ         LAWAR_SIZE_256MB
#endif

#define PCI_MMU_TLB_SZ           _MMU_TLB_SZ_256M

#if (PCI_MEM_SIZE == 0x04000000)
#define PCI_MEM_SIZE_MASK        PCI_ATTR_WS_64M
#endif 

#if (PCI_MEMIO_SIZE == 0x04000000)
#define PCI_MEMIO_SIZE_MASK      PCI_ATTR_WS_64M
#endif

#if (PCI_IO_SIZE == 0x04000000)
#define PCI_IO_SIZE_MASK         PCI_ATTR_WS_64M
#endif

#define PCI_BRIDGE_PIMMR_BASE_ADRS  0x40000000

/* just 1:1 mapping */ 

/* PCI 1 */

#define CPU_PCI_MEM_ADRS          PCI_MEM_ADRS
#define CPU_PCI_MEMIO_ADRS        PCI_MEMIO_ADRS
#define CPU_PCI_IO_ADRS           PCI_IO_ADRS

/* PCI 2 */

#define CPU_PCI_MEM_ADRS2         PCI_MEM_ADRS2
#define CPU_PCI_MEMIO_ADRS2       PCI_MEMIO_ADRS2
#define CPU_PCI_IO_ADRS2          PCI_IO_ADRS2

/* PCI Express */

#define CPU_PCI_MEM_ADRS3         PCI_MEM_ADRS3
#define CPU_PCI_MEMIO_ADRS3       PCI_MEMIO_ADRS3
#define CPU_PCI_IO_ADRS3          PCI_IO_ADRS3

#define CPU_PCI_MEM_SIZE          PCI_MEM_SIZE 
#define CPU_PCI_MEMIO_SIZE        PCI_MEMIO_SIZE 
#define CPU_PCI_IO_SIZE           PCI_IO_SIZE

/* CPU from PCI bus */

#define PCI_MSTR_MEM_BUS           0x00000000
#define PCI_MSTR_MEM_SIZE          0x40000000 /* 1G */

/* CPU Address that is visible from PCI */

#define PCI_LOCAL_MEM_BUS         0x00000000
#define PCI_LOCAL_MEM_SIZE        PCI_MSTR_MEM_SIZE
#define PCI_LOCAL_MEM_SIZE_MASK   PCI_ATTR_WS_1G

#define INCLUDE_PCI_AUTOCONF

#ifndef PCI_CFG_TYPE
#   ifdef INCLUDE_PCI_AUTOCONF
#      define PCI_CFG_TYPE PCI_CFG_AUTO
#   else
#      define PCI_CFG_TYPE PCI_CFG_FORCE
#   endif /* INCLUDE_PCI_AUTOCONF */
#endif /* PCI_CFG_TYPE */

#endif /* INCLUDE_PCI_BUS */

/* Shared memory is set up for Serial RIO */
#if defined(INCLUDE_SM_COMMON)
#   define INCLUDE_SMEND
#   define INCLUDE_SM_NET
#   define INCLUDE_SM_NET_SHOW
#   define INCLUDE_SM_SEQ_ADDR
#   ifdef  STANDALONE
#          define STANDALONE_NET
#   endif  /* STANDALONE */
#   undef IPFORWARDING_CFG
#   define IPFORWARDING_CFG 1
#   define INCLUDE_IPATTACH
#   define INCLUDE_IFCONFIG
#   define INCLUDE_IPWRAP_IPPROTO
#   define INCLUDE_NET_BOOT_CONFIG
#endif /* defined(INCLUDE_SM_NET) */

/*
 * Changing SM_OFF_BOARD to TRUE also requires changing
 * SM_ANCHOR_ADRS and SM_MEM_ADRS appropriately.
 */

#define SM_OFF_BOARD    FALSE

#undef SM_TAS_TYPE
#define SM_TAS_TYPE SM_TAS_HARD

#ifndef _ASMLANGUAGE
IMPORT char* rioHostAdrs;

#undef  SM_ANCHOR_ADRS
#define SM_ANCHOR_ADRS  ((sysProcNumGet() == 0) ? \
        ((char*) (LOCAL_MEM_LOCAL_ADRS + SM_ANCHOR_OFFSET)) : \
        ((char*) ((UINT32)rioHostAdrs + SM_ANCHOR_OFFSET)))

#endif

#define SM_INT_TYPE		SM_INT_BUS  /* or SM_INT_NONE */

#define SM_MEM_ADRS		0x00010000	/* Start of actual SM region */
#define SM_MEM_SIZE		0x00070000
#define SM_OBJ_MEM_ADRS		(SM_MEM_ADRS+SM_MEM_SIZE) /* SM Objects pool */
#define SM_OBJ_MEM_SIZE		0x00040000

#define SM_INT_ARG1   46 /*EPIC_SR_IN_DB1_INT_VEC*/
#define SM_INT_ARG2   46 /*EPIC_SR_IN_DB1_INT_VEC*/
#define SM_INT_ARG3   1


#define SM_TIPC_ADRS_DEFAULT    ((int) SM_OBJ_MEM_ADRS + SM_OBJ_MEM_SIZE)
#define SM_TIPC_ADRS            SM_TIPC_ADRS_DEFAULT
#define SM_TIPC_SIZE_DEFAULT    0x00020000
#define SM_TIPC_SIZE            SM_TIPC_SIZE_DEFAULT /* SM TIPC pool size  */


/*
 * Set the Carrier Card's SW2[12]=00 for the following configuration,
 * the bootrom would be in the last 1 MB of flash0, and UBOOT would still 
 * be in the flash 1.
 */  

#define FLASH_WINDOW_SIZE               0x00800000 
#define CDS85XX_FLASH_RESERVED_SIZE     0x00100000

#ifdef INCLUDE_TFFS

/* Second flash for TFFS support */

#undef  INCLUDE_CDS85XX_SECOND_TFFS_FLASH
#endif /* INCLUDE_TFFS */

/* LBC CS0 - flash 0 - default for bootrom */ 

/*#define FLASH_BASE_ADRS                 0xff800000*/
#define FLASH_BASE_ADRS									0xef000000
#define FLASH_ADRS_MASK                 0xff800000

/* LBC CS1 - flash 1 - default for UBOOT */ 

/*#define FLASH1_BASE_ADRS                0xff000000*/
#define FLASH1_BASE_ADRS								0xee000000
#define FLASH1_ADRS_MASK                0xff800000

#define TOTAL_FLASH_SIZE                0x1000000
/* LBC CS2 - SDRAM */

#define INCLUDE_LBC_SDRAM

/* NOTE this should match the LAWAR SIZE in romInit for the chosen SDRAM */

#define LOCAL_MEM_SIZE2            0x4000000      /* 64 Mbyte memory available */
#define LOCAL_MEM_LOCAL_ADRS2      0xf0000000     /* Base of RAM */
#define LBC_SDRAM_LOCAL_SIZE_MASK  0xfc000000
#define LBC_SDRAM_LOCAL_ADRS       LOCAL_MEM_LOCAL_ADRS2
#define LBC_SDRAM_LOCAL_SIZE       LOCAL_MEM_SIZE2

/* LBC CS3 - nvram, cadmus, ATM phy */

#define INCLUDE_LBC_CS3
#undef INCLUDE_NV_RAM

#ifdef INCLUDE_LBC_CS3
#define INCLUDE_NV_RAM
#define LBC_CS3_LOCAL_ADRS       0xf7000000
#define LBC_CS3_LOCAL_SIZE_MASK  0xff000000
#define LBC_CS3_SIZE             0x01000000
#endif

/* NVRAM configuration */
#ifdef  INCLUDE_NV_RAM
#   define NV_RAM_ADRS          LBC_CS3_LOCAL_ADRS 
#   undef  NV_RAM_SIZE
#   define NV_RAM_SIZE          (0x2000 - 0x10)  /* 8KB - 16 */
#   define NV_RAM_INTRVL        1
#   undef  NV_BOOT_OFFSET
#   define NV_BOOT_OFFSET       0
#   define NV_MAC_ADRS_OFFSET   0x200
#else
#   define NV_RAM_SIZE 0
#   define NV_RAM_ADRS 0
#endif  /* INCLUDE_NV_RAM */

/* Memory addresses */

#define INCLUDE_DDR_SDRAM


/* NOTE this should match the LAWAR SIZE in romInit for the chosen SDRAM */

#define LOCAL_MEM_SIZE          0x10000000      /* 256/512 Mbyte memory available */
#define LOCAL_MEM_LOCAL_ADRS    0x00000000      /* Base of RAM */

#define DDR_SDRAM_LOCAL_ADRS       LOCAL_MEM_LOCAL_ADRS
#define DDR_SDRAM_LOCAL_SIZE       LOCAL_MEM_SIZE
#define DDR_SDRAM_LOCAL_ADRS_END   (DDR_SDRAM_LOCAL_ADRS + DDR_SDRAM_LOCAL_SIZE)

#ifdef INCLUDE_MMU_BASIC

#define INCLUDE_AIM_MMU_CONFIG
#ifndef BOOTAPP
#define INCLUDE_MMU_OPTIMIZE 
#endif

#define INCLUDE_AIM_MMU_SHOW

#define INCLUDE_AIM_MMU_MEM_POOL_CONFIG

/* 
 * The following parameters are to configure initial memory usage for 
 * page table and region tables and in event of running out the increment 
 * of memory allocation and is specified as a number of MMU pages (4KByte
 * blocks). 
 */
#define AIM_MMU_INIT_PT_NUM 0x40
#define AIM_MMU_INIT_PT_INCR 0x20
#define AIM_MMU_INIT_RT_NUM 0x10
#define AIM_MMU_INIT_RT_INCR 0x10

/* This write protects the page tables */
#define INCLUDE_AIM_MMU_PT_PROTECTION

/* 
 * INCLUDE_LOCK_TEXT_SECTION Requires use of CAM entries which can 
 * possibly be already used in sysStaticTlbDesc. Also the larger the 
 * page size that can be used the less CAM entries required so aligning 
 * RAM_LOW_ADRS on a large page size boundary is usually necessary.
 * Locking the text section should increase performance because no 
 * Instruction TLB misses are taken within the text section.
 */

#ifndef BOOTAPP
#define INCLUDE_LOCK_TEXT_SECTION     
#endif

#undef INCLUDE_PAGE_SIZE_OPTIMIZATION /* Not available for 85XX */

#endif /* INCLUDE_MMU_BASIC */

#define INCLUDE_CTORS_DTORS

/* Using software FP support. Athough task based 32 bit HW_FP is allowed 
 * no optimised libraries are available. The kernel doesn't execute any hw 
 * fp instructions */

#undef  INCLUDE_HW_FP
#undef  INCLUDE_PPC_FPU
#define INCLUDE_SW_FP

/*
 * The constants ROM_XXX_ADRS, ROM_SIZE, and RAM_XXX_ADRS are defined
 * in both config.h and Makefile.  All definitions for these constants
 * must be identical.
 */
 
#ifndef RAM_LOW_ADRS
#define	RAM_LOW_ADRS		0x00100000
#endif  /* RAM_LOW_ADRS */

#ifndef RAM_HIGH_ADRS
#define	RAM_HIGH_ADRS		0x01000000
#endif  /* RAM_HIGH_ADRS */

#define ROM_TEXT_ADRS 0xFFF00100
#define ROM_BASE_ADRS 0xFFF00000
#define ROM_SIZE      0x00100000

#define USER_RESERVED_MEM 0x000000

#ifdef __cplusplus
    }
#endif /* __cplusplus */

#endif  /* INCconfigh */

#if defined(PRJ_BUILD)
    #include "prjParams.h"
#endif /* PRJ_BUILD */
