/* hwconf.c - Hardware configuration support module */

/*
 * Copyright (c) 2006-2007 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------
01m,07aug07,dtr  Update for latest RIO driver.
01l,08aug07,h_k  added LAWAR_ENABLE and LAWBAR_ADRS_SHIFT to
                 m85xxLawBarResources[].
01k,06jul07,d_l  Correct DUART2 interrupt number.(WIND00095933)
01j,04jul07,vik  added m85xx Timer driver resources
01i,02jul07,wap  Switch to VxBus TSEC drivers
01h,14jun07,pmr  EPIC regbase change
01g,20apr07,pmr  VxBus PCI and intCtlr
01d,07sep06,dtr  Support Etsec 3 & 4 in RGMII mode.
01f,22sep06,mze  added SM_MAX_PKTS and SM_PKTS_SIZE for WIND00058841
01e,07sep06,dtr  Support Etsec 3 & 4 in RGMII mode.
01d,24aug06,pmr  Use CCSR driver.
01c,09mar06,wap  Allow either mottsec or motetsec driver to be used
                 (SPR #118829)
01b,07feb06,wap  Add VxBus parameter table
01a,16jan06,dtr  written.
*/

#include <vxWorks.h>
#include <vxBusLib.h>
#include <hwif/vxbus/vxBus.h>
#include <hwif/vxbus/vxbPlbLib.h>
#include <hwif/vxbus/hwConf.h>
#include <../src/hwif/h/vxbus/vxbRapidIO.h>
#include <../src/hwif/h/mii/mv88E1x11Phy.h>
#include <hwif/util/vxbParamSys.h>
#include <config.h>
#include <drv/pci/pciConfigLib.h>
#include <drv/pci/pciAutoConfigLib.h>
#include <drv/pci/pciIntLib.h>
#include <hwif/vxbus/vxbIntrCtlr.h>
#include <hwif/intCtlr/vxbEpicIntCtlr.h>
#include "mot85xxPci.h"
#include "sysDuart.h"

#define XTSEC_NAME "mottsec"
#ifdef INCLUDE_ETSEC_VXB_END
#  undef  XTSEC_NAME
#  define XTSEC_NAME "motetsec"
#endif /* INCLUDE_ETSEC_VXB_END */

/*
 * On the cds8548 board, PHYs are physically wired according
 * to the following table:
 *
 * 		Data port pins	Management port pins	MII address
 *		--------------	--------------------	-----------
 * PHY0:	TSEC0		TSEC0			0
 * PHY1:	TSEC1		TSEC0			1
 * PHY2:	TSEC2		TSEC0			2
 * PHY3:	TSEC3		TSEC0			3
 *
 * The tricky part is that both PHYs have their management pins
 * connected to TSEC0. The VxBus TSEC driver allows us to specify
 * the name of the device that provides PHY management support.
 * This device is "mottsec0" in all cases. We also specify the
 * "phyAddr" resource for each device, which is set according
 * to the MII address in the table above.
 */

const struct hcfResource tsecVxbEnd0Resources[] = {
    { "regBase",	HCF_RES_INT,	{ (void *)(CCSBAR + 0x24000) } },
    { "intr0",		HCF_RES_INT,	{ (void *)EPIC_TSEC1TX_INT_VEC } },
    { "intr0Level",	HCF_RES_INT,	{ (void *)EPIC_TSEC1TX_INT_VEC } },
    { "intr1",		HCF_RES_INT,	{ (void *)EPIC_TSEC1RX_INT_VEC } },
    { "intr1Level",	HCF_RES_INT,	{ (void *)EPIC_TSEC1RX_INT_VEC } },
    { "intr2",		HCF_RES_INT,	{ (void *)EPIC_TSEC1ERR_INT_VEC } },
    { "intr2Level",	HCF_RES_INT,	{ (void *)EPIC_TSEC1ERR_INT_VEC } },
    { "phyAddr",	HCF_RES_INT,	{ (void *)0 } },
    { "miiIfName",	HCF_RES_STRING,	{ (void *)XTSEC_NAME } },
    { "miiIfUnit",	HCF_RES_INT,	{ (void *)0 } }
};
#define tsecVxbEnd0Num NELEMENTS(tsecVxbEnd0Resources)

const struct hcfResource tsecVxbEnd1Resources[] = {
    { "regBase",	HCF_RES_INT,	{ (void *)(CCSBAR + 0x25000) } },
    { "intr0",		HCF_RES_INT,	{ (void *)EPIC_TSEC2TX_INT_VEC } },
    { "intr0Level",	HCF_RES_INT,	{ (void *)EPIC_TSEC2TX_INT_VEC } },
    { "intr1",		HCF_RES_INT,	{ (void *)EPIC_TSEC2RX_INT_VEC } },
    { "intr1Level",	HCF_RES_INT,	{ (void *)EPIC_TSEC2RX_INT_VEC } },
    { "intr2",		HCF_RES_INT,	{ (void *)EPIC_TSEC2ERR_INT_VEC } },
    { "intr2Level",	HCF_RES_INT,	{ (void *)EPIC_TSEC2ERR_INT_VEC } },
    { "phyAddr",	HCF_RES_INT,	{ (void *)1 } },
    { "miiIfName",	HCF_RES_STRING,	{ (void *)XTSEC_NAME } },
    { "miiIfUnit",	HCF_RES_INT,	{ (void *)0 } }
};
#define tsecVxbEnd1Num NELEMENTS(tsecVxbEnd1Resources)

