/* sysNet.h - system-dependent Network Header File */

/* Copyright (c) 2005-2006 Wind River Systems, Inc. */

/*
modification history
--------------------
01a,22nov06,d_c  Move MAX_MAC_DEVS and ENET_DEFAULT from sysNet.h to config.h
01a,14oct05dtr	 created from ads834x/01c
*/


#ifndef  __INCsysNeth
#define  __INCsysNeth 

#ifdef __cplusplus
    extern "C" {
#endif

#include <vxWorks.h>
#include <config.h>

extern const char *sysNetDevName[MAX_MAC_DEVS];

/* Prototypes */

int sysMacIndex2Dev (int index);

int sysMacIndex2Unit (int index);

STATUS sysMacOffsetGet (char *ifName, int ifUnit, char **ppEnet, 
                              int *	pOffset);
			      
STATUS sysNetMacNVRamAddrGet (char *ifName, int ifUnit, UINT8 *ifMacAddr, 
                              int ifMacAddrLen);
STATUS sysNetMacAddrGet (char *ifName, int ifUnit, UINT8 *ifMacAddr, 
                              int ifMacAddrLen);
STATUS sysNetMacAddrSet (char *ifName, int ifUnit, UINT8 *ifMacAddr, 
                              int ifMacAddrLen);

#ifdef __cplusplus
    }
#endif

#endif   /* __INCsysNeth  */

