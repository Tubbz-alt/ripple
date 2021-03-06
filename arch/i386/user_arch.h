
#define TRAP 0xcc // int3
#define TRAP_SZ 1

#define REGFMT "0x%08"  PRIx32


#define ARCH_INIT_PROC_INFO(i)			\
	do {\
		i.regs    = (struct iovec) { .iov_base = &i.regs_struct,    .iov_len = sizeof(i.regs_struct) }; \
		i.fpregs  = (struct iovec) { .iov_base = &i.fpregs_struct,  .iov_len = sizeof(i.fpregs_struct) }; \
		i.fpxregs = (struct iovec) { .iov_base = &i.fpxregs_struct, .iov_len = sizeof(i.fpxregs_struct) }; \
	} while (0)



//iam: not clear these are needed now.
// i suppose they are if you wanna do "ARCH=x86_64 CC=clang make" etc
struct user_fpregs_struct_x86
{
  long int cwd;
  long int swd;
  long int twd;
  long int fip;
  long int fcs;
  long int foo;
  long int fos;
  long int st_space [20];
};

struct user_fpxregs_struct_x86
{
  unsigned short int cwd;
  unsigned short int swd;
  unsigned short int twd;
  unsigned short int fop;
  long int fip;
  long int fcs;
  long int foo;
  long int fos;
  long int mxcsr;
  long int reserved;
  long int st_space[32];   /* 8*16 bytes for each FP-reg = 128 bytes */
  long int xmm_space[32];  /* 8*16 bytes for each XMM-reg = 128 bytes */
  long int padding[56];
};

struct user_regs_struct_x86
{
  long int ebx;
  long int ecx;
  long int edx;
  long int esi;
  long int edi;
  long int ebp;
  long int eax;
  long int xds;
  long int xes;
  long int xfs;
  long int xgs;
  long int orig_eax;
  long int eip;
  long int xcs;
  long int eflags;
  long int esp;
  long int xss;
};


struct proc_info_t {
  pid_t pid;

  struct user_regs_struct_x86 regs_struct;
  struct user_regs_struct_x86 old_regs_struct;
  struct iovec regs;

  struct user_fpregs_struct_x86 fpregs_struct;
  struct user_fpregs_struct_x86 old_fpregs_struct;
  struct iovec fpregs;

  struct user_fpxregs_struct_x86 fpxregs_struct;
  struct user_fpxregs_struct_x86 old_fpxregs_struct;
  struct iovec fpxregs;

  int sig;
  long exit_code;
};

