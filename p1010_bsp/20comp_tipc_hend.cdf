/* 20comp_tipc_hend_cdf_master - TIPC HEnd Component configuration file */

/*
 * Copyright (c) 2005 Wind River Systems, Inc.
 *
 * The right to copy, distribute, modify, or otherwise make use
 * of this software may be licensed only pursuant to the terms
 * of an applicable Wind River license agreement.
 */

/*
modification history
--------------------

01a,11Nov05,mze  written.
*/

/* 
DESCRIPTION

This file contains all HEnd components for TIPC, the Transparent Inter-Process
Communication protocol.  TIPC components lie in the Network Protocol Components folder.

Include the main INCLUDE_TIPC component to allow applications to use the
default TIPC configuration, which provides intra-node communication only.

*/



Component INCLUDE_TIPC_HEND_INIT 
{
      NAME		TIPC prioritized interfaces
	SYNOPSIS	Initialization of TIPC prioritized interfaces
      CFG_PARAMS	TIPC_HEND_CONFIG_STR
	INIT_RTN	usrTipcHendAttach();
      REQUIRES    INCLUDE_HEND_PARAM_SYS INCLUDE_TIPC
}

Parameter TIPC_HEND_CONFIG_STR {
	NAME		TIPC interfaces using H-END
	SYNOPSIS	list of interface names, within quotes, with "," between interface names, or NULL
        TYPE            string
	DEFAULT		NULL
}


