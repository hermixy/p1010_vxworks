#include <vxWorks.h>
#include <stdarg.h>
#include <string.h>

#define COM1_ADDR ((volatile unsigned char*)(0xffe04500))

static int read_8(volatile unsigned char* addr)
{
	int ret = 0;
	_WRS_ASM("sync");
	ret = (int)*addr;
	_WRS_ASM("isync");
	return ret;
}

static void write_8(volatile unsigned char* addr, char c)
{
	*addr = c;
	_WRS_ASM("eieio");
}

void _putc(char c)
{
	while(read_8(COM1_ADDR+5)&32 == 0);
	write_8(COM1_ADDR,c);
}	

void putc(char c)
{
	if(c == '\n')
		_putc('\r');
	_putc(c);
}

void puts(char* str)
{
	while(*str)
	{
		putc(*str++);
	}
}

void printTest()
{
	putc('a');
}


int early_p(const char *fmt, ...)
{
        va_list args;
        unsigned int i;
        char printbuffer[100];

        va_start(args, fmt);

        /* For this to work, printbuffer must be larger than
         * anything we ever want to print.
         */
        i = vsprintf(printbuffer, fmt, args);
        va_end(args);

        /* Print the string */
        puts(printbuffer);
        return i;
}

typedef  unsigned int u32;
typedef unsigned int phys_addr_t;

/*#define MAS0 0x270
#define MAS1 0x271
#define MAS2 0x272
#define MAS3 0x273
#define MAS5 0x275
#define MAS6 0x276
#define MAS7 0x3B0
#define MAS8 0x155*/

#define MAS0_TLBSEL_MSK	0x30000000
#define MAS0_TLBSEL(x)	((x << 28) & MAS0_TLBSEL_MSK)
#define MAS0_ESEL_MSK	0x0FFF0000
#define MAS0_ESEL(x)	((x << 16) & MAS0_ESEL_MSK)
#define MAS0_NV(x)	((x) & 0x00000FFF)

#define MAS1_VALID	0x80000000
#define MAS1_IPROT	0x40000000
#define MAS1_TID(x)	((x << 16) & 0x3FFF0000)
#define MAS1_TS		0x00001000
#define MAS1_TSIZE(x)	((x << 8) & 0x00000F00)
#define TSIZE_TO_BYTES(x) ((phys_addr_t)(1UL << ((tsize * 2) + 10)))

#define MAS2_EPN	0xFFFFF000
#define MAS2_X0		0x00000040
#define MAS2_X1		0x00000020
#define MAS2_W		0x00000010
#define MAS2_I		0x00000008
#define MAS2_M		0x00000004
#define MAS2_G		0x00000002
#define MAS2_E		0x00000001

#define MAS3_RPN	0xFFFFF000
#define MAS3_U0		0x00000200
#define MAS3_U1		0x00000100
#define MAS3_U2		0x00000080
#define MAS3_U3		0x00000040
#define MAS3_UX		0x00000020
#define MAS3_SX		0x00000010
#define MAS3_UW		0x00000008
#define MAS3_SW		0x00000004
#define MAS3_UR		0x00000002
#define MAS3_SR		0x00000001

#define MAS4_TLBSELD(x) MAS0_TLBSEL(x)
#define MAS4_TIDDSEL	0x000F0000
#define MAS4_TSIZED(x)	MAS1_TSIZE(x)
#define MAS4_X0D	0x00000040
#define MAS4_X1D	0x00000020
#define MAS4_WD		0x00000010
#define MAS4_ID		0x00000008
#define MAS4_MD		0x00000004
#define MAS4_GD		0x00000002
#define MAS4_ED		0x00000001

#define MAS6_SPID0	0x3FFF0000
#define MAS6_SPID1	0x00007FFE
#define MAS6_SAS	0x00000001
#define MAS6_SPID	MAS6_SPID0

#define MAS7_RPN	0xFFFFFFFF

#define FSL_BOOKE_MAS0(tlbsel,esel,nv) \
		(MAS0_TLBSEL(tlbsel) | MAS0_ESEL(esel) | MAS0_NV(nv))
#define FSL_BOOKE_MAS1(v,iprot,tid,ts,tsize) \
		((((v) << 31) & MAS1_VALID)             |\
		(((iprot) << 30) & MAS1_IPROT)          |\
		(MAS1_TID(tid))				|\
		(((ts) << 12) & MAS1_TS)                |\
		(MAS1_TSIZE(tsize)))
#define FSL_BOOKE_MAS2(epn, wimge) \
		(((epn) & MAS3_RPN) | (wimge))
#define FSL_BOOKE_MAS3(rpn, user, perms) \
		(((rpn) & MAS3_RPN) | (user) | (perms))
#define FSL_BOOKE_MAS7(rpn) \
		(((u64)(rpn)) >> 32)

