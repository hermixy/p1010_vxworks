# Makefile - makefile for Freescale cds8548 BSP
#
# Copyright (c) 2005 Wind River Systems, Inc.
# 
# modification history
# --------------------
# 01d,29may07,vik  removed cmdLine.c build 
# 01c,29apr07,cjj  fix missing mod history when IP_PORT_VXWORKS 
#		   stuff was added.
# 01c,02mar07,rec  WIND00089420 - remove ipnet makefile workaround
# 01b,01dec06,d_c  Add dependency on sysLib.c to create cmdLine.c
# 01a,13jun05,dtr  Modify from cds85xx/Makefile/01b
#
# DESCRIPTION
# This file contains rules for building VxWorks for the
# FreeScale MPC8548 CDS reference board
#
# INCLUDES
#     makeTarget
#*/

CPU              = PPC85XX
TOOL             = sfdiab

#Support for 36 bit physical addresses in the MMU can be added for 
#vxWorks 6.2 and later with the following CPU_VARIANT.
#CPU_VARIANT      = _e500v2

#Use diab for vxWorks 5.5.1
#TOOL = diab

TGT_DIR = $(WIND_BASE)/target

include $(TGT_DIR)/h/make/defs.bsp
#include $(TGT_DIR)/h/make/make.$(CPU)$(TOOL)
#include $(TGT_DIR)/h/make/defs.$(WIND_HOST_TYPE)

## Only redefine make definitions below this point, or your definitions will
## be overwritten by the makefile stubs above.


TARGET_DIR	= cds8548
VENDOR		= Freescale
BOARD		= MPC8548 CDS

RELEASE		+= bootrom_uncmp.hex bootrom_uncmp.bin 

EXTRA_DEFINE    = -g

## The constants ROM_TEXT_ADRS, ROM_SIZE, and RAM_HIGH_ADRS are defined
## in config.h and Makefile. All definitions for these constants must be
## identical.

ROM_TEXT_ADRS    = fff00100 # ROM entry address
ROM_SIZE         = 00100000 # number of bytes of ROM space
ROM_WARM_ADRS    = fff00108 # ROM warm entry address 
ROM_LINK_ADRS	 = fff00000

RAM_LOW_ADRS     = 00100000 # RAM text/data address
RAM_HIGH_ADRS    = 01000000 # RAM text/data address

MACH_EXTRA       = put.o

BOOT_EXTRA       = 
LIB_EXTRA        = 

VMA_START        = 0x0
USR_ENTRY        = usrInit

CONFIG_ALL			= ./all
## Only redefine make definitions above this point, or the expansion of 
## makefile target dependencies may be incorrect.

include $(TGT_DIR)/h/make/rules.bsp
#include $(TGT_DIR)/h/make/rules.$(WIND_HOST_TYPE)

bin:vxWorks
	objdumpppc -D vxWorks>z.txt
	objcopyppc -O binary vxWorks uImage
