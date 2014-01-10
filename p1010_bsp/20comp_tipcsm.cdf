/* 20comp_tipcSm.cdf - TIPC Shared Memory Component configuration file */

/* Copyright (c) 2005-2007 Wind River Systems, Inc.
 * All rights reserved.
 * 
 * Redistribution and use in source and binary forms, with or without 
 * modification, are permitted provided that the following conditions are met:
 * 
 * Redistributions of source code must retain the above copyright notice, 
 * this list of conditions and the following disclaimer. 
 * Redistributions in binary form must reproduce the above copyright notice, 
 * this list of conditions and the following disclaimer in the documentation 
 * and/or other materials provided with the distribution. 
 * Neither the names of the copyright holders nor the names of its contributors 
 * may be used to endorse or promote products derived from this software 
 * without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
 * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, 
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR 
 * PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR 
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, 
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, 
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; 
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, 
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR 
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF 
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */ 

/*
modification history
--------------------
01l,29aug07,mze  re-added SOURCE_ONLY to fix gnu compile issue
01k,21aug07,mze  removed SOURCE_ONLY 
01j,26jul07,mze  changed SOURCE_ONLY list 
01i,19jul07,mze  removed SMP flag 
01h,12jul07,mze  added SMP flag and SOURCE_ONLY flag
01g,25jan07,mze  change names of files to reflect new name changes
01f,16mar06,mze  change to SM_TIPC_NUM_BUF default to 60
01e,09mar06,ebh  change SYNOPSIS entry for consistency in capitalization
01d,28sep05,bwa  added synopsises.
01c,14apr05,bwa  made component child of SELECT_TIPC_MEDIA_TYPES (SPR107526).
01b,14apr05,als  added licensing info
01a,15fev05,bwa  written.
*/

/*
DESCRIPTION
This file contains the description for the shared memory support for TIPC.
*/
Component INCLUDE_TIPC_MEDIA_SM {
	NAME		Shared Memory
        SYNOPSIS        Allows TIPC to communicate over shared memory
	CONFIGLETTES	usrTipcSm.c
        SOURCE_ONLY     {$(TGT_DIR)/src/tipc {tipc_sm_media.o}}
	INIT_RTN	usrTipcSmInit (BOOT_LINE_ADRS);
	_INIT_ORDER	usrNetworkInit
	INIT_BEFORE	INCLUDE_TIPC
	REQUIRES	INCLUDE_SM_COMMON       \
                        INCLUDE_TIPC
        _CHILDREN       SELECT_TIPC_MEDIA_TYPES
	CFG_PARAMS	                        \
                        SM_TIPC_ADRS            \
                        SM_TIPC_SIZE            \
			SM_TIPC_SM_PKT_SIZE     \
			SM_TIPC_PKT_Q_LEN       \
                        SM_TIPC_NUM_BUF
	HDR_FILES	vxWorks.h stdio.h sysLib.h smLib.h smUtilLib.h \
                        tipc/tipc_sm_media.h
}


Parameter SM_TIPC_ADRS {
	NAME		Starting address of TIPC shared memory block
	SYNOPSIS	BSP-specific, SM_TIPC_ADRS_DEFAULT for the BSP default.
	DEFAULT		SM_TIPC_ADRS_DEFAULT
}

Parameter SM_TIPC_SIZE {
	NAME		Size of TIPC shared memory block
	SYNOPSIS	Use SM_TIPC_SIZE_DEFAULT for default BSP-specific value.
	DEFAULT		SM_TIPC_SIZE_DEFAULT
}

Parameter SM_TIPC_SM_PKT_SIZE {
	NAME		Shared memory packets size (0 for system default)
	SYNOPSIS	MTU in bytes, system default is 2176, minimum is 160.
	DEFAULT		0
}

Parameter SM_TIPC_NUM_BUF {
	NAME		Number of buffers in the bearer pool
	SYNOPSIS	Balance between wasted space and retransmissions. Default 60
	DEFAULT		60
}

Parameter SM_TIPC_PKT_Q_LEN {
	NAME		Maximum packets queued in SM (0 for system default)
	SYNOPSIS	System default is 200.
	DEFAULT		0
}
