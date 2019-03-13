#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <sys/user.h>
#include <sys/reg.h>
#include <sys/syscall.h>
#include <sys/ptrace.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>


int main(int argc, char *argv[])
{   
        pid_t traced_process  = atoi(argv[1]);;
        struct user_regs_struct regs;

        ptrace(PTRACE_ATTACH, traced_process, NULL, NULL);
        wait(NULL);
        ptrace(PTRACE_GETREGS, traced_process, NULL, &regs);
        ptrace(PTRACE_PEEKTEXT, traced_process, regs.rip, NULL);
        printf("rip: %lx Instruction executed\n", regs.rip);
        ptrace(PTRACE_DETACH, traced_process, NULL, NULL);
        return 0;
}