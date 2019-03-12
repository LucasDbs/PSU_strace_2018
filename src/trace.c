/*
** EPITECH PROJECT, 2019
** Sabri Ouaked
** File description:
** main.c
*/

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
#include "parsing.h"
#include "strace.h"

syscalls_t find_syscall(size_t syscalls_id)
{
        int i = 0;      
        syscalls_t *find = NULL;


        
}

int waitchild(pid_t pid)
{
        int status = 0;
        
        waitpid(pid, &status, 0);
        if(WIFSTOPPED(status)) {
                return 0;
        } else if (WIFEXITED(status)) {
                return 1;
        } else {
                printf("%d raised an unexpected status %d", pid, status);
                return 1;
        }
}

int trace(pid_t child)
{
        long ret = 0;
        long jmps = 0;
        unsigned char primary;
        unsigned char secondary;
        struct user_regs_struct regs;

        do {
                ret = ptrace(PTRACE_PEEKUSER, child, 8 * RIP, NULL);
                ret = ptrace(PTRACE_PEEKTEXT, child, ret, NULL);
                primary = (unsigned)0xFF & ret;
                secondary = ((unsigned)0xFF00 & ret) >> 8;
                if ((primary == 0xCD && secondary == 0x80) || (primary == 0x0F && secondary == 0x05)) {
                        ptrace(PTRACE_GETREGS, child, NULL, &regs);
                        if (regs.rax == SYS_write) {
                                printf("write(0x%llx, 0x%llx, 0x%llx) = 0x%llx\n", regs.rdi, regs.rsi, regs.rdx, regs.rdx);
                                printf("test %llx\n", regs.r11);
                        }
                                // printf("ret = %lx  prim=%x sec=%x rax: %lld orig_rax=%llu\n", ret, primary, secondary, regs.rax, regs.orig_rax);
                        jmps++;
                }
                ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
        } while(waitchild(child) < 1);
        // printf("SYS_write = %d\n", SYS_write);
        printf("=> There are %lu jumps\n", jmps);
        return (0);
}

int launch(int argc, char ** argv)
{
    pid_t child = fork();

    if(child == 0) {
        ptrace(PTRACE_TRACEME, 0, NULL, NULL);
        // kill(getpid(), SIGUSR1);
        // write(1, "test", 4);
        // kill(getpid(), SIGUSR1);

        execve(argv[1], argv + 1, NULL);
        // execl("/bin/ls", "ls", NULL);
    }
    else {
        // wait for the child to stop
        waitchild(child);
        trace(child);
    }
    return 0;
}