const struct hcfResource tsecVxbEnd2Resources[] = {
    { "regBase",	HCF_RES_INT,	{ (void *)(CCSBAR + 0x26000) } },
    { "intr0",		HCF_RES_INT,	{ (void *)EPIC_TSEC3TX_INT_VEC } },
    { "intr0Level",	HCF_RES_INT,	{ (void *)EPIC_TSEC3TX_INT_VEC } },
    { "intr1",		HCF_RES_INT,	{ (void *)EPIC_TSEC3RX_INT_VEC } },
    { "intr1Level",	HCF_RES_INT,	{ (void *)EPIC_TSEC3RX_INT_VEC } },
    { "intr2",		HCF_RES_INT,	{ (void *)EPIC_TSEC3ERR_INT_VEC } },
    { "intr2Level",	HCF_RES_INT,	{ (void *)EPIC_TSEC3ERR_INT_VEC } },
    { "phyAddr",	HCF_RES_INT,	{ (void *)2 } },
    { "miiIfName",	HCF_RES_STRING,	{ (void *)XTSEC_NAME } },
    { "miiIfUnit",	HCF_RES_INT,	{ (void *)0 } },
};
#define tsecVxbEnd2Num NELEMENTS(tsecVxbEnd2Resources)

const struct hcfResource tsecVxbEnd3Resources[] = {
    { "regBase",	HCF_RES_INT,	{ (void *)(CCSBAR + 0x27000) } },
    { "intr0",		HCF_RES_INT,	{ (void *)EPIC_TSEC4TX_INT_VEC } },
    { "intr0Level",	HCF_RES_INT,	{ (void *)EPIC_TSEC4TX_INT_VEC } },
    { "intr1",		HCF_RES_INT,	{ (void *)EPIC_TSEC4RX_INT_VEC } },
    { "intr1Level",	HCF_RES_INT,	{ (void *)EPIC_TSEC4RX_INT_VEC } },
    { "intr2",		HCF_RES_INT,	{ (void *)EPIC_TSEC4ERR_INT_VEC } },
    { "intr2Level",	HCF_RES_INT,	{ (void *)EPIC_TSEC4ERR_INT_VEC } },
    { "phyAddr",	HCF_RES_INT,	{ (void *)3 } },
    { "miiIfName",	HCF_RES_STRING,	{ (void *)XTSEC_NAME } },
    { "miiIfUnit",	HCF_RES_INT,	{ (void *)0 } },
};
#define tsecVxbEnd3Num NELEMENTS(tsecVxbEnd3Resources)

#ifdef INCLUDE_PCI_BUS

IMPORT STATUS sysPciAutoconfigInclude(PCI_SYSTEM *, PCI_LOC *, UINT);
IMPORT UCHAR sysPciAutoconfigIntrAssign(PCI_SYSTEM *, PCI_LOC *, UCHAR);

