/* 20bsp.cdf - BSP component description file */

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
01d,07aug07,dtr  Update for rapidIo configurations.
01c,22feb07,jmt  Defect 88750 - Fix problem with network boot device CDF
                 defines
01b,04dec06,rlg  update for NOR port
01a,16jul06,pee  created

*/

Bsp cds8548 {
	CPU PPC32
	REQUIRES	INCLUDE_KERNEL
	FP soft
}

/* Network Boot Devices for a BSP
 * The REQUIRES line should be modified for a BSP.
 */
Component       INCLUDE_BOOT_NET_DEVICES {
    REQUIRES    INCLUDE_ETSEC_VXB_END
}

Parameter RAM_HIGH_ADRS {
       NAME         Bootrom Copy region
       DEFAULT      (INCLUDE_BOOT_RAM_IMAGE)::(0x03000000) \
                    (INCLUDE_BOOT_APP)::(0x02000000) \
                    0x01000000
}

Parameter RAM_LOW_ADRS {
       NAME         Runtime kernel load address
       DEFAULT      (INCLUDE_BOOT_RAM_IMAGE)::(0x02000000) \
                    (INCLUDE_BOOT_APP)::(0x01000000) \
                    0x00100000
}

Component INCLUDE_RAPIDIO_BUS {
       REQUIRES   += INCLUDE_M85XX_RAPIDIO \
                  INCLUDE_M85XX_CPU DRV_RESOURCE_M85XXCCSR \
                  RAPIDIO_BUS_STATIC_TABLE \
                  VXBUS_TABLE_CONFIG
}

Component INCLUDE_SM_COMMON {
       REQUIRES   +=  INCLUDE_M85XX_RIO_SM_CFG INCLUDE_VXBUS_SM_SUPPORT \
                  INCLUDE_VXBUS_SM_SUPPORT INCLUDE_SMEND INCLUDE_SM_NET \
                  INCLUDE_IPATTACH INCLUDE_IFCONFIG \
                  INCLUDE_IPWRAP_IPPROTO
}



