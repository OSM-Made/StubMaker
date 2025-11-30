#pragma once

#ifdef __cplusplus
extern "C" {
#endif

#include <cstdint>

    struct reg
    {
        uint64_t r_r15;
        uint64_t r_r14;
        uint64_t r_r13;
        uint64_t r_r12;
        uint64_t r_r11;
        uint64_t r_r10;
        uint64_t r_r9;
        uint64_t r_r8;
        uint64_t r_rdi;
        uint64_t r_rsi;
        uint64_t r_rbp;
        uint64_t r_rbx;
        uint64_t r_rdx;
        uint64_t r_rcx;
        uint64_t r_rax;
        uint32_t r_trapno;
        uint16_t r_fs;
        uint16_t r_gs;
        uint32_t r_err;
        uint16_t r_es;
        uint16_t r_ds;
        uint64_t r_rip;
        uint64_t r_cs;
        uint64_t r_rflags;
        uint64_t r_rsp;
        uint64_t r_ss;
    };

    // Updated with BSD header.
#define PT_TRACE_ME     0       /* child declares it's being traced */
#define PT_READ_I       1       /* read word in child's I space */
#define PT_READ_D       2       /* read word in child's D space */
/* was  PT_READ_U       3        * read word in child's user structure */
#define PT_WRITE_I      4       /* write word in child's I space */
#define PT_WRITE_D      5       /* write word in child's D space */
/* was  PT_WRITE_U      6        * write word in child's user structure */
#define PT_CONTINUE     7       /* continue the child */
#define PT_KILL         8       /* kill the child process */
#define PT_STEP         9       /* single step the child */

#define PT_ATTACH       10      /* trace some running process */
#define PT_DETACH       11      /* stop tracing a process */
#define PT_IO           12      /* do I/O to/from stopped process. */
#define PT_LWPINFO      13      /* Info about the LWP that stopped. */
#define PT_GETNUMLWPS   14      /* get total number of threads */
#define PT_GETLWPLIST   15      /* get thread list */
#define PT_CLEARSTEP    16      /* turn off single step */
#define PT_SETSTEP      17      /* turn on single step */
#define PT_SUSPEND      18      /* suspend a thread */
#define PT_RESUME       19      /* resume a thread */

#define PT_TO_SCE       20
#define PT_TO_SCX       21
#define PT_SYSCALL      22

#define PT_FOLLOW_FORK  23

#define PT_GETREGS      33      /* get general-purpose registers */
#define PT_SETREGS      34      /* set general-purpose registers */
#define PT_GETFPREGS    35      /* get floating-point registers */
#define PT_SETFPREGS    36      /* set floating-point registers */
#define PT_GETDBREGS    37      /* get debugging registers */
#define PT_SETDBREGS    38      /* set debugging registers */

#define PT_VM_TIMESTAMP 40      /* Get VM version (timestamp) */
#define PT_VM_ENTRY     41      /* Get VM map (entry) */

#define PT_FIRSTMACH    64      /* for machine-specific requests */

#ifdef __cplusplus
}
#endif