const struct hcfResource m85xxPci0Resources[] = {
    { "regBase", HCF_RES_INT, { (void *)PCI_CFG_ADR_REG } },
    { "mem32Addr", HCF_RES_ADDR, { (void *)PCI_MEM_ADRS } },
    { "mem32Size", HCF_RES_INT, { (void *)PCI_MEM_SIZE } },
    { "memIo32Addr", HCF_RES_ADDR, { (void *)PCI_MEMIO_ADRS } },
    { "memIo32Size", HCF_RES_INT, { (void *)PCI_MEMIO_SIZE } },
    { "io32Addr", HCF_RES_ADDR, { (void *)PCI_IO_ADRS } },
    { "io32Size", HCF_RES_INT, { (void *)PCI_IO_SIZE } },
    { "fbbEnable", HCF_RES_INT, { (void *)TRUE } },
    { "cacheSize", HCF_RES_INT, { (void *)(_CACHE_ALIGN_SIZE / 4) } },
    { "maxLatAllSet", HCF_RES_INT, { (void *)PCI_LAT_TIMER } },
    { "autoIntRouteSet", HCF_RES_INT, { (void *)TRUE } },
    { "includeFuncSet", HCF_RES_ADDR, { (void *)sysPciAutoconfigInclude } },
    { "intAssignFuncSet", HCF_RES_ADDR, {(void *)sysPciAutoconfigIntrAssign }},
    /* non vxbPciAutoConfig() values */
    { "pimmrBase", HCF_RES_ADDR, { (void *)PCI_BRIDGE_PIMMR_BASE_ADRS } },
    { "lclMemAddr", HCF_RES_ADDR, { (void *)LOCAL_MEM_LOCAL_ADRS } },
    { "lclMemMapSize", HCF_RES_INT, { (void *)(512 * 1024 * 1024) } },
    { "mstrMemBus", HCF_RES_ADDR, { (void *)PCI_MSTR_MEM_BUS } },

    { "pciConfigMechanism",HCF_RES_INT, { (void *)(0)}},
    { "maxBusSet", HCF_RES_INT, { (void *)3 } },
    /* LAWBAR details */
    /* Window Attributes - Defaults to 8540 type if none given */
    { "owAttrMem",HCF_RES_INT, { (void *)(PCI_WINDOW_ENABLE_BIT | PCI_OUT_ATTR_RTT_MEM |  PCI_OUT_ATTR_WTT_MEM) } },
    { "owAttrMemIo", HCF_RES_INT, { (void *)(PCI_WINDOW_ENABLE_BIT | PCI_OUT_ATTR_RTT_MEM |  PCI_OUT_ATTR_WTT_MEM) } },
    { "owAttrIo", HCF_RES_INT, { (void *)(PCI_WINDOW_ENABLE_BIT | PCI_OUT_ATTR_RTT_IO |  PCI_OUT_ATTR_WTT_IO) } },
    { "iwAttr", HCF_RES_INT, { (void *)(PCI_WINDOW_ENABLE_BIT | PCI_PREFETCHABLE| PCI_IN_ATTR_RTT_LM_READ_SNOOP | PCI_IN_ATTR_RTT_LM_WRITE_SNOOP | PCI_IN_ATTR_TGI_LM) } },
    { "singleLawBar", HCF_RES_INT, { (void *)(TRUE)}},
    { "singleLawBarSize",HCF_RES_INT, { (void *)(0x10000000)}},
    { "tgtIf",HCF_RES_INT, { (void *)(LAWAR_TGTIF_PCI)} },
    { "autoConfig",HCF_RES_INT, { (void *)(TRUE)}}

};
#define m85xxPci0Num NELEMENTS(m85xxPci0Resources)

#ifdef INCLUDE_CDS85XX_SECONDARY_PCI
IMPORT STATUS sysPci2AutoconfigInclude(PCI_SYSTEM *, PCI_LOC *, UINT);
IMPORT UCHAR sysPci2AutoconfigIntrAssign(PCI_SYSTEM *, PCI_LOC *, UCHAR);

const struct hcfResource m85xxPci1Resources[] = {
    { "regBase", HCF_RES_INT, { (void *)PCI2_CFG_ADR_REG } },
    { "mem32Addr", HCF_RES_ADDR, { (void *)PCI_MEM_ADRS2 } },
    { "mem32Size", HCF_RES_INT, { (void *)PCI_MEM_SIZE } },
    { "memIo32Addr", HCF_RES_ADDR, { (void *)PCI_MEMIO_ADRS2 } },
    { "memIo32Size", HCF_RES_INT, { (void *)PCI_MEMIO_SIZE } },
    { "io32Addr", HCF_RES_ADDR, { (void *)PCI_IO_ADRS2 } },
    { "io32Size", HCF_RES_INT, { (void *)PCI_IO_SIZE } },
    { "fbbEnable", HCF_RES_INT, { (void *)TRUE } },
    { "cacheSize", HCF_RES_INT, { (void *)(_CACHE_ALIGN_SIZE / 4) } },
    { "maxLatAllSet", HCF_RES_INT, { (void *)PCI_LAT_TIMER } },
    { "autoIntRouteSet", HCF_RES_INT, { (void *)TRUE } },
    { "includeFuncSet", HCF_RES_ADDR, { (void *)sysPci2AutoconfigInclude } },
    { "intAssignFuncSet", HCF_RES_ADDR, {(void *)sysPci2AutoconfigIntrAssign }},
    /* non vxbPciAutoConfig() values */
    { "pimmrBase", HCF_RES_ADDR, { (void *)PCI_BRIDGE_PIMMR_BASE_ADRS } },
    { "lclMemAddr", HCF_RES_ADDR, { (void *)LOCAL_MEM_LOCAL_ADRS } },
    { "lclMemMapSize", HCF_RES_INT, { (void *)(512 * 1024 * 1024) } },
    { "mstrMemBus", HCF_RES_ADDR, { (void *)PCI_MSTR_MEM_BUS } },

    { "pciConfigMechanism",HCF_RES_INT, { (void *)(0)}},
    { "maxBusSet", HCF_RES_INT, { (void *)3 } },
    /* LAWBAR details */
    /* Window Attributes - Defaults to 8540 type if none given */
    { "owAttrMem",HCF_RES_INT, { (void *)(PCI_WINDOW_ENABLE_BIT | PCI_OUT_ATTR_RTT_MEM |  PCI_OUT_ATTR_WTT_MEM) } },
    { "owAttrMemIo", HCF_RES_INT, { (void *)(PCI_WINDOW_ENABLE_BIT | PCI_OUT_ATTR_RTT_MEM |  PCI_OUT_ATTR_WTT_MEM) } },
    { "owAttrIo", HCF_RES_INT, { (void *)(PCI_WINDOW_ENABLE_BIT | PCI_OUT_ATTR_RTT_IO |  PCI_OUT_ATTR_WTT_IO) } },
    { "iwAttr", HCF_RES_INT, { (void *)(PCI_WINDOW_ENABLE_BIT | PCI_PREFETCHABLE| PCI_IN_ATTR_RTT_LM_READ_SNOOP | PCI_IN_ATTR_RTT_LM_WRITE_SNOOP | PCI_IN_ATTR_TGI_LM) } },
    { "singleLawBar", HCF_RES_INT, { (void *)(TRUE)}},
    { "singleLawBarSize",HCF_RES_INT, { (void *)(0x10000000)}},
    { "tgtIf",HCF_RES_INT, { (void *)(LAWAR_TGTIF_PCI2)} },
    { "autoConfig",HCF_RES_INT, { (void *)(TRUE)}}

};
#define m85xxPci1Num NELEMENTS(m85xxPci1Resources)
#endif /* INCLUDE_CDS85XX_SECONDARY_PCI */

