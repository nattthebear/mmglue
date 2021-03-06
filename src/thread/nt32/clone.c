#include <syscall.h>

struct pt_regs {
	unsigned long	ebp;
	unsigned long	ebx;
	unsigned long	eax;
	unsigned long	ecx;
	unsigned long	edx;
	unsigned long	esi;
	unsigned long	edi;
	unsigned long	orig_eax;
	unsigned long	eip;
	unsigned long	cs;
	unsigned long	eflags;
	unsigned long	esp;
	unsigned long	ss;
};

typedef long __sys_clone(
	unsigned long	flags,
	void *		child_stack,
	void *		ptid,
	void *		ctid,
	struct pt_regs *regs);

typedef int __entry_point(void *);

extern unsigned long ** __syscall_vtbl;

int __clone(
	__entry_point *	fn,
	void *		child_stack,
	int		flags,
	void *		arg,
	int *		ptid,
	void *		pthread_self_addr,
	int *		ctid)
{
	struct pt_regs	regs;
	__sys_clone *	pfn_clone;

	regs.eip = (unsigned long)fn;
	regs.ecx = (unsigned long)arg;
	regs.edx = (unsigned long)pthread_self_addr;

	pfn_clone = (__sys_clone *)(__syscall_vtbl[SYS_clone]);

	return (int)pfn_clone(
		flags,
		child_stack,
		ptid,
		ctid,
		&regs);
}
