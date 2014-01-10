REM   *********************************************************
REM   Wind River Probe REGISTER CONFIGURATION CAPTURE FILE
REM   Captured On:  04-29-2005 : 16:54:45
REM   from Wind River Probe Firmware:  
REM   visionCLICK version:  8.00.0027
REM   ComDll version:  8.0V
Created On:  10/19/2004 5:55:12 PM
REM   *********************************************************

REM *******************************************
REM CF CONFIGURATION
REM *******************************************
REM DDR settings are for 533Mhz - NO ECC
REM *******************************************
CF TAR                             8548
CF SB                              SB
CF MMU                             DISABLE
CF BL                              DISABLE
CF RST                             YES
CF CLK                             16
CF LENDIAN                         NO
CF DLD                             NORMAL
CF HRESET                          ENABLE
CF TRESET                          ACTIVE
CF RESET                           HRESET
CF CHECKSTOP                       NO
CF SPOWER                          YES
CF PONR                            0
CF TRPEXP                          YES
CF INCOLD                          YES
CF WSPACE                          00005000 ff68
CF TGTCONS                         BDM
CF RTP                             NO
CF RPL                             1
CF ETM                             c2010
CF PORABIST                        YES
CF TMD                             DISABLE
CF BOOTMODE                        NORMAL
CF DDRDLL                          YES
CF LBCLK                           NO
CF DRST                            1
CF L2TLB                           00000000
REM *******************************************
REM SCGA    TA               CONFIGURATION
REM *******************************************
SC GRP ERASE
SCGA LA                              CCSRBAR                         00000000  000E0000 LA                              /va_dr /ua:0 /sa:0 /ue:0
SCGA LA                              ALTCBAR                         00000008  00000000 LA                              /ua:0
SCGA LA                              ALTCSR                          00000010  00000000 LA                              /ua:0
SCGA LA                              BPTR                            00000020  00000000 LA                              /ua:0
SCGA LA                              LAWBAR0                         00000C08  00000000 LA                              /ua:0
SCGA LA                              LAWAR0                          00000C10  00000000 LA                              /ua:0
SCGA LA                              LAWBAR1                         00000C28  00000000 LA                              /ua:0
SCGA LA                              LAWAR1                          00000C30  80F0001C LA                              /ua:0
SCGA LA                              LAWBAR2                         00000C48  00080000 LA                              /ua:0
SCGA LA                              LAWAR2                          00000C50  8000001C LA                              /ua:0
SCGA LA                              LAWBAR3                         00000C68  000A0000 LA                              /ua:0
SCGA LA                              LAWAR3                          00000C70  8010001C LA                              /ua:0
SCGA LA                              LAWBAR4                         00000C88  000E2000 LA                              /ua:0
SCGA LA                              LAWAR4                          00000C90  80000017 LA                              /ua:0
SCGA LA                              LAWBAR5                         00000CA8  000E3000 LA                              /ua:0
SCGA LA                              LAWAR5                          00000CB0  80100017 LA                              /ua:0
SCGA LA                              LAWBAR6                         00000CC8  000F0000 LA                              /ua:0
SCGA LA                              LAWAR6                          00000CD0  8040001B LA                              /ua:0
SCGA LA                              LAWBAR7                         00000CE8  00000000 LA                              /ua:0
SCGA LA                              LAWAR7                          00000CF0  00000000 LA                              /ua:0
SCGA ECM                             EEBACR                          00001000  00000003 ECM                             /ua:0
SCGA ECM                             EEBPCR                          00001010  01000000 ECM                             /ua:0
SCGA ECM                             EEDR                            00001E00  00000000 ECM                             /ua:0
SCGA ECM                             EEER                            00001E08  00000000 ECM                             /ua:0
SCGA ECM                             EEATR                           00001E0C  00000000 ECM                             /ua:0
SCGA ECM                             EEADR                           00001E10  00000000 ECM                             /ua:0
SCGA LBC                             BR0                             00005000  FF801001 LBC                             /va_dr /ua:0 /sa:1
SCGA LBC                             OR0                             00005004  FF806FF7 LBC                             /ua:0
SCGA LBC                             BR1                             00005008  FF001001 LBC                             /va_dr /ua:0 /sa:1
SCGA LBC                             OR1                             0000500C  FF806ff7 LBC                             /ua:0
SCGA LBC                             BR2                             00005010  F0001861 LBC                             /va_dr /ua:0 /sa:1
SCGA LBC                             OR2                             00005014  FC006901 LBC                             /ua:0
SCGA LBC                             BR3                             00005018  F8000801 LBC                             /va_dr /ua:0 /sa:1
SCGA LBC                             OR3                             0000501C  FFF00FF7 LBC                             /ua:0
SCGA LBC                             BR4                             00005020  00000000 LBC                             /va_dr /ua:0 /sa:1
SCGA LBC                             OR4                             00005024  00000000 LBC                             /ua:0
SCGA LBC                             BR5                             00005028  00000000 LBC                             /va_dr /ua:0 /sa:1
SCGA LBC                             OR5                             0000502C  00000000 LBC                             /ua:0
SCGA LBC                             BR6                             00005030  00000000 LBC                             /va_dr /ua:0 /sa:1
SCGA LBC                             OR6                             00005034  00000000 LBC                             /ua:0
SCGA LBC                             BR7                             00005038  00000000 LBC                             /va_dr /ua:0 /sa:1
SCGA LBC                             OR7                             0000503C  00000000 LBC                             /ua:0
SCGA LBC                             MAR                             00005068  00000000 LBC                             /ua:0
SCGA LBC                             MAMR                            00005070  00000000 LBC                             /ua:0
SCGA LBC                             MBMR                            00005074  00000000 LBC                             /ua:0
SCGA LBC                             MCMR                            00005078  00000000 LBC                             /ua:0
SCGA LBC                             MRTPR                           00005084  00000000 LBC                             /ua:0
SCGA LBC                             MDR                             00005088  00000000 LBC                             /ua:0
SCGA LBC                             LSDMR                           00005094  4063FF03 LBC                             /ua:0
SCGA LBC                             LURT                            000050A0  00000000 LBC                             /ua:0
SCGA LBC                             LSRT                            000050A4  20000000 LBC                             /ua:0
SCGA LBC                             LTESR                           000050B0  00000000 LBC                             /r /ua:0
SCGA LBC                             LTEDR                           000050B4  00000000 LBC                             /ua:0
SCGA LBC                             LTEIR                           000050B8  00000000 LBC                             /ua:0
SCGA LBC                             LTEATR                          000050BC  00000000 LBC                             /ua:0
SCGA LBC                             LTEAR                           000050C0  00000000 LBC                             /ua:0
SCGA LBC                             LBCR                            000050D0  00000000 LBC                             /ua:0
SCGA LBC                             LCRR                            000050D4  80030008 LBC                             /ua:0
SCGA I2C                             I2CADR                          00003000  7E       I2C                             /ua:0
SCGA I2C                             I2CFDR                          00003004  3F       I2C                             /ua:0
SCGA I2C                             I2CCR                           00003008  80       I2C                             /ua:0
SCGA I2C                             I2CSR                           0000300C  81       I2C                             /ua:0
SCGA I2C                             I2CDR                           00003010  00       I2C                             /ua:0
SCGA I2C                             I2CDFSRR                        00003014  10       I2C                             /ua:0
SCGA DUART                           URBR0                           00004500  00       DUART                           /r /ua:2 /ue:1
SCGA DUART                           UTHR0                           00004500  00       DUART                           /w /ua:2 /ue:1
SCGA DUART                           UDLB0                           00004500  00       DUART                           /ua:2 /ue:1
SCGA DUART                           UIER0                           00004501  00       DUART                           /ua:2 /ue:1
SCGA DUART                           UDMB0                           00004501  00       DUART                           /ua:2 /ue:1
SCGA DUART                           UIIR0                           00004502  01       DUART                           /r /ua:2 /ue:1
SCGA DUART                           UFCR0                           00004502  01       DUART                           /w /ua:2 /ue:1
SCGA DUART                           UAFR0                           00004502  01       DUART                           /ua:2 /ue:1
SCGA DUART                           ULCR0                           00004503  00       DUART                           /ua:2 /ue:1
SCGA DUART                           UMCR0                           00004504  00       DUART                           /ua:2 /ue:1
SCGA DUART                           ULSR0                           00004505  60       DUART                           /r /ua:2 /ue:1
SCGA DUART                           UMSR0                           00004506  00       DUART                           /r /ua:2 /ue:1
SCGA DUART                           USCR0                           00004507  00       DUART                           /ua:2 /ue:1
SCGA DUART                           UDSR0                           00004510  01       DUART                           /r /ua:2 /ue:1
SCGA DUART                           URBR1                           00004600  00       DUART                           /r /ua:2 /ue:1
SCGA DUART                           UTHR1                           00004600  00       DUART                           /w /ua:2 /ue:1
SCGA DUART                           UDLB1                           00004600  00       DUART                           /ua:2 /ue:1
SCGA DUART                           UIER1                           00004601  00       DUART                           /ua:2 /ue:1
SCGA DUART                           UDMB1                           00004601  00       DUART                           /ua:2 /ue:1
SCGA DUART                           UIIR1                           00004602  C1       DUART                           /r /ua:2 /ue:1
SCGA DUART                           UFCR1                           00004602  C1       DUART                           /w /ua:2 /ue:1
SCGA DUART                           UAFR1                           00004602  C1       DUART                           /ua:2 /ue:1
SCGA DUART                           ULCR1                           00004603  03       DUART                           /ua:2 /ue:1
SCGA DUART                           UMCR1                           00004604  03       DUART                           /ua:2 /ue:1
SCGA DUART                           ULSR1                           00004605  60       DUART                           /r /ua:2 /ue:1
SCGA DUART                           UMSR1                           00004606  11       DUART                           /r /ua:2 /ue:1
SCGA DUART                           USCR1                           00004607  00       DUART                           /ua:2 /ue:1
SCGA DUART                           UDSR1                           00004610  01       DUART                           /r /ua:2 /ue:1
SCGA DDRMC                           CS0_BNDS                        00002000  0000000F DDRMC                           /ua:0
SCGA DDRMC                           CS1_BNDS                        00002008  0010001F DDRMC                           /ua:0
SCGA DDRMC                           CS2_BNDS                        00002010  00000000 DDRMC                           /ua:0
SCGA DDRMC                           CS3_BNDS                        00002018  00000000 DDRMC                           /ua:0
SCGA DDRMC                           CS0_CONFIG                      00002080  80010102 DDRMC                           /ua:0
SCGA DDRMC                           CS1_CONFIG                      00002084  80010102 DDRMC                           /ua:0
SCGA DDRMC                           CS2_CONFIG                      00002088  00000000 DDRMC                           /ua:0
SCGA DDRMC                           CS3_CONFIG                      0000208C  00000000 DDRMC                           /ua:0
SCGA DDRMC                           EXT_REFREC                      00002100  00010000 DDRMC                           /ua:0
SCGA DDRMC                           TIMING_CFG_0                    00002104  AA260802 DDRMC                           /ua:0
SCGA DDRMC                           TIMING_CFG_1                    00002108  4C47A432 DDRMC                           /ua:0
SCGA DDRMC                           TIMING_CFG_2                    0000210C  0F984CCE DDRMC                           /ua:0
SCGA DDRMC                           DDR_SDRAM_CFG1                  00002110  43008000 DDRMC                           /ua:0 /ue:2
SCGA DDRMC                           DDR_SDRAM_CFG3                  00002114  24000000  DDRMC                           /ua:0
SCGA DDRMC                           DDR_SDRAM_MODE                  00002118  00400842  DDRMC                           /ua:0
SCGA DDRMC                           DDR_SDRAM_MODE2                 0000211C  00000000 DDRMC                           /ua:0
SCGA DDRMC                           DDR_SDRAM_MD_CNTL               00002120  00000000 DDRMC                           /ua:0
SCGA DDRMC                           DDR_SDRAM_INT                   00002124  08200100  DDRMC                           /ua:0
SCGA DDRMC                           DDR_DATA_INIT                   00002128  00000000 DDRMC                           /ua:0
SCGA DDRMC                           DDR_SDRAM_CLK_CNTL              00002130  03800000 DDRMC                           /ua:0
SCGA DDRMC                           DATA_ERR_INJ_HI                 00002E00  00000000 DDRMC                           /ua:0
SCGA DDRMC                           DATA_ERR_INJ_LO                 00002E04  00000000 DDRMC                           /ua:0
SCGA DDRMC                           ECC_ERR_INJECT                  00002E08  00000000 DDRMC                           /ua:0
SCGA DDRMC                           CAPTURE_DATA_HI                 00002E20  00000000 DDRMC                           /ua:0
SCGA DDRMC                           CAPTURE_DATA_LO                 00002E24  00000000 DDRMC                           /ua:0
SCGA DDRMC                           CAPTURE_ECC                     00002E28  00000000 DDRMC                           /ua:0
SCGA DDRMC                           ERR_DETECT                      00002E40  00000000 DDRMC                           /ua:0
SCGA DDRMC                           ERR_DISABLE                     00002E44  00000000 DDRMC                           /ua:0
SCGA DDRMC                           ERR_INT_EN                      00002E48  00000000 DDRMC                           /ua:0
SCGA DDRMC                           CAPTURE_ATTRI                   00002E4C  00000000 DDRMC                           /ua:0
SCGA DDRMC                           CAPTURE_ADDRESS                 00002E50  00000000 DDRMC                           /ua:0
SCGA DDRMC                           ERR_SBE                         00002E58  00000000 DDRMC                           /ua:0
SCGA DDRMC                           DDR_IO_OVCR                     000E0F24  90000000 DDRMC                           /ua:0
SCGA DDRMC                           DDR_SDRAM_CFG2                  00002110  C3008000 DDRMC                           /ua:0
SCGA TA                              ITLB0A                          10000000  000FFFFF TA                              /cpur
SCGA TA                              ITLB0B                          10000001  00FFFFF1 TA                              /cpur
SCGA TA                              ITLB0C                          10000002  0FC01800 TA                              /cpur
SCGA TA                              ITLB1A                          10000010  000FFFFF TA                              /cpur
SCGA TA                              ITLB1B                          10000011  00FFFFF1 TA                              /cpur
SCGA TA                              ITLB1C                          10000012  0FC01800 TA                              /cpur
SCGA TA                              ITLB2A                          10000020  400FFFFF TA                              /cpur
SCGA TA                              ITLB2B                          10000021  00FF0001 TA                              /cpur
SCGA TA                              ITLB2C                          10000022  00011B80 TA                              /cpur
SCGA TA                              ITLB3A                          10000030  400FFD8C TA                              /cpur
SCGA TA                              ITLB3B                          10000031  00100000 TA                              /cpur
SCGA TA                              ITLB3C                          10000032  00001B80 TA                              /cpur
SCGA TA                              DTLB0A                          20000000  400FFB3C TA                              /cpur
SCGA TA                              DTLB0B                          20000001  00100000 TA                              /cpur
SCGA TA                              DTLB0C                          20000002  00001B80 TA                              /cpur
SCGA TA                              DTLB1A                          20000010  4008004F TA                              /cpur
SCGA TA                              DTLB1B                          20000011  00F80001 TA                              /cpur
SCGA TA                              DTLB1C                          20000012  0C011B80 TA                              /cpur
SCGA TA                              DTLB2A                          20000020  4000000E TA                              /cpur
SCGA TA                              DTLB2B                          20000021  00E00001 TA                              /cpur
SCGA TA                              DTLB2C                          20000022  00011B80 TA                              /cpur
SCGA TA                              DTLB3A                          20000030  4000000C TA                              /cpur
SCGA TA                              DTLB3B                          20000031  00000000 TA                              /cpur
SCGA TA                              DTLB3C                          20000032  00001B80 TA                              /cpur
SCGA    TA                LTLB0A                          30000000  300FF000 TA                                        /cpur
SCGA    TA                LTLB0B                          30000001  700FF000 TA                                        /cpur
SCGA    TA                LTLB0C                          30000002  03F62870 TA                                        /cpur
SCGA    TA                LTLB1A                          30000010  30000000 TA                                        /cpur
SCGA    TA                LTLB1B                          30000011  90000000 TA                                        /cpur
SCGA    TA                LTLB1C                          30000012  0FF61070 TA                                        /cpur
SCGA    TA                LTLB2A                          30000020  30010000 TA                                        /cpur
SCGA    TA                LTLB2B                          30000021  90010000 TA                                        /cpur
SCGA    TA                LTLB2C                          30000022  0FF61070 TA                                        /cpur
SCGA    TA                LTLB3A                          30000030  300E0000 TA                                        /cpur
SCGA    TA                LTLB3B                          30000031  500E0000 TA                                        /cpur
SCGA    TA                LTLB3C                          30000032  00F62860 TA                                        /cpur
SCGA    TA                LTLB4A                          30000040  900E0000 TA                                        /cpur
SCGA    TA                LTLB4B                          30000041  500E0000 TA                                        /cpur
SCGA    TA                LTLB4C                          30000042  00F02860 TA                                        /cpur
SCGA    TA                LTLB5A                          30000050  300F0000 TA                                        /cpur
SCGA    TA                LTLB5B                          30000051  800F0000 TA                                        /cpur
SCGA    TA                LTLB5C                          30000052  07F61070 TA                                        /cpur
SCGA    TA                LTLB6A                          30000060  300F7000 TA                                        /cpur
SCGA    TA                LTLB6B                          30000061  700F7000 TA                                        /cpur
SCGA    TA                LTLB6C                          30000062  03F63860 TA                                        /cpur
SCGA    TA                LTLB7A                          30000070  100C0000 TA                                        /cpur
SCGA    TA                LTLB7B                          30000071  900C0000 TA                                        /cpur
SCGA    TA                LTLB7C                          30000072  0FF02060 TA                                        /cpur
SCGA    TA                LTLB8A                          30000080  10050000 TA                                        /cpur
SCGA    TA                LTLB8B                          30000081  90050000 TA                                        /cpur
SCGA    TA                LTLB8C                          30000082  0FF02860 TA                                        /cpur
SCGA    TA                LTLB9A                          30000090  00000000 TA                                        /cpur
SCGA    TA                LTLB9B                          30000091  00000000 TA                                        /cpur
SCGA    TA                LTLB9C                          30000092  00000000 TA                                        /cpur
SCGA    TA                LTLB10A                         300000A0  00000000 TA                                        /cpur
SCGA    TA                LTLB10B                         300000A1  00000000 TA                                        /cpur
SCGA    TA                LTLB10C                         300000A2  00000000 TA                                        /cpur
SCGA    TA                LTLB11A                         300000B0  00000000 TA                                        /cpur
SCGA    TA                LTLB11B                         300000B1  00000000 TA                                        /cpur
SCGA    TA                LTLB11C                         300000B2  00000000 TA                                        /cpur
SCGA    TA                LTLB12A                         300000C0  00000000 TA                                        /cpur
SCGA    TA                LTLB12B                         300000C1  00000000 TA                                        /cpur
SCGA    TA                LTLB12C                         300000C2  00000000 TA                                        /cpur
SCGA    TA                LTLB13A                         300000D0  00000000 TA                                        /cpur
SCGA    TA                LTLB13B                         300000D1  00000000 TA                                        /cpur
SCGA    TA                LTLB13C                         300000D2  00000000 TA                                        /cpur
SCGA    TA                LTLB14A                         300000E0  00000000 TA                                        /cpur
SCGA    TA                LTLB14B                         300000E1  00000000 TA                                        /cpur
SCGA    TA                LTLB14C                         300000E2  00000000 TA                                        /cpur
SCGA    TA                LTLB15A                         300000F0  00000000 TA                                        /cpur
SCGA    TA                LTLB15B                         300000F1  00000000 TA                                        /cpur
SCGA    TA                LTLB15C                         300000F2  00000000 TA                                        /cpur
SCGA PCI                             MAP                             01234567  00008000 PCI                             /no_addr /no_in /hide /tld:6 /ue:6
SCGA PCI                             XOFFSET                         76543210  00000004 PCI                             /no_addr /no_in /hide /tld:7 /ue:6
SCGA PCI                             ANCHOR0                         89ABCDEF  00000000 PCI                             /no_addr /no_in /hide /sa:4 /ue:6
SCGA PCI                             ANCHOR1                         FEDCBA98  00000000 PCI                             /no_addr /no_in /hide /sa:5 /ue:6
SCGA PCI                             VENDORID                        00000000  1057     PCI                             /r(nwf) /w(nwf) /lendian /r /ua:5
SCGA PCI                             ADDR_00                         00000000  80000000 PCI                             /wo /hide /lendian /w /ua:4
SCGA PCI                             DEVICEID                        00000002  0012     PCI                             /r(nwf) /w(nwf) /lendian /r /ua:5
SCGA PCI                             ADDR_02                         00000000  80000002 PCI                             /wo /hide /lendian /w /ua:4
SCGA PCI                             PCIBCMD                         00000000  0004     PCI                             /r(nwf) /w(nwf) /lendian /ua:5
SCGA PCI                             ADDR_04                         00000000  80000004 PCI                             /wo /hide /lendian /w /ua:4
SCGA PCI                             PCIBSTAT                        00000002  00B0     PCI                             /r(nwf) /w(nwf) /lendian /r /ua:5
SCGA PCI                             ADDR_06                         00000000  80000006 PCI                             /wo /hide /lendian /w /ua:4
SCGA PCI                             REVID                           00000000  10       PCI                             /r(nwf) /w(nwf) /lendian /r /ua:5
SCGA PCI                             ADDR_08                         00000000  80000008 PCI                             /wo /hide /lendian /w /ua:4
SCGA PCI                             BPIR                            00000001  00       PCI                             /r(nwf) /w(nwf) /lendian /r /ua:5
SCGA PCI                             ADDR_09                         00000000  80000009 PCI                             /wo /hide /lendian /w /ua:4
SCGA PCI                             SUBCCODE                        00000002  20       PCI                             /r(nwf) /w(nwf) /lendian /r /ua:5
SCGA PCI                             ADDR_0A                         00000000  8000000A PCI                             /wo /hide /lendian /w /ua:4
SCGA PCI                             BBCCR                           00000003  0B       PCI                             /r(nwf) /w(nwf) /lendian /r /ua:5
SCGA PCI                             ADDR_0B                         00000000  8000000B PCI                             /wo /hide /lendian /w /ua:4
SCGA PCI                             BCLSR                           00000000  00       PCI                             /r(nwf) /w(nwf) /lendian /ua:5
SCGA PCI                             ADDR_0C                         00000000  8000000C PCI                             /wo /hide /lendian /w /ua:4
SCGA PCI                             BLTR                            00000001  00       PCI                             /r(nwf) /w(nwf) /lendian /ua:5
SCGA PCI                             ADDR_0D                         00000000  8000000D PCI                             /wo /hide /lendian /w /ua:4
SCGA PCI                             HTR                             00000002  00       PCI                             /r(nwf) /w(nwf) /lendian /r /ua:5
SCGA PCI                             ADDR_0E                         00000000  8000000E PCI                             /wo /hide /lendian /w /ua:4
SCGA PCI                             BISTCTRL                        00000003  00       PCI                             /r(nwf) /w(nwf) /lendian /r /ua:5
SCGA PCI                             ADDR_0F                         00000000  8000000F PCI                             /wo /hide /lendian /w /ua:4
SCGA PCI                             PCSRBAR                         00000000  00000000 PCI                             /r(nwf) /w(nwf) /lendian /ua:5
SCGA PCI                             ADDR_10                         00000000  80000010 PCI                             /wo /hide /lendian /w /ua:4
SCGA PCI                             32BMBAR                         00000000  00000000 PCI                             /r(nwf) /w(nwf) /lendian /ua:5
SCGA PCI                             ADDR_14                         00000000  80000014 PCI                             /wo /hide /lendian /w /ua:4
SCGA PCI                             64BLMBAR1                       00000000  00000004 PCI                             /r(nwf) /w(nwf) /lendian /ua:5
SCGA PCI                             ADDR_18                         00000000  80000018 PCI                             /wo /hide /lendian /w /ua:4
SCGA PCI                             64BHMBAR1                       00000000  00000000 PCI                             /r(nwf) /w(nwf) /lendian /ua:5
SCGA PCI                             ADDR_1C                         00000000  8000001C PCI                             /wo /hide /lendian /w /ua:4
SCGA PCI                             64BLMBAR2                       00000000  00000004 PCI                             /r(nwf) /w(nwf) /lendian /ua:5
SCGA PCI                             ADDR_20                         00000000  80000020 PCI                             /wo /hide /lendian /w /ua:4
SCGA PCI                             64BHMBAR2                       00000000  00000000 PCI                             /r(nwf) /w(nwf) /lendian /ua:5
SCGA PCI                             ADDR_24                         00000000  80000024 PCI                             /wo /hide /lendian /w /ua:4
SCGA PCI                             SUBVENDOR                       00000000  0000     PCI                             /r(nwf) /w(nwf) /lendian /ua:5
SCGA PCI                             ADDR_2C                         00000000  8000002C PCI                             /wo /hide /lendian /w /ua:4
SCGA PCI                             SUBID                           00000002  0000     PCI                             /r(nwf) /w(nwf) /lendian /ua:5
SCGA PCI                             ADDR_2E                         00000000  8000002E PCI                             /wo /hide /lendian /w /ua:4
SCGA PCI                             PBCP                            00000000  60       PCI                             /r(nwf) /w(nwf) /lendian /r /ua:5
SCGA PCI                             ADDR_34                         00000000  80000034 PCI                             /wo /hide /lendian /w /ua:4
SCGA PCI                             PBILR                           00000000  00       PCI                             /r(nwf) /w(nwf) /lendian /ua:5
SCGA PCI                             ADDR_3C                         00000000  8000003C PCI                             /wo /hide /lendian /w /ua:4
SCGA PCI                             PBINTPIN                        00000001  01       PCI                             /r(nwf) /w(nwf) /lendian /r /ua:5
SCGA PCI                             ADDR_3D                         00000000  8000003D PCI                             /wo /hide /lendian /w /ua:4
SCGA PCI                             MAX_GNT                         00000002  00       PCI                             /r(nwf) /w(nwf) /lendian /r /ua:5
SCGA PCI                             ADDR_3E                         00000000  8000003E PCI                             /wo /hide /lendian /w /ua:4
SCGA PCI                             MAX_LAT                         00000003  00       PCI                             /r(nwf) /w(nwf) /lendian /r /ua:5
SCGA PCI                             ADDR_3F                         00000000  8000003F PCI                             /wo /hide /lendian /w /ua:4
SCGA PCI                             PCIBFR                          00000000  0020     PCI                             /r(nwf) /w(nwf) /lendian /ua:5
SCGA PCI                             ADDR_44                         00000000  80000044 PCI                             /wo /hide /lendian /w /ua:4
SCGA PCI                             PBACR                           00000002  8000     PCI                             /r(nwf) /w(nwf) /lendian /ua:5
SCGA PCI                             ADDR_46                         00000000  80000046 PCI                             /wo /hide /lendian /w /ua:4
SCGA PCI                             PCIXCID                         00000000  00       PCI                             /r(nwf) /w(nwf) /lendian /ua:5
SCGA PCI                             ADDR_60                         00000000  80000060 PCI                             /wo /hide /lendian /w /ua:4
SCGA PCI                             PCIXNC                          00000001  00       PCI                             /r(nwf) /w(nwf) /lendian /r /ua:5
SCGA PCI                             ADDR_61                         00000000  80000061 PCI                             /wo /hide /lendian /w /ua:4
SCGA PCI                             PCIXCMD                         00000002  0000     PCI                             /r(nwf) /w(nwf) /lendian /ua:5
SCGA PCI                             ADDR_62                         00000000  80000062 PCI                             /wo /hide /lendian /w /ua:4
SCGA PCI                             PCIXSTAT                        00000000  00000000 PCI                             /r(nwf) /w(nwf) /lendian /ua:5
SCGA PCI                             ADDR_64                         00000000  80000064 PCI                             /wo /hide /lendian /w /ua:4
SCGA PCI                             PCI1CFGADDR                     00008000  80000064 PCI                             /no_in /ua:0
SCGA PCI                             PCI1CFGDATA                     00008004  00000000 PCI                             /no_in /ua:0
SCGA PCI                             PCI1INTACK                      00008008  00000000 PCI                             /r /ua:0 /ue:6
SCGA PCI                             PCI1OWTAR0                      00008C00  00000000 PCI                             /ua:0
SCGA PCI                             PCI1OWTEAR0                     00008C04  00000000 PCI                             /ua:0
SCGA PCI                             PCI1OWAR0                       00008C10  8004401F PCI                             /ua:0
SCGA PCI                             PCI1OWTAR1                      00008C20  00000000 PCI                             /ua:0
SCGA PCI                             PCI1OWTEAR1                     00008C24  00000000 PCI                             /ua:0
SCGA PCI                             PCI1OWBAR1                      00008C28  00000000 PCI                             /ua:0
SCGA PCI                             PCI1OWAR1                       00008C30  00000000 PCI                             /ua:0
SCGA PCI                             PCI1OWTAR2                      00008C40  00000000 PCI                             /ua:0
SCGA PCI                             PCI1OWTEAR2                     00008C44  00000000 PCI                             /ua:0
SCGA PCI                             PCI1OWBAR2                      00008C48  00000000 PCI                             /ua:0
SCGA PCI                             PCI1OWAR2                       00008C50  00000000 PCI                             /ua:0
SCGA PCI                             PCI1OWTAR3                      00008C60  00000000 PCI                             /ua:0
SCGA PCI                             PCI1OWTEAR3                     00008C64  00000000 PCI                             /ua:0
SCGA PCI                             PCI1OWBAR3                      00008C68  00000000 PCI                             /ua:0
SCGA PCI                             PCI1OWAR3                       00008C70  00000000 PCI                             /ua:0
SCGA PCI                             PCI1OWTAR4                      00008C80  00000000 PCI                             /ua:0
SCGA PCI                             PCI1OWTEAR4                     00008C84  00000000 PCI                             /ua:0
SCGA PCI                             PCI1OWBAR4                      00008C88  00000000 PCI                             /ua:0
SCGA PCI                             PCI1OWAR4                       00008C90  00000000 PCI                             /ua:0
SCGA PCI                             PCI1IWTAR3                      00008DA0  00000000 PCI                             /ua:0
SCGA PCI                             PCI1IWBAR3                      00008DA8  00000000 PCI                             /ua:0
SCGA PCI                             PCI1IWBEAR3                     00008DAC  00000000 PCI                             /ua:0
SCGA PCI                             PCI1IWAR3                       00008DB0  00000000 PCI                             /ua:0
SCGA PCI                             PCI1IWTAR2                      00008DC0  00000000 PCI                             /ua:0
SCGA PCI                             PCI1IWBAR2                      00008DC8  00000000 PCI                             /ua:0
SCGA PCI                             PCI1IWBEAR2                     00008DCC  00000000 PCI                             /ua:0
SCGA PCI                             PCI1IWAR2                       00008DD0  00000000 PCI                             /ua:0
SCGA PCI                             PCI1IWTAR1                      00008DE0  00000000 PCI                             /ua:0
SCGA PCI                             PCI1IWBAR1                      00008DE8  00000000 PCI                             /ua:0
SCGA PCI                             PCI1IWAR1                       00008DF0  00000000 PCI                             /ua:0
SCGA PCI                             PCI1EDR                         00008E00  00000000 PCI                             /ua:0
SCGA PCI                             PCI1ECDR                        00008E04  00000000 PCI                             /ua:0
SCGA PCI                             PCI1EER                         00008E08  00000000 PCI                             /ua:0
SCGA PCI                             PCI1EATTRCR                     00008E0C  00000000 PCI                             /ua:0
SCGA PCI                             PCI1EADDRCR                     00008E10  00000000 PCI                             /ua:0
SCGA PCI                             PCI1EEACR                       00008E14  00000000 PCI                             /ua:0
SCGA PCI                             PCI1EDLCR                       00008E18  00000000 PCI                             /ua:0
SCGA PCI                             PCI1EDHCR                       00008E1C  00000000 PCI                             /ua:0
SCGA PCI                             PCI1GTR                         00008E20  0103FFFF PCI                             /ua:0
SCGA PCI                             PCI2CFGADDR                     00009000  00000000 PCI                             /no_in /ua:0
SCGA PCI                             PCI2CFGDATA                     00009004  00000000 PCI                             /no_in /ua:0
SCGA PCI                             PCI2INTACK                      00009008  00000000 PCI                             /r /ua:0 /ue:6
SCGA PCI                             PCI2OWTAR0                      00009C00  00000000 PCI                             /ua:0
SCGA PCI                             PCI2OWTEAR0                     00009C04  00000000 PCI                             /ua:0
SCGA PCI                             PCI2OWAR0                       00009C10  00000000 PCI                             /ua:0
SCGA PCI                             PCI2OWTAR1                      00009C20  00000000 PCI                             /ua:0
SCGA PCI                             PCI2OWTEAR1                     00009C24  00000000 PCI                             /ua:0
SCGA PCI                             PCI2OWBAR1                      00009C28  00000000 PCI                             /ua:0
SCGA PCI                             PCI2OWAR1                       00009C30  00000000 PCI                             /ua:0
SCGA PCI                             PCI2OWTAR2                      00009C40  00000000 PCI                             /ua:0
SCGA PCI                             PCI2OWTEAR2                     00009C44  00000000 PCI                             /ua:0
SCGA PCI                             PCI2OWBAR2                      00009C48  00000000 PCI                             /ua:0
SCGA PCI                             PCI2OWAR2                       00009C50  00000000 PCI                             /ua:0
SCGA PCI                             PCI2OWTAR3                      00009C60  00000000 PCI                             /ua:0
SCGA PCI                             PCI2OWTEAR3                     00009C64  00000000 PCI                             /ua:0
SCGA PCI                             PCI2OWBAR3                      00009C68  00000000 PCI                             /ua:0
SCGA PCI                             PCI2OWAR3                       00009C70  00000000 PCI                             /ua:0
SCGA PCI                             PCI2OWTAR4                      00009C80  00000000 PCI                             /ua:0
SCGA PCI                             PCI2OWTEAR4                     00009C84  00000000 PCI                             /ua:0
SCGA PCI                             PCI2OWBAR4                      00009C88  00000000 PCI                             /ua:0
SCGA PCI                             PCI2OWAR4                       00009C90  00000000 PCI                             /ua:0
SCGA PCI                             PCI2IWTAR3                      00009DA0  00000000 PCI                             /ua:0
SCGA PCI                             PCI2IWBAR3                      00009DA8  00000000 PCI                             /ua:0
SCGA PCI                             PCI2IWBEAR3                     00009DAC  00000000 PCI                             /ua:0
SCGA PCI                             PCI2IWAR3                       00009DB0  00000000 PCI                             /ua:0
SCGA PCI                             PCI2IWTAR2                      00009DC0  00000000 PCI                             /ua:0
SCGA PCI                             PCI2IWBAR2                      00009DC8  00000000 PCI                             /ua:0
SCGA PCI                             PCI2IWBEAR2                     00009DCC  00000000 PCI                             /ua:0
SCGA PCI                             PCI2IWAR2                       00009DD0  00000000 PCI                             /ua:0
SCGA PCI                             PCI2IWTAR1                      00009DE0  00000000 PCI                             /ua:0
SCGA PCI                             PCI2IWBAR1                      00009DE8  00000000 PCI                             /ua:0
SCGA PCI                             PCI2IWAR1                       00009DF0  00000000 PCI                             /ua:0
SCGA PCI                             PCI2EDR                         00009E00  00000000 PCI                             /ua:0
SCGA PCI                             PCI2ECDR                        00009E04  00000000 PCI                             /ua:0
SCGA PCI                             PCI2EER                         00009E08  00000000 PCI                             /ua:0
SCGA PCI                             PCI2EATTRCR                     00009E0C  00000000 PCI                             /ua:0
SCGA PCI                             PCI2EADDRCR                     00009E10  00000000 PCI                             /ua:0
SCGA PCI                             PCI2EEACR                       00009E14  00000000 PCI                             /ua:0
SCGA PCI                             PCI2EDLCR                       00009E18  00000000 PCI                             /ua:0
SCGA PCI                             PCI2EDHCR                       00009E1C  00000000 PCI                             /ua:0
SCGA PCI                             PCI2GTR                         00009E20  00000000 PCI                             /ua:0
SCGA L2SRAM                          L2CTL                           00020000  20000000 L2SRAM                          /ua:0
SCGA L2SRAM                          L2CEWAR0                        00020010  00000000 L2SRAM                          /ua:0
SCGA L2SRAM                          L2CEWCR0                        00020018  00000000 L2SRAM                          /ua:0
SCGA L2SRAM                          L2CEWAR1                        00020020  00000000 L2SRAM                          /ua:0
SCGA L2SRAM                          L2CEWCR1                        00020028  00000000 L2SRAM                          /ua:0
SCGA L2SRAM                          L2CEWAR2                        00020030  00000000 L2SRAM                          /ua:0
SCGA L2SRAM                          L2CEWCR2                        00020038  00000000 L2SRAM                          /ua:0
SCGA L2SRAM                          L2CEWAR3                        00020040  00000000 L2SRAM                          /ua:0
SCGA L2SRAM                          L2CEWCR3                        00020048  00000000 L2SRAM                          /ua:0
SCGA L2SRAM                          L2SRBAR0                        00020100  07FFC000 L2SRAM                          /ua:0
SCGA L2SRAM                          L2SRBAR1                        00020108  00000000 L2SRAM                          /ua:0
SCGA L2SRAM                          L2ERRINJHI                      00020E00  00000000 L2SRAM                          /ua:0
SCGA L2SRAM                          L2ERRINJLO                      00020E04  00000000 L2SRAM                          /ua:0
SCGA L2SRAM                          L2ERRINJCTL                     00020E08  00000000 L2SRAM                          /ua:0
SCGA L2SRAM                          L2CAPTDATAHI                    00020E20  00000000 L2SRAM                          /r /ua:0
SCGA L2SRAM                          L2CAPTDATALO                    00020E24  00000000 L2SRAM                          /r /ua:0
SCGA L2SRAM                          L2CAPTECC                       00020E28  00000000 L2SRAM                          /r /ua:0
SCGA L2SRAM                          L2ERRDET                        00020E40  00000000 L2SRAM                          /ua:0
SCGA L2SRAM                          L2ERRDIS                        00020E44  00000000 L2SRAM                          /ua:0
SCGA L2SRAM                          L2ERRINTEN                      00020E48  00000000 L2SRAM                          /ua:0
SCGA L2SRAM                          L2ERRATTR                       00020E4C  00802001 L2SRAM                          /ua:0
SCGA L2SRAM                          L2ERRADDR                       00020E50  00000000 L2SRAM                          /r /ua:0
SCGA L2SRAM                          L2ERRCTL                        00020E58  00000000 L2SRAM                          /ua:0
SCGA DMA                             DMODR0                          00021100  00000000 DMA                             /ua:0
SCGA DMA                             DSTATR0                         00021104  00000000 DMA                             /ua:0
SCGA DMA                             DCLNDAR0                        0002110C  00000000 DMA                             /ua:0
SCGA DMA                             DSATTR0                         00021110  00000000 DMA                             /ua:0
SCGA DMA                             DSADDR0                         00021114  00000000 DMA                             /ua:0
SCGA DMA                             DDATTR0                         00021118  00000000 DMA                             /ua:0
SCGA DMA                             DDADDR0                         0002111C  00000000 DMA                             /ua:0
SCGA DMA                             DBCNTR0                         00021120  00000000 DMA                             /ua:0
SCGA DMA                             DNLNDAR0                        00021128  00000000 DMA                             /ua:0
SCGA DMA                             DCLIDAR0                        00021134  00000000 DMA                             /ua:0
SCGA DMA                             DNLIDAR0                        0002113C  00000000 DMA                             /ua:0
SCGA DMA                             DSSTR0                          00021140  00000000 DMA                             /ua:0
SCGA DMA                             DDSTR0                          00021144  00000000 DMA                             /ua:0
SCGA DMA                             DMODR1                          00021180  00000000 DMA                             /ua:0
SCGA DMA                             DSTATR1                         00021184  00000000 DMA                             /ua:0
SCGA DMA                             DCLNDAR1                        0002118C  00000000 DMA                             /ua:0
SCGA DMA                             DSATTR1                         00021190  00000000 DMA                             /ua:0
SCGA DMA                             DSADDR1                         00021194  00000000 DMA                             /ua:0
SCGA DMA                             DDATTR1                         00021198  00000000 DMA                             /ua:0
SCGA DMA                             DDADDR1                         0002119C  00000000 DMA                             /ua:0
SCGA DMA                             DBCNTR1                         000211A0  00000000 DMA                             /ua:0
SCGA DMA                             DNLNDAR1                        000211A8  00000000 DMA                             /ua:0
SCGA DMA                             DCLIDAR1                        000211B4  00000000 DMA                             /ua:0
SCGA DMA                             DNLIDAR1                        000211BC  00000000 DMA                             /ua:0
SCGA DMA                             DSSTR1                          000211C0  00000000 DMA                             /ua:0
SCGA DMA                             DDSTR1                          000211C4  00000000 DMA                             /ua:0
SCGA DMA                             DMODR2                          00021200  00000000 DMA                             /ua:0
SCGA DMA                             DSTATR2                         00021204  00000000 DMA                             /ua:0
SCGA DMA                             DCLNDAR2                        0002120C  00000000 DMA                             /ua:0
SCGA DMA                             DSATTR2                         00021210  00000000 DMA                             /ua:0
SCGA DMA                             DSADDR2                         00021214  00000000 DMA                             /ua:0
SCGA DMA                             DDATTR2                         00021218  00000000 DMA                             /ua:0
SCGA DMA                             DDADDR2                         0002121C  00000000 DMA                             /ua:0
SCGA DMA                             DBCNTR2                         00021220  00000000 DMA                             /ua:0
SCGA DMA                             DNLNDAR2                        00021228  00000000 DMA                             /ua:0
SCGA DMA                             DCLIDAR2                        00021234  00000000 DMA                             /ua:0
SCGA DMA                             DNLIDAR2                        0002123C  00000000 DMA                             /ua:0
SCGA DMA                             DSSTR2                          00021240  00000000 DMA                             /ua:0
SCGA DMA                             DDSTR2                          00021244  00000000 DMA                             /ua:0
SCGA DMA                             DMODR3                          00021280  00000000 DMA                             /ua:0
SCGA DMA                             DSTATR3                         00021284  00000000 DMA                             /ua:0
SCGA DMA                             DCLNDAR3                        0002128C  00000000 DMA                             /ua:0
SCGA DMA                             DSATTR3                         00021290  00000000 DMA                             /ua:0
SCGA DMA                             DSADDR3                         00021294  00000000 DMA                             /ua:0
SCGA DMA                             DDATTR3                         00021298  00000000 DMA                             /ua:0
SCGA DMA                             DDADDR3                         0002129C  00000000 DMA                             /ua:0
SCGA DMA                             DBCNTR3                         000212A0  00000000 DMA                             /ua:0
SCGA DMA                             DNLNDAR3                        000212A8  00000000 DMA                             /ua:0
SCGA DMA                             DCLIDAR3                        000212B4  00000000 DMA                             /ua:0
SCGA DMA                             DNLIDAR3                        000212BC  00000000 DMA                             /ua:0
SCGA DMA                             DSSTR3                          000212C0  00000000 DMA                             /ua:0
SCGA DMA                             DDSTR3                          000212C4  00000000 DMA                             /ua:0
SCGA DMA                             DGSTATR                         00021300  00000000 DMA                             /r /ua:0
SCGA TSEC                            TSEC1_IEVENT                    00024010  00000600 TSEC                            /ua:0
SCGA TSEC                            TSEC1_IMASK                     00024014  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_EDIS                      00024018  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_ECNTRL                    00024020  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_MINFLR                    00024024  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_PTV                       00024028  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_DMACTRL                   0002402C  00000002 TSEC                            /ua:0
SCGA TSEC                            TSEC1_TBIPA                     00024030  0000001F TSEC                            /ua:0
SCGA TSEC                            TSEC1_FTX_THR                   0002408C  00000080 TSEC                            /ua:0
SCGA TSEC                            TSEC1_FTX_STARVE                00024098  00000040 TSEC                            /ua:0
SCGA TSEC                            TSEC1_FT_SHUTOFF                0002409C  00000080 TSEC                            /ua:0
SCGA TSEC                            TSEC1_TCTRL                     00024100  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_TSTAT                     00024104  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_TBDLEN                    0002410C  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_TXIC                      00024110  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_CTBPTR                    00024124  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_TBPTR                     00024184  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_TBASE                     00024204  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_OSTBD                     000242B0  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_OSTBDP                    000242B4  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_RCTRL                     00024300  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_RSTAT                     00024304  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_RBDLEN                    0002430C  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_RXIC                      00024310  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_CRBPTR                    00024324  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_MRBLR                     00024340  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_RBPTR                     00024384  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_RBASE                     00024404  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_MACCFG1                   00024500  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_MACCFG2                   00024504  00007000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_IPGIFGI                   00024508  40605060 TSEC                            /ua:0
SCGA TSEC                            TSEC1_HAFDUP                    0002450C  00A1F037 TSEC                            /ua:0
SCGA TSEC                            TSEC1_MAXFRM                    00024510  00000600 TSEC                            /ua:0
SCGA TSEC                            TSEC1_MIIMCFG                   00024520  00000003 TSEC                            /ua:0
SCGA TSEC                            TSEC1_MIIMCOM                   00024524  00000001 TSEC                            /ua:0
SCGA TSEC                            TSEC1_MIIMADD                   00024528  00000117 TSEC                            /ua:0
SCGA TSEC                            TSEC1_MIIMCON                   0002452C  00000006 TSEC                            /w /ua:0
SCGA TSEC                            TSEC1_MIIMSTAT                  00024530  00000000 TSEC                            /r /ua:0
SCGA TSEC                            TSEC1_MIIMIND                   00024534  00000000 TSEC                            /r /ua:0
SCGA TSEC                            TSEC1_IFSTAT                    0002453C  00000000 TSEC                            /r /ua:0
SCGA TSEC                            TSEC1_MACSTNADD1                00024540  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_MACSTNADD2                00024544  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_TR64                      00024680  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_TR127                     00024684  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_TR255                     00024688  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_TR511                     0002468C  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_TR1K                      00024690  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_TRMAX                     00024694  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_TRMGV                     00024698  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_RBYT                      0002469C  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_RPKT                      000246A0  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_RFCS                      000246A4  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_RMCA                      000246A8  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_RBCA                      000246AC  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_RXCF                      000246B0  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_RXPF                      000246B4  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_RXUO                      000246B8  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_RALN                      000246BC  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_RFLR                      000246C0  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_RCDE                      000246C4  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_RCSE                      000246C8  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_RUND                      000246CC  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_ROVR                      000246D0  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_RFRG                      000246D4  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_RJBR                      000246D8  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_RDRP                      000246DC  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_TBYT                      000246E0  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_TPKT                      000246E4  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_TMCA                      000246E8  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_TBCA                      000246EC  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_TXPF                      000246F0  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_TDFR                      000246F4  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_TEDF                      000246F8  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_TSCL                      000246FC  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_TMCL                      00024700  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_TLCL                      00024704  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_TXCL                      00024708  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_TNCL                      0002470C  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_TDRP                      00024714  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_TJBR                      00024718  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_TFCS                      0002471C  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_TXCF                      00024720  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_TOVR                      00024724  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_TUND                      00024728  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_TFRG                      0002472C  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_CAR1                      00024730  00000000 TSEC                            /r /ua:0
SCGA TSEC                            TSEC1_CAR2                      00024734  00000000 TSEC                            /r /ua:0
SCGA TSEC                            TSEC1_CAM1                      00024738  FE03FFFF TSEC                            /ua:0
SCGA TSEC                            TSEC1_CAM2                      0002473C  000FFFFD TSEC                            /ua:0
SCGA TSEC                            TSEC1_IADDR0                    00024800  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_IADDR1                    00024804  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_IADDR2                    00024808  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_IADDR3                    0002480C  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_IADDR4                    00024810  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_IADDR5                    00024814  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_IADDR6                    00024818  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_IADDR7                    0002481C  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_GADDR0                    00024880  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_GADDR1                    00024884  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_GADDR2                    00024888  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_GADDR3                    0002488C  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_GADDR4                    00024890  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_GADDR5                    00024894  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_GADDR6                    00024898  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_GADDR7                    0002489C  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC1_ATTR                      00024BF8  00000000 TSEC                            /r /ua:0
SCGA TSEC                            TSEC1_ATTRELI                   00024BFC  00000000 TSEC                            /r /ua:0
SCGA TSEC                            TSEC2_IEVENT                    00025010  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_IMASK                     00025014  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_EDIS                      00025018  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_ECNTRL                    00025020  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_MINFLR                    00025024  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_PTV                       00025028  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_DMACTRL                   0002502C  00000002 TSEC                            /ua:0
SCGA TSEC                            TSEC2_TBIPA                     00025030  0000001F TSEC                            /ua:0
SCGA TSEC                            TSEC2_FTX_THR                   0002508C  00000080 TSEC                            /ua:0
SCGA TSEC                            TSEC2_FTX_STARVE                00025098  00000040 TSEC                            /ua:0
SCGA TSEC                            TSEC2_FT_SHUTOFF                0002509C  00000080 TSEC                            /ua:0
SCGA TSEC                            TSEC2_TCTRL                     00025100  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_TSTAT                     00025104  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_TBDLEN                    0002510C  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_TXIC                      00025110  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_CTBPTR                    00025124  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_TBPTR                     00025184  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_TBASE                     00025204  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_OSTBD                     000252B0  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_OSTBDP                    000252B4  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_RCTRL                     00025300  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_RSTAT                     00025304  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_RBDLEN                    0002530C  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_RXIC                      00025310  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_CRBPTR                    00025324  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_MRBLR                     00025340  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_RBPTR                     00025384  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_RBASE                     00025404  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_MACCFG1                   00025500  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_MACCFG2                   00025504  00007000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_IPGIFGI                   00025508  40605060 TSEC                            /ua:0
SCGA TSEC                            TSEC2_HAFDUP                    0002550C  00A1F037 TSEC                            /ua:0
SCGA TSEC                            TSEC2_MAXFRM                    00025510  00000600 TSEC                            /ua:0
SCGA TSEC                            TSEC2_MIIMCFG                   00025520  00000007 TSEC                            /ua:0
SCGA TSEC                            TSEC2_MIIMCOM                   00025524  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_MIIMADD                   00025528  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_MIIMCON                   0002552C  00000000 TSEC                            /w /ua:0
SCGA TSEC                            TSEC2_MIIMSTAT                  00025530  00000000 TSEC                            /r /ua:0
SCGA TSEC                            TSEC2_MIIMIND                   00025534  00000000 TSEC                            /r /ua:0
SCGA TSEC                            TSEC2_IFSTAT                    0002553C  00000000 TSEC                            /r /ua:0
SCGA TSEC                            TSEC2_MACSTNADD1                00025540  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_MACSTNADD2                00025544  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_TR64                      00025680  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_TR127                     00025684  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_TR255                     00025688  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_TR511                     0002568C  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_TR1K                      00025690  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_TRMAX                     00025694  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_TRMGV                     00025698  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_RBYT                      0002569C  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_RPKT                      000256A0  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_RFCS                      000256A4  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_RMCA                      000256A8  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_RBCA                      000256AC  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_RXCF                      000256B0  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_RXPF                      000256B4  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_RXUO                      000256B8  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_RALN                      000256BC  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_RFLR                      000256C0  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_RCDE                      000256C4  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_RCSE                      000256C8  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_RUND                      000256CC  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_ROVR                      000256D0  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_RFRG                      000256D4  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_RJBR                      000256D8  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_RDRP                      000256DC  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_TBYT                      000256E0  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_TPKT                      000256E4  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_TMCA                      000256E8  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_TBCA                      000256EC  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_TXPF                      000256F0  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_TDFR                      000256F4  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_TEDF                      000256F8  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_TSCL                      000256FC  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_TMCL                      00025700  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_TLCL                      00025704  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_TXCL                      00025708  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_TNCL                      0002570C  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_TDRP                      00025714  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_TJBR                      00025718  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_TFCS                      0002571C  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_TXCF                      00025720  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_TOVR                      00025724  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_TUND                      00025728  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_TFRG                      0002572C  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_CAR1                      00025730  00000000 TSEC                            /r /ua:0
SCGA TSEC                            TSEC2_CAR2                      00025734  00000000 TSEC                            /r /ua:0
SCGA TSEC                            TSEC2_CAM1                      00025738  FE03FFFF TSEC                            /ua:0
SCGA TSEC                            TSEC2_CAM2                      0002573C  000FFFFD TSEC                            /ua:0
SCGA TSEC                            TSEC2_IADDR0                    00025800  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_IADDR1                    00025804  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_IADDR2                    00025808  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_IADDR3                    0002580C  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_IADDR4                    00025810  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_IADDR5                    00025814  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_IADDR6                    00025818  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_IADDR7                    0002581C  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_GADDR0                    00025880  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_GADDR1                    00025884  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_GADDR2                    00025888  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_GADDR3                    0002588C  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_GADDR4                    00025890  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_GADDR5                    00025894  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_GADDR6                    00025898  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_GADDR7                    0002589C  00000000 TSEC                            /ua:0
SCGA TSEC                            TSEC2_ATTR                      00025BF8  00000000 TSEC                            /r /ua:0
SCGA TSEC                            TSEC2_ATTRELI                   00025BFC  00000000 TSEC                            /r /ua:0
SCGA SE                              SEIMR                           00031008  0000000000000000 SE                              /ua:0
SCGA SE                              SEISR                           00031010  0000000000000000 SE                              /r /ua:0
SCGA SE                              SEICR                           00031018  0000000000000000 SE                              /w /ua:0
SCGA SE                              SEID                            00031020  0000000000000040 SE                              /r /ua:0
SCGA SE                              SEEUASR                         00031028  F0F0F0F0FFF0F0F0 SE                              /r /ua:0
SCGA SE                              SEMCR                           00031030  0000000000000000 SE                              /ua:0
SCGA SE                              SECCCR1                         00031108  0000000000000000 SE                              /ua:0
SCGA SE                              SECCPSR1                        00031110  0000000000000007 SE                              /r /ua:0
SCGA SE                              SECDPR1                         00031140  0000000000000000 SE                              /r /ua:0
SCGA SE                              SEFF1                           00031148  0000000000000000 SE                              /w /ua:0
SCGA SE                              SEDB1_BA                        00031180  0000000000000000 SE                              /r /ua:0
SCGA SE                              SECCCR2                         00031208  0000000000000000 SE                              /ua:0
SCGA SE                              SECCPSR2                        00031210  0000000000000007 SE                              /r /ua:0
SCGA SE                              SECDPR2                         00031240  0000000000000000 SE                              /r /ua:0
SCGA SE                              SEFF2                           00031248  0000000000000000 SE                              /w /ua:0
SCGA SE                              SEDB2_BA                        00031280  0000000000000000 SE                              /r /ua:0
SCGA SE                              SECCCR3                         00031308  0000000000000000 SE                              /ua:0
SCGA SE                              SECCPSR3                        00031310  0000000000000007 SE                              /r /ua:0
SCGA SE                              SECDPR3                         00031340  0000000000000000 SE                              /r /ua:0
SCGA SE                              SEFF3                           00031348  0000000000000000 SE                              /w /ua:0
SCGA SE                              SEDB3_BA                        00031380  0000000000000000 SE                              /r /ua:0
SCGA SE                              SECCCR4                         00031408  0000000000000000 SE                              /ua:0
SCGA SE                              SECCPSR4                        00031410  0000000000000007 SE                              /r /ua:0
SCGA SE                              SECDPR4                         00031440  0000000000000000 SE                              /r /ua:0
SCGA SE                              SEFF4                           00031448  0000000000000000 SE                              /w /ua:0
SCGA SE                              SEDB4_BA                        00031480  0000000000000000 SE                              /r /ua:0
SCGA SE                              SEDEUMR                         00032000  0000000000000000 SE                              /ua:0
SCGA SE                              SEDEUKSR                        00032008  0000000000000000 SE                              /ua:0
SCGA SE                              SEDEUDSR                        00032010  0000000000000000 SE                              /ua:0
SCGA SE                              SEDEURCR                        00032018  0000000000000000 SE                              /ua:0
SCGA SE                              SEDEUSR                         00032028  0000000000000001 SE                              /r /ua:0
SCGA SE                              SEDEUISR                        00032030  0000000000000000 SE                              /r /ua:0
SCGA SE                              SEDEUICR                        00032038  0000000000003000 SE                              /ua:0
SCGA SE                              SEDEUEUG                        00032050  0000000000000000 SE                              /w /ua:0
SCGA SE                              SEDEUIV                         00032100  0000000000000000 SE                              /ua:0
SCGA SE                              SEDEUK1                         00032400  0000000000000000 SE                              /w /ua:0
SCGA SE                              SEDEUK2                         00032408  0000000000000000 SE                              /w /ua:0
SCGA SE                              SEDEUK3                         00032410  0000000000000000 SE                              /w /ua:0
SCGA SE                              SEDEUFIFO                       00032800  0000000000000000 SE                              /ua:0
SCGA SE                              SEAESUMR                        00034000  0000000000000000 SE                              /ua:0
SCGA SE                              SEAESUKSR                       00034008  0000000000000000 SE                              /ua:0
SCGA SE                              SEAESUDSR                       00034010  0000000000000000 SE                              /ua:0
SCGA SE                              SEAESURCR                       00034018  0000000000000000 SE                              /ua:0
SCGA SE                              SEAESUSR                        00034028  0000000000000001 SE                              /r /ua:0
SCGA SE                              SEAESUISR                       00034030  0000000000000000 SE                              /r /ua:0
SCGA SE                              SEAESUICR                       00034038  0000000000001000 SE                              /ua:0
SCGA SE                              SEAESUEMR                       00034050  0000000000000000 SE                              /w /ua:0
SCGA SE                              SEAESUCMR_BA                    00034100  0000000000000000 SE                              /ua:0
SCGA SE                              SEAESUK1                        00034400  0000000000000000 SE                              /ua:0
SCGA SE                              SEAESUK2                        00034404  0000000000000000 SE                              /ua:0
SCGA SE                              SEAESUK3                        00034408  0000000000000000 SE                              /ua:0
SCGA SE                              SEAESUFIFO                      00034800  0000000000000000 SE                              /ua:0
SCGA SE                              SEMDEUMR                        00036000  0000000000000000 SE                              /ua:0
SCGA SE                              SEMDEUKSR                       00036008  0000000000000000 SE                              /ua:0
SCGA SE                              SEMDEUDSR                       00036010  0000000000000000 SE                              /ua:0
SCGA SE                              SEMDEURCR                       00036018  0000000000000000 SE                              /ua:0
SCGA SE                              SEMDEUSR                        00036028  0000000001000001 SE                              /r /ua:0
SCGA SE                              SEMDEUISR                       00036030  0000000000000000 SE                              /r /ua:0
SCGA SE                              SEMDEUICR                       00036038  0000000000001000 SE                              /ua:0
SCGA SE                              SEMDEUEUG                       00036050  0000000000000000 SE                              /w /ua:0
SCGA SE                              SEMDEUCMR_BA                    00036100  67452301EFCDAB89 SE                              /ua:0
SCGA SE                              SEMDEUKM_BA                     00036400  0000000000000000 SE                              /w /ua:0
SCGA SE                              SEMDEUFIFO                      00036800  0000000000000000 SE                              /w /ua:0
SCGA SE                              SEAFEUMR                        00038000  0000000000000000 SE                              /ua:0
SCGA SE                              SEAFEUKSR                       00038008  0000000000000000 SE                              /ua:0
SCGA SE                              SEAFEUDSR                       00038010  0000000000000000 SE                              /ua:0
SCGA SE                              SEAFEURCR                       00038018  0000000000000000 SE                              /ua:0
SCGA SE                              SEAFEUSR                        00038028  0000000000000001 SE                              /r /ua:0
SCGA SE                              SEAFEUISR                       00038030  0000000000000000 SE                              /r /ua:0
SCGA SE                              SEAFEUICR                       00038038  0000000000001000 SE                              /ua:0
SCGA SE                              SEAFEUEMR                       00038050  0000000000000000 SE                              /w /ua:0
SCGA SE                              SEAFEUCMR_BA                    00038100  0000000000000000 SE                              /ua:0
SCGA SE                              SEAFEUCMP_BA                    00038200  0000000000000000 SE                              /ua:0
SCGA SE                              SEAFEUK1                        00038400  0000000000000000 SE                              /w /ua:0
SCGA SE                              SEAFEUK2                        00038408  0000000000000000 SE                              /w /ua:0
SCGA SE                              SEAFEUFIFO                      00038800  0000000000000000 SE                              /ua:0
SCGA SE                              SERNGMR                         0003A000  0000000000000000 SE                              /ua:0
SCGA SE                              SERNGDSR                        0003A010  0000000000000000 SE                              /ua:0
SCGA SE                              SERNGRCR                        0003A018  0000000000000000 SE                              /ua:0
SCGA SE                              SERNGSR                         0003A028  0000000000000301 SE                              /r /ua:0
SCGA SE                              SERNGISR                        0003A030  0000000000000000 SE                              /r /ua:0
SCGA SE                              SERNGICR                        0003A038  0000000000001000 SE                              /ua:0
SCGA SE                              SERNGEUG                        0003A050  0000000000000000 SE                              /w /ua:0
SCGA SE                              SERNGFIFO                       0003A800  0000000000000000 SE                              /r /ua:0
SCGA SE                              SEPKEUMR                        0003C000  0000000000000000 SE                              /ua:0
SCGA SE                              SEPKEUKSR                       0003C008  0000000000000000 SE                              /ua:0
SCGA SE                              SEPKEUDSR                       0003C010  0000000000000000 SE                              /ua:0
SCGA SE                              SEPKEURCR                       0003C018  0000000000000000 SE                              /ua:0
SCGA SE                              SEPKEUSR                        0003C028  0000000000000001 SE                              /r /ua:0
SCGA SE                              SEPKEUISR                       0003C030  0000000000000000 SE                              /r /ua:0
SCGA SE                              SEPKEUICR                       0003C038  0000000000001000 SE                              /ua:0
SCGA SE                              SEPKEUABS                       0003C040  0000000000000000 SE                              /ua:0
SCGA SE                              SEPKEUEUG                       0003C050  0000000000000000 SE                              /w /ua:0
SCGA SE                              SEPKEUPMA0_BA                   0003C200  0000000000000000 SE                              /ua:0
SCGA SE                              SEPKEUPMA1_BA                   0003C240  0000000000000000 SE                              /ua:0
SCGA SE                              SEPKEUPMA2_BA                   0003C280  0000000000000000 SE                              /ua:0
SCGA SE                              SEPKEUPMA3_BA                   0003C2C0  0000000000000000 SE                              /ua:0
SCGA SE                              SEPKEUPMB0_BA                   0003C300  0000000000000000 SE                              /ua:0
SCGA SE                              SEPKEUPMB1_BA                   0003C340  0000000000000000 SE                              /ua:0
SCGA SE                              SEPKEUPMB2_BA                   0003C380  0000000000000000 SE                              /ua:0
SCGA SE                              SEPKEUPMB3_BA                   0003C3C0  0000000000000000 SE                              /ua:0
SCGA SE                              SEPKEUPME_BA                    0003C400  0000000000000000 SE                              /w /ua:0
SCGA SE                              SEPKEUPMN_BA                    0003C800  0000000000000000 SE                              /ua:0
SCGA PIC                             IPIDR0                          00040040  00000000 PIC                             /w /ua:0
SCGA PIC                             IPIDR1                          00040050  00000000 PIC                             /w /ua:0
SCGA PIC                             IPIDR2                          00040060  00000000 PIC                             /w /ua:0
SCGA PIC                             IPIDR3                          00040070  00000000 PIC                             /w /ua:0
SCGA PIC                             CTPR                            00040080  00000000 PIC                             /ua:0
SCGA PIC                             WHOAMI                          00040090  00000003 PIC                             /r /ua:0
SCGA PIC                             IACK                            000400A0  00000000 PIC                             /r /ua:0
SCGA PIC                             EOI                             000400B0  00000000 PIC                             /w /ua:0
SCGA PIC                             FRR                             00041000  004F0002 PIC                             /r /ua:0
SCGA PIC                             GCR                             00041020  00000000 PIC                             /ua:0
SCGA PIC                             VIR                             00041080  00000000 PIC                             /r /ua:0
SCGA PIC                             PINITR                          00041090  00000000 PIC                             /ua:0
SCGA PIC                             IPIVPR0                         000410A0  80000000 PIC                             /ua:0
SCGA PIC                             IPIVPR1                         000410B0  80000000 PIC                             /ua:0
SCGA PIC                             IPIVPR2                         000410C0  80000000 PIC                             /ua:0
SCGA PIC                             IPIVPR3                         000410D0  80000000 PIC                             /ua:0
SCGA PIC                             SVR                             000410E0  0000FFFF PIC                             /ua:0
SCGA PIC                             TFRR                            000410F0  00000000 PIC                             /ua:0
SCGA PIC                             GTCCR0                          00041100  00000000 PIC                             /r /ua:0
SCGA PIC                             GTBCR0                          00041110  80000000 PIC                             /ua:0
SCGA PIC                             GTVPR0                          00041120  80000000 PIC                             /ua:0
SCGA PIC                             GTDR0                           00041130  00000001 PIC                             /ua:0
SCGA PIC                             GTCCR1                          00041140  00000000 PIC                             /r /ua:0
SCGA PIC                             GTBCR1                          00041150  80000000 PIC                             /ua:0
SCGA PIC                             GTVPR1                          00041160  80000000 PIC                             /ua:0
SCGA PIC                             GTDR1                           00041170  00000001 PIC                             /ua:0
SCGA PIC                             GTCCR2                          00041180  00000000 PIC                             /r /ua:0
SCGA PIC                             GTBCR2                          00041190  80000000 PIC                             /ua:0
SCGA PIC                             GTVPR2                          000411A0  80000000 PIC                             /ua:0
SCGA PIC                             GTDR2                           000411B0  00000001 PIC                             /ua:0
SCGA PIC                             GTCCR3                          000411C0  00000000 PIC                             /r /ua:0
SCGA PIC                             GTBCR3                          000411D0  80000000 PIC                             /ua:0
SCGA PIC                             GTVPR3                          000411E0  80000000 PIC                             /ua:0
SCGA PIC                             GTDR3                           000411F0  00000001 PIC                             /ua:0
SCGA PIC                             TCTRLR                          00041300  00000000 PIC                             /ua:0
SCGA PIC                             IRQSR0                          00041310  00000000 PIC                             /r /ua:0
SCGA PIC                             IRQSR1                          00041320  00000000 PIC                             /r /ua:0
SCGA PIC                             CISR0                           00041330  00000000 PIC                             /r /ua:0
SCGA PIC                             CISR1                           00041340  00000000 PIC                             /r /ua:0
SCGA PIC                             PM0MR0                          00041350  00FFFFFF PIC                             /ua:0
SCGA PIC                             PM0MR1                          00041360  FFFFFFFF PIC                             /ua:0
SCGA PIC                             PM1MR0                          00041370  00FFFFFF PIC                             /ua:0
SCGA PIC                             PM1MR1                          00041380  FFFFFFFF PIC                             /ua:0
SCGA PIC                             PM2MR0                          00041390  00FFFFFF PIC                             /ua:0
SCGA PIC                             PM2MR1                          000413A0  FFFFFFFF PIC                             /ua:0
SCGA PIC                             PM3MR0                          000413B0  00FFFFFF PIC                             /ua:0
SCGA PIC                             PM3MR1                          000413C0  FFFFFFFF PIC                             /ua:0
SCGA PIC                             MSGR0                           00041400  00000000 PIC                             /ua:0
SCGA PIC                             MSGR1                           00041410  00000000 PIC                             /ua:0
SCGA PIC                             MSGR2                           00041420  00000000 PIC                             /ua:0
SCGA PIC                             MSGR3                           00041430  00000000 PIC                             /ua:0
SCGA PIC                             MSGER                           00041500  00000000 PIC                             /ua:0
SCGA PIC                             MSGSR                           00041510  00000000 PIC                             /ua:0
SCGA PIC                             EIVPR0                          00050000  80000000 PIC                             /ua:0
SCGA PIC                             EIDR0                           00050010  00000001 PIC                             /ua:0
SCGA PIC                             EIVPR1                          00050020  80000000 PIC                             /ua:0
SCGA PIC                             EIDR1                           00050030  00000001 PIC                             /ua:0
SCGA PIC                             EIVPR2                          00050040  80000000 PIC                             /ua:0
SCGA PIC                             EIDR2                           00050050  00000001 PIC                             /ua:0
SCGA PIC                             EIVPR3                          00050060  80000000 PIC                             /ua:0
SCGA PIC                             EIDR3                           00050070  00000001 PIC                             /ua:0
SCGA PIC                             EIVPR4                          00050080  80000000 PIC                             /ua:0
SCGA PIC                             EIDR4                           00050090  00000001 PIC                             /ua:0
SCGA PIC                             EIVPR5                          000500A0  80000000 PIC                             /ua:0
SCGA PIC                             EIDR5                           000500B0  00000001 PIC                             /ua:0
SCGA PIC                             EIVPR6                          000500C0  80000000 PIC                             /ua:0
SCGA PIC                             EIDR6                           000500D0  00000001 PIC                             /ua:0
SCGA PIC                             EIVPR7                          000500E0  80000000 PIC                             /ua:0
SCGA PIC                             EIDR7                           000500F0  00000001 PIC                             /ua:0
SCGA PIC                             EIVPR8                          00050100  80000000 PIC                             /ua:0
SCGA PIC                             EIDR8                           00050110  00000001 PIC                             /ua:0
SCGA PIC                             EIVPR9                          00050120  80000000 PIC                             /ua:0
SCGA PIC                             EIDR9                           00050130  00000001 PIC                             /ua:0
SCGA PIC                             EIVPR10                         00050140  80000000 PIC                             /ua:0
SCGA PIC                             EIDR10                          00050150  00000001 PIC                             /ua:0
SCGA PIC                             EIVPR11                         00050160  80000000 PIC                             /ua:0
SCGA PIC                             EIDR11                          00050170  00000001 PIC                             /ua:0
SCGA PIC                             IIVPR0                          00050200  80800000 PIC                             /ua:0
SCGA PIC                             IIDR0                           00050210  00000001 PIC                             /ua:0
SCGA PIC                             IIVPR1                          00050220  80800000 PIC                             /ua:0
SCGA PIC                             IIDR1                           00050230  00000001 PIC                             /ua:0
SCGA PIC                             IIVPR2                          00050240  80800000 PIC                             /ua:0
SCGA PIC                             IIDR2                           00050250  00000001 PIC                             /ua:0
SCGA PIC                             IIVPR3                          00050260  80800000 PIC                             /ua:0
SCGA PIC                             IIDR3                           00050270  00000001 PIC                             /ua:0
SCGA PIC                             IIVPR4                          00050280  80800000 PIC                             /ua:0
SCGA PIC                             IIDR4                           00050290  00000001 PIC                             /ua:0
SCGA PIC                             IIVPR5                          000502A0  80800000 PIC                             /ua:0
SCGA PIC                             IIDR5                           000502B0  00000001 PIC                             /ua:0
SCGA PIC                             IIVPR6                          000502C0  80800000 PIC                             /ua:0
SCGA PIC                             IIDR6                           000502D0  00000001 PIC                             /ua:0
SCGA PIC                             IIVPR7                          000502E0  80800000 PIC                             /ua:0
SCGA PIC                             IIDR7                           000502F0  00000001 PIC                             /ua:0
SCGA PIC                             IIVPR8                          00050300  80800000 PIC                             /ua:0
SCGA PIC                             IIDR8                           00050310  00000001 PIC                             /ua:0
SCGA PIC                             IIVPR9                          00050320  80800000 PIC                             /ua:0
SCGA PIC                             IIDR9                           00050330  00000001 PIC                             /ua:0
SCGA PIC                             IIVPR10                         00050340  80800000 PIC                             /ua:0
SCGA PIC                             IIDR10                          00050350  00000001 PIC                             /ua:0
SCGA PIC                             IIVPR11                         00050360  80800000 PIC                             /ua:0
SCGA PIC                             IIDR11                          00050370  00000001 PIC                             /ua:0
SCGA PIC                             IIVPR12                         00050380  80800000 PIC                             /ua:0
SCGA PIC                             IIDR12                          00050390  00000001 PIC                             /ua:0
SCGA PIC                             IIVPR13                         000503A0  80800000 PIC                             /ua:0
SCGA PIC                             IIDR13                          000503B0  00000001 PIC                             /ua:0
SCGA PIC                             IIVPR14                         000503C0  80800000 PIC                             /ua:0
SCGA PIC                             IIDR14                          000503D0  00000001 PIC                             /ua:0
SCGA PIC                             IIVPR15                         000503E0  80800000 PIC                             /ua:0
SCGA PIC                             IIDR15                          000503F0  00000001 PIC                             /ua:0
SCGA PIC                             IIVPR16                         00050400  80800000 PIC                             /ua:0
SCGA PIC                             IIDR16                          00050410  00000001 PIC                             /ua:0
SCGA PIC                             IIVPR17                         00050420  80800000 PIC                             /ua:0
SCGA PIC                             IIDR17                          00050430  00000001 PIC                             /ua:0
SCGA PIC                             IIVPR18                         00050440  80800000 PIC                             /ua:0
SCGA PIC                             IIDR18                          00050450  00000001 PIC                             /ua:0
SCGA PIC                             IIVPR19                         00050460  80800000 PIC                             /ua:0
SCGA PIC                             IIDR19                          00050470  00000001 PIC                             /ua:0
SCGA PIC                             IIVPR20                         00050480  80800000 PIC                             /ua:0
SCGA PIC                             IIDR20                          00050490  00000001 PIC                             /ua:0
SCGA PIC                             IIVPR21                         000504A0  80800000 PIC                             /ua:0
SCGA PIC                             IIDR21                          000504B0  00000001 PIC                             /ua:0
SCGA PIC                             IIVPR22                         000504C0  80800000 PIC                             /ua:0
SCGA PIC                             IIDR22                          000504D0  00000001 PIC                             /ua:0
SCGA PIC                             IIVPR23                         000504E0  80800000 PIC                             /ua:0
SCGA PIC                             IIDR23                          000504F0  00000001 PIC                             /ua:0
SCGA PIC                             IIVPR24                         00050500  80800000 PIC                             /ua:0
SCGA PIC                             IIDR24                          00050510  00000001 PIC                             /ua:0
SCGA PIC                             IIVPR25                         00050520  80800000 PIC                             /ua:0
SCGA PIC                             IIDR25                          00050530  00000001 PIC                             /ua:0
SCGA PIC                             IIVPR26                         00050540  80800000 PIC                             /ua:0
SCGA PIC                             IIDR26                          00050550  00000001 PIC                             /ua:0
SCGA PIC                             IIVPR27                         00050560  80800000 PIC                             /ua:0
SCGA PIC                             IIDR27                          00050570  00000001 PIC                             /ua:0
SCGA PIC                             IIVPR28                         00050580  80800000 PIC                             /ua:0
SCGA PIC                             IIDR28                          00050590  00000001 PIC                             /ua:0
SCGA PIC                             IIVPR29                         000505A0  80800000 PIC                             /ua:0
SCGA PIC                             IIDR29                          000505B0  00000001 PIC                             /ua:0
SCGA PIC                             IIVPR30                         000505C0  80800000 PIC                             /ua:0
SCGA PIC                             IIDR30                          000505D0  00000001 PIC                             /ua:0
SCGA PIC                             IIVPR31                         000505E0  80800000 PIC                             /ua:0
SCGA PIC                             IIDR31                          000505F0  00000001 PIC                             /ua:0
SCGA PIC                             MIVPR0                          00051600  80000000 PIC                             /ua:0
SCGA PIC                             MIDR0                           00051610  00000001 PIC                             /ua:0
SCGA PIC                             MIVPR1                          00051620  80000000 PIC                             /ua:0
SCGA PIC                             MIDR1                           00051630  00000001 PIC                             /ua:0
SCGA PIC                             MIVPR2                          00051640  80000000 PIC                             /ua:0
SCGA PIC                             MIDR2                           00051650  00000001 PIC                             /ua:0
SCGA PIC                             MIVPR3                          00051660  80000000 PIC                             /ua:0
SCGA PIC                             MIDR3                           00051670  00000001 PIC                             /ua:0
SCGA PIC                             P0IPIDR0                        00060040  00000000 PIC                             /w /ua:0
SCGA PIC                             P0IPIDR1                        00060050  00000000 PIC                             /w /ua:0
SCGA PIC                             P0IPIDR2                        00060060  00000000 PIC                             /w /ua:0
SCGA PIC                             P0IPIDR3                        00060070  00000000 PIC                             /w /ua:0
SCGA PIC                             CTPR0                           00060080  0000000F PIC                             /ua:0
SCGA PIC                             WHOAMI0                         00060090  00000003 PIC                             /r /ua:0
SCGA PIC                             IACK0                           000600A0  0000FFFF PIC                             /r /ua:0
SCGA PIC                             EOI0                            000600B0  00000000 PIC                             /w /ua:0
SCGA UPMA                            UPMA_T0                         00005088  00000000 UPMA                            /tclr:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T1                         00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T2                         00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T3                         00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T4                         00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T5                         00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T6                         00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T7                         00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T8                         00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T9                         00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T10                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T11                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T12                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T13                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T14                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T15                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T16                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T17                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T18                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T19                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T20                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T21                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T22                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T23                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T24                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T25                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T26                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T27                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T28                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T29                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T30                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T31                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T32                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T33                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T34                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T35                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T36                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T37                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T38                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T39                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T40                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T41                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T42                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T43                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T44                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T45                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T46                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T47                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T48                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T49                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T50                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T51                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T52                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T53                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T54                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T55                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T56                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T57                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T58                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T59                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T60                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T61                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T62                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMA                            UPMA_T63                        00005088  00000000 UPMA                            /tp1:3 /ua:0 /ue:3
SCGA UPMB                            UPMB_T0                         00005088  00000000 UPMB                            /tclr:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T1                         00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T2                         00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T3                         00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T4                         00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T5                         00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T6                         00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T7                         00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T8                         00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T9                         00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T10                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T11                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T12                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T13                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T14                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T15                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T16                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T17                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T18                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T19                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T20                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T21                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T22                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T23                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T24                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T25                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T26                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T27                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T28                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T29                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T30                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T31                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T32                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T33                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T34                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T35                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T36                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T37                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T38                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T39                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T40                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T41                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T42                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T43                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T44                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T45                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T46                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T47                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T48                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T49                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T50                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T51                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T52                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T53                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T54                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T55                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T56                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T57                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T58                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T59                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T60                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T61                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T62                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMB                            UPMB_T63                        00005088  00000000 UPMB                            /tp1:4 /ua:0 /ue:4
SCGA UPMC                            UPMC_T0                         00005088  00000000 UPMC                            /tclr:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T1                         00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T2                         00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T3                         00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T4                         00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T5                         00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T6                         00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T7                         00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T8                         00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T9                         00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T10                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T11                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T12                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T13                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T14                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T15                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T16                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T17                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T18                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T19                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T20                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T21                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T22                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T23                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T24                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T25                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T26                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T27                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T28                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T29                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T30                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T31                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T32                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T33                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T34                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T35                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T36                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T37                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T38                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T39                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T40                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T41                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T42                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T43                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T44                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T45                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T46                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T47                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T48                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T49                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T50                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T51                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T52                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T53                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T54                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T55                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T56                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T57                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T58                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T59                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T60                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T61                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T62                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA UPMC                            UPMC_T63                        00005088  00000000 UPMC                            /tp1:5 /ua:0 /ue:5
SCGA CPMIC                           SICR                            00090C00  0000     CPMIC                           /ua:0
SCGA CPMIC                           SIVEC                           00090C04  00000000 CPMIC                           /ua:0
SCGA CPMIC                           SIPNR_H                         00090C08  00000000 CPMIC                           /ua:0
SCGA CPMIC                           SIPNR_L                         00090C0C  00000000 CPMIC                           /ua:0
SCGA CPMIC                           SCPRR_H                         00090C14  00000000 CPMIC                           /ua:0
SCGA CPMIC                           SCPRR_L                         00090C18  00000000 CPMIC                           /ua:0
SCGA CPMIC                           SIMR_H                          00090C1C  00000000 CPMIC                           /ua:0
SCGA CPMIC                           SIMR_L                          00090C20  00000000 CPMIC                           /ua:0
SCGA CPMIC                           SIEXR                           00090C24  00000000 CPMIC                           /ua:0
SCGA IOPORTS                         PDIRA                           00090D00  00000000 IOPORTS                         /ua:0
SCGA IOPORTS                         PPARA                           00090D04  00000000 IOPORTS                         /ua:0
SCGA IOPORTS                         PSORA                           00090D08  00000000 IOPORTS                         /ua:0
SCGA IOPORTS                         PODRA                           00090D0C  00000000 IOPORTS                         /ua:0
SCGA IOPORTS                         PDATA                           00090D10  00000000 IOPORTS                         /ua:0
SCGA IOPORTS                         PDIRB                           00090D20  00000000 IOPORTS                         /ua:0
SCGA IOPORTS                         PPARB                           00090D24  00000000 IOPORTS                         /ua:0
SCGA IOPORTS                         PSORB                           00090D28  00000000 IOPORTS                         /ua:0
SCGA IOPORTS                         PODRB                           00090D2C  00000000 IOPORTS                         /ua:0
SCGA IOPORTS                         PDATB                           00090D30  00000000 IOPORTS                         /ua:0
SCGA IOPORTS                         PDIRC                           00090D40  00000000 IOPORTS                         /ua:0
SCGA IOPORTS                         PPARC                           00090D44  00000000 IOPORTS                         /ua:0
SCGA IOPORTS                         PSORC                           00090D48  00000000 IOPORTS                         /ua:0
SCGA IOPORTS                         PODRC                           00090D4C  00000000 IOPORTS                         /ua:0
SCGA IOPORTS                         PDATC                           00090D50  00000000 IOPORTS                         /ua:0
SCGA IOPORTS                         PDIRD                           00090D60  00000000 IOPORTS                         /ua:0
SCGA IOPORTS                         PPARD                           00090D64  00000000 IOPORTS                         /ua:0
SCGA IOPORTS                         PSORD                           00090D68  00000000 IOPORTS                         /ua:0
SCGA IOPORTS                         PODRD                           00090D6C  00000000 IOPORTS                         /ua:0
SCGA IOPORTS                         PDATD                           00090D70  00000000 IOPORTS                         /ua:0
SCGA CPMTIMERS                       TGCR1                           00090D80  00       CPMTIMERS                       /ua:0
SCGA CPMTIMERS                       TGCR2                           00090D84  00       CPMTIMERS                       /ua:0
SCGA CPMTIMERS                       TMR1                            00090D90  0000     CPMTIMERS                       /ua:0
SCGA CPMTIMERS                       TMR2                            00090D92  0000     CPMTIMERS                       /ua:0
SCGA CPMTIMERS                       TRR1                            00090D94  0000     CPMTIMERS                       /ua:0
SCGA CPMTIMERS                       TRR2                            00090D96  0000     CPMTIMERS                       /ua:0
SCGA CPMTIMERS                       TCR1                            00090D98  0000     CPMTIMERS                       /ua:0
SCGA CPMTIMERS                       TCR2                            00090D9A  0000     CPMTIMERS                       /ua:0
SCGA CPMTIMERS                       TCN1                            00090D9C  0000     CPMTIMERS                       /ua:0
SCGA CPMTIMERS                       TCN2                            00090D9E  0000     CPMTIMERS                       /ua:0
SCGA CPMTIMERS                       TMR3                            00090DA0  0000     CPMTIMERS                       /ua:0
SCGA CPMTIMERS                       TMR4                            00090DA2  0000     CPMTIMERS                       /ua:0
SCGA CPMTIMERS                       TRR3                            00090DA4  0000     CPMTIMERS                       /ua:0
SCGA CPMTIMERS                       TRR4                            00090DA6  0000     CPMTIMERS                       /ua:0
SCGA CPMTIMERS                       TCR3                            00090DA8  0000     CPMTIMERS                       /ua:0
SCGA CPMTIMERS                       TCR4                            00090DAA  0000     CPMTIMERS                       /ua:0
SCGA CPMTIMERS                       TCN3                            00090DAC  0000     CPMTIMERS                       /ua:0
SCGA CPMTIMERS                       TCN4                            00090DAE  0000     CPMTIMERS                       /ua:0
SCGA CPMTIMERS                       TER1                            00090DB0  0000     CPMTIMERS                       /ua:0
SCGA CPMTIMERS                       TER2                            00090DB2  0000     CPMTIMERS                       /ua:0
SCGA CPMTIMERS                       TER3                            00090DB4  0000     CPMTIMERS                       /ua:0
SCGA CPMTIMERS                       TER4                            00090DB6  0000     CPMTIMERS                       /ua:0
SCGA CI                              CEAR                            00090000  00000000 CI                              /r /ua:0
SCGA CI                              CEER                            00090004  0000     CI                              /ua:0
SCGA CI                              CEMR                            00090006  0000     CI                              /ua:0
SCGA SDMA                            SDSR                            00091018  00       SDMA                            /ua:0
SCGA SDMA                            SDMR                            0009101C  00       SDMA                            /ua:0
SCGA SDMA                            SMAER                           00090050  00000000 SDMA                            /r /ua:0
SCGA SDMA                            SMSER                           00090054  00000000 SDMA                            /r /ua:0
SCGA SDMA                            SMEVR                           00090058  00000000 SDMA                            /ua:0
SCGA SDMA                            LMAER                           00090060  00000000 SDMA                            /r /ua:0
SCGA SDMA                            LMSER                           00090064  00000000 SDMA                            /r /ua:0
SCGA SDMA                            LMEVR                           00090068  00000000 SDMA                            /ua:0
SCGA FCC                             GFMR1                           00091300  00000000 FCC                             /ua:0
SCGA FCC                             FPSMR1                          00091304  00000000 FCC                             /ua:0
SCGA FCC                             FTODR1                          00091308  0000     FCC                             /ua:0
SCGA FCC                             FDSR1                           0009130C  0000     FCC                             /ua:0
SCGA FCC                             FCCE1                           00091310  00000000 FCC                             /ua:0
SCGA FCC                             FCCM1                           00091314  00000000 FCC                             /ua:0
SCGA FCC                             FCCS1                           00091318  00       FCC                             /ua:0
SCGA FCC                             FTIRR1_PHY0                     0009131C  00       FCC                             /ua:0
SCGA FCC                             FTIRR1_PHY1                     0009131D  00       FCC                             /ua:0
SCGA FCC                             FTIRR1_PHY2                     0009131E  00       FCC                             /ua:0
SCGA FCC                             FTIRR1_PHY3                     0009131F  00       FCC                             /ua:0
SCGA FCC                             FIRPER1                         00091380  00000000 FCC                             /ua:0
SCGA FCC                             FIRER1                          00091384  00000000 FCC                             /ua:0
SCGA FCC                             FIRSR1_HI                       00091388  00000000 FCC                             /ua:0
SCGA FCC                             FIRSR1_LO                       0009138C  00000000 FCC                             /ua:0
SCGA FCC                             GFEMR1                          00091390  00       FCC                             /ua:0
SCGA FCC                             GFMR2                           00091320  00000000 FCC                             /ua:0
SCGA FCC                             FPSMR2                          00091324  00000000 FCC                             /ua:0
SCGA FCC                             FTODR2                          00091328  0000     FCC                             /ua:0
SCGA FCC                             FDSR2                           0009132C  0000     FCC                             /ua:0
SCGA FCC                             FCCE2                           00091330  00000000 FCC                             /ua:0
SCGA FCC                             FCCM2                           00091334  00000000 FCC                             /ua:0
SCGA FCC                             FCCS2                           00091338  00       FCC                             /ua:0
SCGA FCC                             FTIRR2_PHY0                     0009133C  00       FCC                             /ua:0
SCGA FCC                             FTIRR2_PHY1                     0009133D  00       FCC                             /ua:0
SCGA FCC                             FTIRR2_PHY2                     0009133E  00       FCC                             /ua:0
SCGA FCC                             FTIRR2_PHY3                     0009133F  00       FCC                             /ua:0
SCGA FCC                             FIRPER2                         000913A0  00000000 FCC                             /ua:0
SCGA FCC                             FIRER2                          000913A4  00000000 FCC                             /ua:0
SCGA FCC                             FIRSR2_HI                       000913A8  00000000 FCC                             /ua:0
SCGA FCC                             FIRSR2_LO                       000913AC  00000000 FCC                             /ua:0
SCGA FCC                             GFEMR2                          000913B0  00       FCC                             /ua:0
SCGA USB                             USMOD                           00091B60  00       USB                             /ua:0
SCGA USB                             USADR                           00091B61  00       USB                             /ua:0
SCGA USB                             USCOM                           00091B62  00       USB                             /ua:0
SCGA USB                             USEP1                           00091B64  0000     USB                             /ua:0
SCGA USB                             USEP2                           00091B66  0000     USB                             /ua:0
SCGA USB                             USEP3                           00091B68  0000     USB                             /ua:0
SCGA USB                             USEP4                           00091B6A  0000     USB                             /ua:0
SCGA USB                             USBER                           00091B70  0000     USB                             /ua:0
SCGA USB                             USBMR                           00091B74  0000     USB                             /ua:0
SCGA USB                             USBS                            00091B77  00       USB                             /ua:0
SCGA CPMI2C_SPI                      I2MOD                           00091860  00       CPMI2C_SPI                      /ua:0
SCGA CPMI2C_SPI                      I2ADD                           00091864  00       CPMI2C_SPI                      /ua:0
SCGA CPMI2C_SPI                      I2BRG                           00091868  00       CPMI2C_SPI                      /ua:0
SCGA CPMI2C_SPI                      I2COM                           0009186C  00       CPMI2C_SPI                      /ua:0
SCGA CPMI2C_SPI                      I2CER                           00091870  00       CPMI2C_SPI                      /ua:0
SCGA CPMI2C_SPI                      I2CMR                           00091874  00       CPMI2C_SPI                      /ua:0
SCGA CPMI2C_SPI                      SPMODE                          00091AA0  0000     CPMI2C_SPI                      /ua:0
SCGA CPMI2C_SPI                      SPIE                            00091AA6  00       CPMI2C_SPI                      /ua:0
SCGA CPMI2C_SPI                      SPIM                            00091AAA  00       CPMI2C_SPI                      /ua:0
SCGA CPMI2C_SPI                      SPCOM                           00091AAD  00       CPMI2C_SPI                      /w /ua:0
SCGA COMM                            CPCR                            000919C0  00000000 COMM                            /ua:0
SCGA COMM                            RCCR                            000919C4  00000000 COMM                            /ua:0
SCGA COMM                            RTER                            000919D6  0000     COMM                            /ua:0
SCGA COMM                            RTMR                            000919DA  0000     COMM                            /ua:0
SCGA COMM                            RTSCR                           000919DC  0000     COMM                            /ua:0
SCGA COMM                            RTSR                            000919E0  0000     COMM                            /ua:0
SCGA COMM                            SCCR                            00090C80  00000000 COMM                            /ua:0
SCGA COMM                            BRGC1                           000919F0  00000000 COMM                            /ua:0
SCGA COMM                            BRGC2                           000919F4  00000000 COMM                            /ua:0
SCGA COMM                            BRGC3                           000919F8  00000000 COMM                            /ua:0
SCGA COMM                            BRGC4                           000919FC  00000000 COMM                            /ua:0
SCGA COMM                            BRGC5                           000915F0  00000000 COMM                            /ua:0
SCGA COMM                            BRGC6                           000915F4  00000000 COMM                            /ua:0
SCGA COMM                            BRGC7                           000915F8  00000000 COMM                            /ua:0
SCGA COMM                            BRGC8                           000915FC  00000000 COMM                            /ua:0
SCGA COMM                            GSMR_L1                         00091A00  00000000 COMM                            /ua:0
SCGA COMM                            GSMR_H1                         00091A04  00000000 COMM                            /ua:0
SCGA COMM                            PSMR1                           00091A08  0000     COMM                            /ua:0
SCGA COMM                            TODR1                           00091A0C  0000     COMM                            /ua:0
SCGA COMM                            DSR1                            00091A0E  0000     COMM                            /ua:0
SCGA COMM                            SCCE1                           00091A10  0000     COMM                            /ua:0
SCGA COMM                            SCCM1                           00091A14  0000     COMM                            /ua:0
SCGA COMM                            SCCS1                           00091A17  00       COMM                            /ua:0
SCGA COMM                            GSMR_L3                         00091A40  00000000 COMM                            /ua:0
SCGA COMM                            GSMR_H3                         00091A44  00000000 COMM                            /ua:0
SCGA COMM                            PSMR3                           00091A48  0000     COMM                            /ua:0
SCGA COMM                            TODR3                           00091A4C  0000     COMM                            /ua:0
SCGA COMM                            DSR3                            00091A4E  0000     COMM                            /ua:0
SCGA COMM                            SCCE3                           00091A50  0000     COMM                            /ua:0
SCGA COMM                            SCCM3                           00091A54  0000     COMM                            /ua:0
SCGA COMM                            SCCS3                           00091A57  00       COMM                            /ua:0
SCGA COMM                            GSMR_L4                         00091A60  00000000 COMM                            /ua:0
SCGA COMM                            GSMR_H4                         00091A64  00000000 COMM                            /ua:0
SCGA COMM                            PSMR4                           00091A68  0000     COMM                            /ua:0
SCGA COMM                            TODR4                           00091A6C  0000     COMM                            /ua:0
SCGA COMM                            DSR4                            00091A6E  0000     COMM                            /ua:0
SCGA COMM                            SCCE4                           00091A70  0000     COMM                            /ua:0
SCGA COMM                            SCCM4                           00091A74  0000     COMM                            /ua:0
SCGA COMM                            SCCS4                           00091A77  00       COMM                            /ua:0
SCGA COMM                            SMCMR1                          00091A82  0000     COMM                            /ua:0
SCGA COMM                            SMCE1                           00091A86  00       COMM                            /ua:0
SCGA COMM                            SMCM1                           00091A8A  00       COMM                            /ua:0
SCGA COMM                            SMCMR2                          00091A92  0000     COMM                            /ua:0
SCGA COMM                            SMCE2                           00091A96  00       COMM                            /ua:0
SCGA COMM                            SMCM2                           00091A9A  00       COMM                            /ua:0
SCGA CPMUX                           CMXSI1CR                        00091B0C  00       CPMUX                           /ua:0
SCGA CPMUX                           CMXSI2CR                        00091B02  00       CPMUX                           /ua:0
SCGA CPMUX                           CMXFCR                          00091B04  00000000 CPMUX                           /ua:0
SCGA CPMUX                           CMXSCR                          00091B08  00000000 CPMUX                           /ua:0
SCGA CPMUX                           CMXUAR                          00091B0E  0000     CPMUX                           /ua:0
SCGA SI                              SI2AMR                          00091B40  0000     SI                              /ua:0
SCGA SI                              SI2BMR                          00091B42  0000     SI                              /ua:0
SCGA SI                              SI2CMR                          00091B44  0000     SI                              /ua:0
SCGA SI                              SI2GMR                          00091B48  00       SI                              /ua:0
SCGA SI                              SI2CMDR                         00091B4A  00       SI                              /ua:0
SCGA SI                              SI2STR                          00091B4C  00       SI                              /ua:0
SCGA SI                              SI2RSR                          00091B4E  0000     SI                              /ua:0
SCGA GLOBU                           PORPLLSR                        000E0000  00C5C014 GLOBU                           /r /ua:0
SCGA GLOBU                           PORBMSR                         000E0004  86370000 GLOBU                           /r /ua:0
SCGA GLOBU                           PORIMPSCR                       000E0008  0003007F GLOBU                           /ua:0
SCGA GLOBU                           PORDEVSR                        000E000C  C2A5EF67 GLOBU                           /r /ua:0
SCGA GLOBU                           PORDBGMSR                       000E0010  0F000000 GLOBU                           /r /ua:0
SCGA GLOBU                           GPPORCR                         000E0020  FFFFFFFF GLOBU                           /r /ua:0
SCGA GLOBU                           GPIOCR                          000E0030  00000000 GLOBU                           /ua:0
SCGA GLOBU                           GPOUTDR                         000E0040  00000000 GLOBU                           /ua:0
SCGA GLOBU                           GPINDR                          000E0050  00000000 GLOBU                           /r /ua:0
SCGA GLOBU                           PMUXCR                          000E0060  00000000 GLOBU                           /ua:0
SCGA GLOBU                           DEVDISR                         000E0070  50000010 GLOBU                           /ua:0
SCGA GLOBU                           POWMGTCSR                       000E0080  00000000 GLOBU                           /ua:0
SCGA GLOBU                           MCPSUMR                         000E0090  00000002 GLOBU                           /r /ua:0
SCGA GLOBU                           GUPVR                           000E00A0  80210010 GLOBU                           /r /ua:0
SCGA GLOBU                           GUSVR                           000E00A4  80390010 GLOBU                           /r /ua:0
SCGA GLOBU                           CLKOCR                          000E0E00  00000000 GLOBU                           /ua:0
SCGA GLOBU                           DDRDLLCR                        000E0E10  00000000 GLOBU                           /ua:0
SCGA GLOBU                           LBDLLCR                         000E0E20  00000000 GLOBU                           /ua:0
SCGA PM                              PMGCR                           000E1000  00000000 PM                              /ua:0
SCGA PM                              PMLCRA0                         000E1010  00000000 PM                              /ua:0
SCGA PM                              PMLCRB0                         000E1014  00000000 PM                              /ua:0
SCGA PM                              PMCR0                           000E1018  5034EAC8 PM                              /ua:0
SCGA PM                              PMCREX0                         000E101C  00000001 PM                              /ua:0
SCGA PM                              PMLCRA1                         000E1020  00000000 PM                              /ua:0
SCGA PM                              PMLCRB1                         000E1024  00000000 PM                              /ua:0
SCGA PM                              PMCR1                           000E1028  00000000 PM                              /ua:0
SCGA PM                              PMLCRA2                         000E1030  00000000 PM                              /ua:0
SCGA PM                              PMLCRB2                         000E1034  00000000 PM                              /ua:0
SCGA PM                              PMCR2                           000E1038  00000000 PM                              /ua:0
SCGA PM                              PMLCRA3                         000E1040  00000000 PM                              /ua:0
SCGA PM                              PMLCRB3                         000E1044  00000000 PM                              /ua:0
SCGA PM                              PMCR3                           000E1048  00000000 PM                              /ua:0
SCGA PM                              PMLCRA4                         000E1050  00000000 PM                              /ua:0
SCGA PM                              PMLCRB4                         000E1054  00000000 PM                              /ua:0
SCGA PM                              PMCR4                           000E1058  00000000 PM                              /ua:0
SCGA PM                              PMLCRA5                         000E1060  00000000 PM                              /ua:0
SCGA PM                              PMLCRB5                         000E1064  00000000 PM                              /ua:0
SCGA PM                              PMCR5                           000E1068  00000000 PM                              /ua:0
SCGA PM                              PMLCRA6                         000E1070  00000000 PM                              /ua:0
SCGA PM                              PMLCRB6                         000E1074  00000000 PM                              /ua:0
SCGA PM                              PMCR6                           000E1078  00000000 PM                              /ua:0
SCGA PM                              PMLCRA7                         000E1080  00000000 PM                              /ua:0
SCGA PM                              PMLCRB7                         000E1084  00000000 PM                              /ua:0
SCGA PM                              PMCR7                           000E1088  00000000 PM                              /ua:0
SCGA PM                              PMLCRA8                         000E1090  00000000 PM                              /ua:0
SCGA PM                              PMLCRB8                         000E1094  00000000 PM                              /ua:0
SCGA PM                              PMCR8                           000E1098  00000000 PM                              /ua:0
SCGA WP                              WMCR0                           000E2000  00000000 WP                              /ua:0
SCGA WP                              WMCR1                           000E2004  00000000 WP                              /ua:0
SCGA WP                              WMAR                            000E200C  00000000 WP                              /ua:0
SCGA WP                              WMAMR                           000E2014  00000000 WP                              /ua:0
SCGA WP                              WMTMR                           000E2018  00000000 WP                              /ua:0
SCGA WP                              WMSR                            000E201C  00000000 WP                              /ua:0
SCGA WP                              TBCR0                           000E2040  00000000 WP                              /ua:0
SCGA WP                              TBCR1                           000E2044  00000000 WP                              /ua:0
SCGA WP                              TBAR                            000E204C  00000000 WP                              /ua:0
SCGA WP                              TBAMR                           000E2054  00000000 WP                              /ua:0
SCGA WP                              TBTMR                           000E2058  00000000 WP                              /ua:0
SCGA WP                              TBSR                            000E205C  00000000 WP                              /ua:0
SCGA WP                              TBACR                           000E2060  00000000 WP                              /ua:0
SCGA WP                              TBADHR                          000E2064  00000000 WP                              /ua:0
SCGA WP                              TBADR                           000E2068  00000000 WP                              /ua:0
SCGA WP                              PCIDR                           000E20A0  00000000 WP                              /ua:0
SCGA WP                              CCIDR                           000E20A4  00000000 WP                              /ua:0
SCGA WP                              TOSR                            000E20B0  00000000 WP                              /ua:0
SCGA WRLSDRAM                        LSDMR1                          00005094  2862A526 WRLSDRAM                        /wo /w /ua:0
SCGA WRLSDRAM                        DWR1_1                          20000000  FF       WRLSDRAM                        /wo /w
SCGA WRLSDRAM                        DWR1_2                          24000000  FF       WRLSDRAM                        /wo /w
SCGA WRLSDRAM                        LSDMR2                          00005094  0862A526 WRLSDRAM                        /wo /w /ua:0
SCGA WRLSDRAM                        DWR2_1                          20000000  FF       WRLSDRAM                        /wo /w
SCGA WRLSDRAM                        DWR2_2                          24000000  FF       WRLSDRAM                        /wo /w
SCGA WRLSDRAM                        DWR3_1                          20000000  FF       WRLSDRAM                        /wo /w
SCGA WRLSDRAM                        DWR3_2                          24000000  FF       WRLSDRAM                        /wo /w
SCGA WRLSDRAM                        DWR4_1                          20000000  FF       WRLSDRAM                        /wo /w
SCGA WRLSDRAM                        DWR4_2                          24000000  FF       WRLSDRAM                        /wo /w
SCGA WRLSDRAM                        DWR5_1                          20000000  FF       WRLSDRAM                        /wo /w
SCGA WRLSDRAM                        DWR5_2                          24000000  FF       WRLSDRAM                        /wo /w
SCGA WRLSDRAM                        DWR6_1                          20000000  FF       WRLSDRAM                        /wo /w
SCGA WRLSDRAM                        DWR6_2                          24000000  FF       WRLSDRAM                        /wo /w
SCGA WRLSDRAM                        DWR7_1                          20000000  FF       WRLSDRAM                        /wo /w
SCGA WRLSDRAM                        DWR7_2                          24000000  FF       WRLSDRAM                        /wo /w
SCGA WRLSDRAM                        DWR8_1                          20000000  FF       WRLSDRAM                        /wo /w
SCGA WRLSDRAM                        DWR8_2                          24000000  FF       WRLSDRAM                        /wo /w
SCGA WRLSDRAM                        DWR9_1                          20000000  FF       WRLSDRAM                        /wo /w
SCGA WRLSDRAM                        DWR9_2                          24000000  FF       WRLSDRAM                        /wo /w
SCGA WRLSDRAM                        LSDMR3                          00005094  1862A526 WRLSDRAM                        /wo /w /ua:0
SCGA WRLSDRAM                        DWR10_1                         20000000  FF       WRLSDRAM                        /wo /w
SCGA WRLSDRAM                        DWR10_2                         24000000  FF       WRLSDRAM                        /wo /w
SCGA WRLSDRAM                        LSDMR4                          00005094  4062A526 WRLSDRAM                        /wo /w /ua:0
SCGA CUSTOM                          VEC_WR                          00000000  48000000 CUSTOM                          /wo /w
REM *******************************************
REM CF GROUP CONFIGURATION
REM *******************************************
CF GRP                  LA ENABLED
CF GRP                  ECM DISABLED
CF GRP                  LBC ENABLED
CF GRP                  I2C DISABLED
CF GRP                  DUART DISABLED
CF GRP                  DDRMC ENABLED
CF GRP                  TA ENABLED
CF GRP                  PCI DISABLED
CF GRP                  L2SRAM ENABLED
CF GRP                  DMA DISABLED
CF GRP                  TSEC DISABLED
CF GRP                  SE DISABLED
CF GRP                  PIC DISABLED
CF GRP                  UPMA DISABLED
CF GRP                  UPMB DISABLED
CF GRP                  UPMC DISABLED
CF GRP                  CPMIC DISABLED
CF GRP                  IOPORTS DISABLED
CF GRP                  CPMTIMERS DISABLED
CF GRP                  CI DISABLED
CF GRP                  SDMA DISABLED
CF GRP                  FCC DISABLED
CF GRP                  USB DISABLED
CF GRP                  CPMI2C_SPI DISABLED
CF GRP                  COMM DISABLED
CF GRP                  CPMUX DISABLED
CF GRP                  SI DISABLED
CF GRP                  GLOBU DISABLED
CF GRP                  PM DISABLED
CF GRP                  WP DISABLED
CF GRP                  WRLSDRAM DISABLED
CF GRP                  CUSTOM ENABLED
REM *******************************************
REM TF CONFIGURATION AMD29LV64xDx (4096 x 16) 1 device
REM *******************************************
TF CONF 116 00005000 65384 FFC00000
REM *******************************************
REM MMU CONFIGURATION
REM *******************************************
MMUD ALL
REM *******************************************
REM BL CONFIGURATION
REM *******************************************
BL DELETE
REM *******************************************
REM MMUOS CONFIGURATION
REM *******************************************
MMUOS DELETE