#ifdef INCLUDE_CDS85XX_PCIEX
IMPORT STATUS sysPci3AutoconfigInclude(PCI_SYSTEM *, PCI_LOC *, UINT);
IMPORT UCHAR sysPci3AutoconfigIntrAssign(PCI_SYSTEM *, PCI_LOC *, UCHAR);

const struct hcfResource m85xxPci2Resources[] = {
    { "regBase", HCF_RES_INT, { (void *)PCIEX_CFG_ADR_REG } },
    { "mem32Addr", HCF_RES_ADDR, { (void *)PCI_MEM_ADRS3 } },
    { "mem32Size", HCF_RES_INT, { (void *)PCI_MEM_SIZE } },
    { "memIo32Addr", HCF_RES_ADDR, { (void *)PCI_MEMIO_ADRS3 } },
    { "memIo32Size", HCF_RES_INT, { (void *)PCI_MEMIO_SIZE } },
    { "io32Addr", HCF_RES_ADDR, { (void *)PCI_IO_ADRS3 } },
    { "io32Size", HCF_RES_INT, { (void *)PCI_IO_SIZE } },
    { "fbbEnable", HCF_RES_INT, { (void *)TRUE } },
    { "cacheSize", HCF_RES_INT, { (void *)(_CACHE_ALIGN_SIZE / 4) } },
    { "maxLatAllSet", HCF_RES_INT, { (void *)PCI_LAT_TIMER } },
    { "autoIntRouteSet", HCF_RES_INT, { (void *)TRUE } },
    { "includeFuncSet", HCF_RES_ADDR, { (void *)sysPci3AutoconfigInclude } },
    { "intAssignFuncSet", HCF_RES_ADDR, {(void *)sysPci3AutoconfigIntrAssign }},
    /* non vxbPciAutoConfig() values */
    { "pimmrBase", HCF_RES_ADDR, { (void *)PCI_BRIDGE_PIMMR_BASE_ADRS } },
    { "lclMemAddr", HCF_RES_ADDR, { (void *)LOCAL_MEM_LOCAL_ADRS } },
    { "lclMemMapSize", HCF_RES_INT, { (void *)(512 * 1024 * 1024) } },
    { "mstrMemBus", HCF_RES_ADDR, { (void *)PCI_MSTR_MEM_BUS } },

    { "pciConfigMechanism",HCF_RES_INT, { (void *)(0)}},
    { "maxBusSet", HCF_RES_INT, { (void *)3 } },
    /* LAWBAR details */
    /* Window Attributes - Defaults to 8540 type if none given */
    { "owAttrMem",HCF_RES_INT, { (void *)(PCI_WINDOW_ENABLE_BIT | PCI_OUT_ATTR_RTT_MEM |  PCI_OUT_ATTR_WTT_MEM) } },
    { "owAttrMemIo", HCF_RES_INT, { (void *)(PCI_WINDOW_ENABLE_BIT | PCI_OUT_ATTR_RTT_MEM |  PCI_OUT_ATTR_WTT_MEM) } },
    { "owAttrIo", HCF_RES_INT, { (void *)(PCI_WINDOW_ENABLE_BIT | PCI_OUT_ATTR_RTT_IO |  PCI_OUT_ATTR_WTT_IO) } },
    { "iwAttr", HCF_RES_INT, { (void *)(PCI_WINDOW_ENABLE_BIT | PCI_PREFETCHABLE| PCI_IN_ATTR_RTT_LM_READ_SNOOP | PCI_IN_ATTR_RTT_LM_WRITE_SNOOP | PCI_IN_ATTR_TGI_LM) } },
    { "singleLawBar", HCF_RES_INT, { (void *)(TRUE)}},
    { "singleLawBarSize",HCF_RES_INT, { (void *)(0x10000000)}},
    { "tgtIf",HCF_RES_INT, { (void *)(LAWAR_TGTIF_PCIEX)} },
    { "autoConfig",HCF_RES_INT, { (void *)(TRUE)}},
    { "pciExpressHost",HCF_RES_INT, { (void *)(TRUE)}}

};
#define m85xxPci2Num NELEMENTS(m85xxPci2Resources)
#endif /* INCLUDE_CDS85XX_PCIEX */

