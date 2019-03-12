/*
** EPITECH PROJECT, 2019
** Sabri Ouaked
** File description:
** pid.c
*/

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

int child_process()
{
    ptrace(PTRACE_TRACEME, 0, NULL, NULL);
    // execl("/bin/env", "", NULL);
    execl("/bin/ls", "ls", NULL);
    // write(1, "Test\n", 6);
    return (0);
}

int is_syscall(int *insyscall, pid_t child)
{
    struct user_regs_struct regs;
    long rax = 0;

    if (*insyscall == 0) { /* Syscall entry */
        *insyscall = 1;
        ptrace(PTRACE_GETREGS, child, NULL, &regs);
        printf("Write called with %lld, %lld, %lld\n", regs.rdi, regs.rsi, regs.rdx);
    }
    else { /* Syscall exit */
        rax = ptrace(PTRACE_PEEKUSER, child, 4 * RAX, NULL);
        printf("Write returned with %ld\n", rax);
        insyscall = 0;
    }
    return (0);
}

int parent_process(pid_t child)
{
    int status = 0;
    int insyscall = 0;
    long orig_rax = 0;

    // int retval;
    // struct user_regs_struct regs;
    // long rip;

    do {
        wait(&status);
        orig_rax = ptrace(PTRACE_PEEKUSER, child, 8 * ORIG_RAX, NULL);
        printf("orig_rax = %ld\n", orig_rax);
        printf("status = %d\n", status);
        // if (orig_rax == -1) {
        //     perror("");
        //     return 0;
        // }
        if (orig_rax == SYS_write)
            is_syscall(&insyscall, child);
        ptrace(PTRACE_SINGLESTEP, child, NULL, NULL);
        // printf("Test");
    } while (status == 1407);
    return (0);
}

int test_trace()
{
    pid_t child = fork();

    if (child == -1)
        return (84);
    else if (child == 0)
        child_process();
    else
        parent_process(child);
    return 0;
}