#define BOOKE_PAGESZ_1K         0
#define BOOKE_PAGESZ_4K         1
#define BOOKE_PAGESZ_16K        2
#define BOOKE_PAGESZ_64K        3
#define BOOKE_PAGESZ_256K       4
#define BOOKE_PAGESZ_1M         5
#define BOOKE_PAGESZ_4M         6
#define BOOKE_PAGESZ_16M        7
#define BOOKE_PAGESZ_64M        8
#define BOOKE_PAGESZ_256M       9
#define BOOKE_PAGESZ_1G		10
#define BOOKE_PAGESZ_4G		11
#define BOOKE_PAGESZ_16GB	12
#define BOOKE_PAGESZ_64GB	13
#define BOOKE_PAGESZ_256GB	14
#define BOOKE_PAGESZ_1TB	15
#define stringify(s)	tostring(s)
#define tostring(s)	#s

#define ARRAY_SIZE(x) (sizeof(x)/sizeof(x[0]))

/*
 * print sizes as "xxx KiB", "xxx.y KiB", "xxx MiB", "xxx.y MiB",
 * xxx GiB, xxx.y GiB, etc as needed; allow for optional trailing string
 * (like "\n")
 */
void print_size(unsigned long long size, const char *s)
{
	unsigned long m = 0, n;
	unsigned long long f;
	static const char names[] = {'E', 'P', 'T', 'G', 'M', 'K'};
	unsigned long d = 10 * ARRAY_SIZE(names);
	char c = 0;
	unsigned int i;

	for (i = 0; i < ARRAY_SIZE(names); i++, d -= 10) {
		if (size >> d) {
			c = names[i];
			break;
		}
	}

	if (!c) {
		printf("%llu Bytes%s", size, s);
		return;
	}

	n = size >> d;
	f = size & ((1ULL << d) - 1);

	/* If there's a remainder, deal with it */
	if (f) {
		m = (10ULL * f + (1ULL << (d - 1))) >> d;

		if (m >= 10) {
			m -= 10;
			n += 1;
		}
	}

	printf ("%lu", n);
	if (m) {
		printf (".%ld", m);
	}
	printf (" %ciB%s", c, s);
}

void read_tlbcam_entry(int idx, u32 *valid, u32 *tsize, unsigned long *epn,
		       phys_addr_t *rpn)
{
	u32 _mas1;

	mtspr_mas0(FSL_BOOKE_MAS0(1, idx, 0));
	_WRS_ASM("tlbre;isync");
	_mas1 = mfspr_mas1();

	*valid = (_mas1 & MAS1_VALID);
	*tsize = (_mas1 >> 8) & 0xf;
	*epn = mfspr_mas2() & MAS2_EPN;
	*rpn = mfspr_mas3() & MAS3_RPN;
}

void print_tlbcam(void)
{
	int i;
	unsigned int num_cam = mfspr_tlb1cfg() & 0xfff;

	/* walk all the entries */
	printf("TLBCAM entries\n");
	for (i = 0; i < num_cam; i++) {
		unsigned long epn;
		u32 tsize, valid;
		phys_addr_t rpn;

		read_tlbcam_entry(i, &valid, &tsize, &epn, &rpn);
		printf("entry %02d: V: %d EPN 0x%08x RPN 0x%08llx size:",
			i, (valid == 0) ? 0 : 1, (unsigned int)epn,
			(unsigned long long)rpn);
		print_size(TSIZE_TO_BYTES(tsize), "\n");
	}
}

void tlbcam_invalid(int index)
{
	unsigned int mas0, mas1, mas2, mas3;
	mtspr_mas0(FSL_BOOKE_MAS0(1, index, 0));
	_WRS_ASM("tlbre;isync");

	mas0 = mfspr_mas0();
	mas1 = mfspr_mas1();
	mas2 = mfspr_mas2();
	mas3 = mfspr_mas3();

	mas1 &= ~(MAS1_VALID|MAS1_IPROT);

	write_tlb(mas0, mas1, mas2, mas3);
}

void tlbcam_read(int index)
{
	unsigned int mas0, mas1, mas2, mas3;
	mtspr_mas0(FSL_BOOKE_MAS0(1, index, 0));
	_WRS_ASM("tlbre;isync");

	mas0 = mfspr_mas0();
	mas1 = mfspr_mas1();
	mas2 = mfspr_mas2();
	mas3 = mfspr_mas3();

	printf("%x %x %x %x\n", mas0, mas1, mas2, mas3);
}

void tlbcam_clear_but(int nodel)
{
	int i;
	unsigned int num_cam = mfspr_tlb1cfg()&0xfff;
	for(i = 0; i < num_cam; i++)
	{
		if(i != nodel)
		{
			tlbcam_invalid(i);
		}
	}
}

int tlbcam_find(int pid, void* addr)
{
	unsigned int oldpid;
	int index;

	oldpid = mmuPpcPidGet();

	if(oldpid != pid)
	{
		mmuPpcPidSet(pid);
	}
	index = mmuPpcTlbSearch(addr);
	if(oldpid != pid)
	{
		mmuPpcPidSet(oldpid);
	}

	return index;
}