#endif /* INCLUDE_PCI_BUS */


#ifdef REV13_CARRIER

const struct hcfResource mv88E1xx0Resources[] = {
    { "phyAddr", HCF_RES_INT, { (void *)0 } },
    { "nonGenericBspMod", HCF_RES_INT, { (void *)MV88E_NO_BSP_MOD } },
};
#define mv88E1xx0Num NELEMENTS(mv88E1xx0Resources)

const struct hcfResource mv88E1xx1Resources[] = {
    { "phyAddr", HCF_RES_INT, { (void *)1 } },
    { "nonGenericBspMod", HCF_RES_INT, { (void *)MV88E_NO_BSP_MOD } },
};
#define mv88E1xx1Num NELEMENTS(mv88E1xx1Resources)

const struct hcfResource mv88E1xx2Resources[] = {
    { "phyAddr", HCF_RES_INT, { (void *)2 } },
    { "nonGenericBspMod", HCF_RES_INT, { (void *)MV88E_CDS8548_BSP_MOD } },
};
#define mv88E1xx2Num NELEMENTS(mv88E1xx2Resources)

const struct hcfResource mv88E1xx3Resources[] = {
    { "phyAddr", HCF_RES_INT, { (void *)3 } },
    { "nonGenericBspMod", HCF_RES_INT, { (void *)MV88E_CDS8548_BSP_MOD } },
};

#define mv88E1xx3Num NELEMENTS(mv88E1xx3Resources)
#endif /* REV13_CARRIER */

#ifdef INCLUDE_RAPIDIO_BUS
const struct hcfResource m85xxRio0Resources[] = {
    { "regBase",	HCF_RES_INT, {(void *)RAPIDIO_BASE} },
    { "deviceBase", HCF_RES_INT, {(void *)(RAPIDIO_ADRS + 0x0000000)}},
    { "deviceSize", HCF_RES_INT, {(void *)(RAPIDIO_SIZE - 0x0000000)}},
    { "rioBusAdrs", HCF_RES_INT, {(void *)RAPIDIO_BUS_ADRS }},
    { "rioBusSize", HCF_RES_INT, {(void *)RAPIDIO_BUS_SIZE }},
    { "tgtIf", HCF_RES_INT, {(void *)LAWAR_TGTIF_RAPIDIO }},
    { "localMemAdrs",HCF_RES_INT, {(void *)LOCAL_MEM_LOCAL_ADRS}}    
};
#define m85xxRio0Num    NELEMENTS(m85xxRio0Resources)

const struct hcfResource m85xxCPU0Resources[] = {
	{ "regBase",	HCF_RES_INT, {(void *)RAPIDIO_BASE }},
	{ "targetID",	HCF_RES_INT, {(void *)0 }},
	{ "outboundWindow0",     HCF_RES_INT, {(void *)RIO_CHANNEL_RESERVED }},
	{ "outboundWindow1",     HCF_RES_INT, {(void *)RIO_CHANNEL_MAINT }},
	{ "outboundWindow2",     HCF_RES_INT, {(void *)RIO_CHANNEL_CFG }},
	{ "outboundWindow3",     HCF_RES_INT, {(void *)RIO_CHANNEL_UNRESERVED }},
	{ "outboundWindow4",     HCF_RES_INT, {(void *)RIO_CHANNEL_UNRESERVED }},
	{ "outboundWindow5",     HCF_RES_INT, {(void *)RIO_CHANNEL_UNRESERVED }},
	{ "outboundWindow6",     HCF_RES_INT, {(void *)RIO_CHANNEL_UNRESERVED }},
	{ "outboundWindow7",     HCF_RES_INT, {(void *)RIO_CHANNEL_UNRESERVED }},
	{ "outboundWindow8",     HCF_RES_INT, {(void *)RIO_CHANNEL_UNRESERVED }},
	{ "inboundWindow0",     HCF_RES_INT, {(void *)RIO_CHANNEL_RESERVED }},
	{ "inboundWindow1",     HCF_RES_INT, {(void *)RIO_CHANNEL_SM }},
	{ "inboundWindow2",     HCF_RES_INT, {(void *)RIO_CHANNEL_UNRESERVED }},
	{ "inboundWindow3",     HCF_RES_INT, {(void *)RIO_CHANNEL_UNRESERVED }},
	{ "inboundWindow4",     HCF_RES_INT, {(void *)RIO_CHANNEL_UNRESERVED }}

};
#define m85xxCPU0Num    NELEMENTS(m85xxCPU0Resources)

