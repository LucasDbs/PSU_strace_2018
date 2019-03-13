/*
** EPITECH PROJECT, 2019
** Lucas Duboisse
** File description:
** trace.c
*/

#include <sys/stat.h>
#include <fcntl.h>
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
        switch (i) {
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
        // long long *test = NULL;

        ptrace(PTRACE_GETREGS, child, NULL, &regs);
        syscall = syscalls_list[regs.rax];
        printf("%s(", syscall.name);
        for (i = 0; i != syscall.nb_args; i++) {
                if (i == syscall.nb_args - 1) {
                        printf("0x%llx", register_find(i, regs));
                } else {
                        printf("0x%llx, ", register_find(i, regs));
                }
        }
        i--;
        printf(") = 0x%llx\n", regs.rbx);
        // test = &regs;
        // while (test) {
        //         printf("%lld\n", *test);
        //         test++;
        // }
        return (0);
}

int waitchild(pid_t pid)
{
        int status = 0;
        
        waitpid(pid, &status, 0);
        if (WIFSTOPPED(status)) {
                return (0);
        } else if (WIFEXITED(status)) {
                return (1);
        } else {
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


int launch_pid(pid_t pid)
{
        printf("inside");
        ptrace(PTRACE_ATTACH, pid, NULL, NULL);
        waitchild(pid);
        trace(pid);
        ptrace(PTRACE_DETACH, pid, NULL, NULL);
        return 0;
}

int launch(char **av)
{
        pid_t child = fork();
        int fd = open("/dev/null", O_WRONLY);

        if (fd == -1) {
                perror("fd failed");
        }
        if (child == 0) {
                dup2(fd, STDOUT_FILENO);
                ptrace(PTRACE_TRACEME, 0, NULL, NULL);
                execve(argv[1], argv + 1, NULL);
        } else {
                waitchild(child);
                trace(child);
        }
        close(fd);
        return 0;
}