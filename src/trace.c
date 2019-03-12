/*
** EPITECH PROJECT, 2019
** Lucas Duboisse
** File description:
** trace.c
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

long long register_find(int i, struct user_regs_struct regs)
{
        switch (i)
        {
                case 0:
                        return regs.rdi;
                case 1:
                        return regs.rsi;
                case 2:
                        return regs.rdx;
                case 3:
                        return regs.r10;
                case 4: 
                        return regs.r8;
                case 5:
                        return regs.r9;
                default:
                        return (0);
        }
}

int print_syscall(pid_t child)
{
        struct user_regs_struct regs;
        syscalls_t syscall;
        size_t i = 0;

        ptrace(PTRACE_GETREGS, child, NULL, &regs);
        syscall = syscalls_list[regs.rax];
        printf("%s(", syscall.name);
        for (i = 0; i != syscall.nb_args; i++) {
                if (i == syscall.nb_args - 1)
                        printf("0x%llx", register_find(i, regs));
                else
                        printf("0x%llx, ", register_find(i, regs));
        }
        printf(")\n");
        return (0);
}

int waitchild(pid_t pid)
{
        int status = 0;
        
        waitpid(pid, &status, 0);
        if (WIFSTOPPED(status))
                return (0);
        else if (WIFEXITED(status))
                return (1);
        else {
                printf("%d raised an unexpected status %d", pid, status);
                return (1);
        }
}

int trace(pid_t child)
{
        long ret = 0;
        unsigned char primary;
        unsigned char secondary;

        do {
                ret = ptrace(PTRACE_PEEKUSER, child, 8 * RIP, NULL);
                ret = ptrace(PTRACE_PEEKTEXT, child, ret, NULL);
                primary = (unsigned)0xFF & ret;
                secondary = ((unsigned)0xFF00 & ret) >> 8;
                if ((primary == 0xCD && secondary == 0x80) || (primary == 0x0F && secondary == 0x05)) {
                        print_syscall(child);
                }
                ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
        } while (waitchild(child) < 1);
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
        } else {
                // wait for the child to stop
                waitchild(child);
                trace(child);
        }
        return 0;
}