const struct hcfResource m85xxCPU1Resources[] = {
	{ "regBase",	HCF_RES_INT, {(void *)RAPIDIO_BASE }},
	{ "targetID",	HCF_RES_INT, {(void *) 0x9 }},
	{ "hopCount",	HCF_RES_INT, {(void *) 0x0 }},
	{ "outboundWindow0",     HCF_RES_INT, {(void *)RIO_CHANNEL_RESERVED }},
	{ "outboundWindow1",     HCF_RES_INT, {(void *)RIO_CHANNEL_SM }},
	{ "outboundWindow2",     HCF_RES_INT, {(void *)RIO_CHANNEL_TAS_SET }},
	{ "outboundWindow3",     HCF_RES_INT, {(void *)RIO_CHANNEL_TAS_CLEAR }},
	{ "outboundWindow4",     HCF_RES_INT, {(void *)RIO_CHANNEL_DOORBELL }},
	{ "outboundWindow5",     HCF_RES_INT, {(void *)RIO_CHANNEL_UNRESERVED }},
	{ "outboundWindow6",     HCF_RES_INT, {(void *)RIO_CHANNEL_UNRESERVED }},
	{ "outboundWindow7",     HCF_RES_INT, {(void *)RIO_CHANNEL_UNRESERVED }},
	{ "outboundWindow8",     HCF_RES_INT, {(void *)RIO_CHANNEL_UNRESERVED }},
	{ "inboundWindow0",     HCF_RES_INT, {(void *) RIO_CHANNEL_RESERVED}},
	{ "inboundWindow1",     HCF_RES_INT, {(void *)RIO_CHANNEL_UNRESERVED }},
	{ "inboundWindow2",     HCF_RES_INT, {(void *)RIO_CHANNEL_UNRESERVED }},
	{ "inboundWindow3",     HCF_RES_INT, {(void *)RIO_CHANNEL_UNRESERVED }},
	{ "inboundWindow4",     HCF_RES_INT, {(void *)RIO_CHANNEL_UNRESERVED }}

};
#define m85xxCPU1Num    NELEMENTS(m85xxCPU1Resources)

#ifdef INCLUDE_SM_NET
const struct hcfResource smEnd0Resources[] = {		
{ "regBase",	HCF_RES_INT, {(void *)CCSBAR} },
{ "SM_ANCHOR_OFFSET", HCF_RES_INT, {(void *)SM_ANCHOR_OFFSET}},
{ "SM_MEM_ADRS", HCF_RES_INT,{(void *)SM_MEM_ADRS }},
{ "SM_MEM_SIZE", HCF_RES_INT,{(void *)SM_MEM_SIZE}},
{ "SM_TAS_TYPE", HCF_RES_INT,{(void *)SM_TAS_TYPE} },
{ "SM_INT_TYPE", HCF_RES_INT,{(void *)SM_INT_TYPE} },
{ "SM_INT_ARG1", HCF_RES_INT,{(void *)SM_INT_ARG1}},
{ "SM_INT_ARG2", HCF_RES_INT, {(void *)SM_INT_ARG2}},
{ "SM_INT_ARG3", HCF_RES_INT, {(void *)SM_INT_ARG3}},
{ "SM_PKTS_SIZE", HCF_RES_INT, {(void *)SM_PKTS_SIZE}},
{ "SM_MAX_PKTS", HCF_RES_INT, {(void *)SM_MAX_PKTS}},
{ "SM_MBLK_NUM", HCF_RES_INT, {(void *)600}},
{ "SM_CBLK_NUM", HCF_RES_INT, {(void *)200}}
};

#define smEnd0Num    NELEMENTS(smEnd0Resources)
#endif /* INCLUDE_SM_NET */

#endif /* INCLUDE_RAPIDIO_BUS */

#ifdef DRV_RESOURCE_M85XXCCSR
const struct hcfResource m85xxLawBarResources[] = {
{ "regBase",	HCF_RES_INT, {(void *)CCSBAR} },
{ "LAWAR_ENABLE",       HCF_RES_INT, {(void *) LAWAR_ENABLE} },
{ "LAWBAR_ADRS_SHIFT",  HCF_RES_INT, {(void *) LAWBAR_ADRS_SHIFT} },
{ "LAWBAR0",	HCF_RES_STRING, {"reserved"} },
{ "LAWBAR1",	HCF_RES_STRING, {"reserved"} },
{ "LAWBAR2",	HCF_RES_STRING, {NULL} },
{ "LAWBAR3",	HCF_RES_STRING, {"reserved"} },
{ "LAWBAR4",	HCF_RES_STRING, {"m85xxPci"} },
{ "LAWBAR5",	HCF_RES_STRING, {"m85xxPci"} },
{ "LAWBAR6",	HCF_RES_STRING, {"m85xxPci"} },
{ "LAWBAR7",	HCF_RES_STRING, {"m85xxRio"} },
{ "LAWBAR8",	HCF_RES_STRING, {"reserved"} },
{ "LAWBAR9",	HCF_RES_STRING, {"reserved"} }

};

#define m85xxLawBarNum    NELEMENTS(m85xxLawBarResources)
#endif /* DRV_RESOURCE_M85XXCCSR */

#ifdef DRV_SIO_NS16550
const struct hcfResource ns1655x1Resources[] = {
    { VXB_REG_BASE,  HCF_RES_INT,  {(void *)COM2_ADR} },
    { "irq",         HCF_RES_INT,  {(void *)EPIC_DUART_INT_VEC} },
    { "regInterval", HCF_RES_INT,  {(void *)DUART_REG_ADDR_INTERVAL} },
    { "irqLevel",    HCF_RES_INT,  {(void *)EPIC_DUART_INT_VEC} },
    { VXB_CLK_FREQ,     HCF_RES_ADDR, {(void *)&sysClkFreqGet} }
};
#define ns1655x1Num NELEMENTS(ns1655x1Resources)

const struct hcfResource ns1655x2Resources[] = {
    { VXB_REG_BASE,  HCF_RES_INT,  {(void *)COM1_ADR} },
    { "irq",         HCF_RES_INT,  {(void *)EPIC_DUART_INT_VEC} },
    { "regInterval", HCF_RES_INT,  {(void *)DUART_REG_ADDR_INTERVAL} },
    { "irqLevel",    HCF_RES_INT,  {(void *)EPIC_DUART_INT_VEC} },
    { VXB_CLK_FREQ,     HCF_RES_ADDR, {(void *)&sysClkFreqGet} }
};
#define ns1655x2Num NELEMENTS(ns1655x2Resources)
#endif /* DRV_SIO_NS16550 */

struct intrCtlrInputs epicInputs[] = {
    { EPIC_DUART_INT_VEC, "ns16550", 1, 0 },
#if defined (INCLUDE_ETSEC_VXB_END) || defined (INCLUDE_TSEC_VXB_END)
    { EPIC_TSEC1TX_INT_VEC, XTSEC_NAME, 0, 0 },
    { EPIC_TSEC1RX_INT_VEC, XTSEC_NAME, 0, 1 },
    { EPIC_TSEC3TX_INT_VEC, XTSEC_NAME, 2, 0 },
    { EPIC_TSEC3RX_INT_VEC, XTSEC_NAME, 2, 1 },
    { EPIC_TSEC3ERR_INT_VEC, XTSEC_NAME, 2, 2 },
    { EPIC_TSEC1ERR_INT_VEC, XTSEC_NAME, 0, 2 },
    { EPIC_TSEC2TX_INT_VEC, XTSEC_NAME, 1, 0 },
    { EPIC_TSEC2RX_INT_VEC, XTSEC_NAME, 1, 1 },
    { EPIC_TSEC4TX_INT_VEC, XTSEC_NAME, 3, 0 },
    { EPIC_TSEC4RX_INT_VEC, XTSEC_NAME, 3, 1 },
    { EPIC_TSEC4ERR_INT_VEC, XTSEC_NAME, 3, 2 },
    { EPIC_TSEC2ERR_INT_VEC, XTSEC_NAME, 1, 2 },
#endif /* defined (INCLUDE_ETSEC_VXB_END) || defined (INCLUDE_TSEC_VXB_END) */
    { EPIC_DUART_INT_VEC, "ns16550", 0, 0},
};

const struct hcfResource epic0Resources[] = {
    { "regBase",        HCF_RES_INT,    {(void *)(CCSBAR) } },
    { "input",          HCF_RES_ADDR,   {(void *)&epicInputs[0] } },
    { "inputTableSize", HCF_RES_INT,    {(void *)NELEMENTS(epicInputs) } },
    { "numCpus",	HCF_RES_INT,	{(void *)1 } },
#ifdef INCLUDE_PCI_BUS
    { "exPolar",	HCF_RES_INT,	{(void *)EPIC_INT_ACT_LOW } },
#endif /* INCLUDE_PCI_BUS */
};
#define epic0Num NELEMENTS(epic0Resources)

struct intrCtlrInputs ppcIntCtlrInputs[] = {
    { 0, "epic", 0, 0 },
};

const struct hcfResource ppcIntCtlr0Resources[] = {
    { "regBase",        HCF_RES_INT,    {(void *)TRUE} },
    { "input",          HCF_RES_ADDR,   {(void *)&ppcIntCtlrInputs[0] } },
    { "inputTableSize", HCF_RES_INT,    {(void *)NELEMENTS(ppcIntCtlrInputs) } }
,
};
#define ppcIntCtlr0Num NELEMENTS(ppcIntCtlr0Resources)

#ifdef DRV_TIMER_M85XX

struct hcfResource m85xxTimerResources[] =  {
    {"regBase", HCF_RES_INT, {(void *)0}},
    {"decMinClkRate",HCF_RES_INT, {(void *)SYS_CLK_RATE_MIN}},
    {"decMaxClkRate",HCF_RES_INT, {(void *)SYS_CLK_RATE_MAX}},
    {"fitMinClkRate",HCF_RES_INT, {(void *)AUX_CLK_RATE_MIN}},
    {"fitMaxClkRate",HCF_RES_INT, {(void *)AUX_CLK_RATE_MAX}},
    {"vectorDec",HCF_RES_INT, {(void *)_EXC_OFF_DECR}},
    {"vectorFit",HCF_RES_INT, {(void *)_EXC_OFF_FIT}},
    {"vectorWdt",HCF_RES_INT, {(void *)_EXC_OFF_WD}},
    {"sysClockFreq",HCF_RES_ADDR, {(void *)&sysClkFreqGet}}
};
#define m85xxTimerNum         NELEMENTS(m85xxTimerResources)

#endif /* DRV_TIMER_M85XX */

const struct hcfDevice hcfDeviceList[] = {
    { "epic", 0, VXB_BUSID_PLB, 0, epic0Num, epic0Resources },
    { "ppcIntCtlr", 0, VXB_BUSID_PLB, 0, ppcIntCtlr0Num, ppcIntCtlr0Resources },

#if defined (INCLUDE_ETSEC_VXB_END) || defined (INCLUDE_TSEC_VXB_END)
#error 1
    { XTSEC_NAME, 0, VXB_BUSID_PLB, 0, tsecVxbEnd0Num, tsecVxbEnd0Resources },
    { XTSEC_NAME, 1, VXB_BUSID_PLB, 0, tsecVxbEnd1Num, tsecVxbEnd1Resources },
    { XTSEC_NAME, 2, VXB_BUSID_PLB, 0, tsecVxbEnd2Num, tsecVxbEnd2Resources },
    { XTSEC_NAME, 3, VXB_BUSID_PLB, 0, tsecVxbEnd3Num, tsecVxbEnd3Resources },
#endif

#ifdef DRV_SIO_NS16550
/*#error 2*/
    { "ns16550", 0, VXB_BUSID_PLB, 0, ns1655x1Num, ns1655x1Resources },
    { "ns16550", 1, VXB_BUSID_PLB, 0, ns1655x2Num, ns1655x2Resources },
#endif

#ifdef INCLUDE_PCI_BUS
#error 3
    { "m85xxPci", 0, VXB_BUSID_PLB,0, m85xxPci0Num, m85xxPci0Resources },
#ifdef INCLUDE_CDS85XX_SECONDARY_PCI
    { "m85xxPci", 1, VXB_BUSID_PLB,0, m85xxPci1Num, m85xxPci1Resources },
#endif
#ifdef INCLUDE_CDS85XX_PCIEX
    { "m85xxPci", 2, VXB_BUSID_PLB,0, m85xxPci2Num, m85xxPci2Resources },
#endif
#endif /* INCLUDE_PCI_BUS */

#ifdef REV13_CARRIER
#error 4
    { "mv88E14xPhy", 0, VXB_BUSID_MII, 0, mv88E1xx0Num, mv88E1xx0Resources },
    { "mv88E14xPhy", 1, VXB_BUSID_MII, 0, mv88E1xx1Num, mv88E1xx1Resources },
    { "mv88E14xPhy", 2, VXB_BUSID_MII, 0, mv88E1xx2Num, mv88E1xx2Resources },
    { "mv88E14xPhy", 3, VXB_BUSID_MII, 0, mv88E1xx3Num, mv88E1xx3Resources },
#endif

#ifdef INCLUDE_RAPIDIO_BUS
#error 5
    { "m85xxRio", 0, VXB_BUSID_PLB, 0, m85xxRio0Num, m85xxRio0Resources },
    { "m85xxCPU", 0, VXB_BUSID_RAPIDIO, 0, m85xxCPU0Num, m85xxCPU0Resources },
    { "m85xxCPU", 1, VXB_BUSID_RAPIDIO, 0, m85xxCPU1Num, m85xxCPU1Resources },
#ifdef INCLUDE_SM_NET
    { "smEnd", 0, VXB_BUSID_PLB,0, smEnd0Num, smEnd0Resources},
#endif /* INCLUDE_SM_NET */
#endif

#ifdef DRV_RESOURCE_M85XXCCSR
#error 6
    { "m85xxCCSR", 0, VXB_BUSID_PLB, 0, m85xxLawBarNum, m85xxLawBarResources },
#endif /* DRV_RESOURCE_M85XXCCSR */

#ifdef DRV_TIMER_M85XX
/*#error 7*/
    {"m85xxTimerDev", 0, VXB_BUSID_PLB, 0, m85xxTimerNum,
                                                        m85xxTimerResources},
#endif /* DRV_TIMER_M85XX */
};
const int hcfDeviceNum = NELEMENTS(hcfDeviceList);

/* Example of pass parameter to etsec driver included */
VXB_INST_PARAM_OVERRIDE sysInstParamTable[] =
    {
    { NULL, 0, NULL, VXB_PARAM_END_OF_LIST, {(void *)0} }
    };
