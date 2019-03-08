/*
** EPITECH PROJECT, 2019
** Sabri Ouaked
** File description:
** pid.c
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/ptrace.h>
#include <sys/user.h> /* for struct user_regs_struct */


int child_process()
{
    ptrace(PTRACE_TRACEME, 0, NULL, NULL);
    return (0);
}

int parent_process(pid_t pid)
{
    int status = 0; 
    struct user_regs_struct regs;
    int count = 0;
    int called =0;

    wait(&status);
    while(status == 1407){
        ptrace(PTRACE_GETREGS, pid, NULL, &regs);
        if (!called) {
            count++;
            called=1;
            printf("Syscall\n");
        } else {
            called = 0; 
        }
        ptrace(PTRACE_SYSCALL, pid, NULL, NULL); 
        wait(&status); 
    }
    printf("there is %d syscalls\n", count);
    return (status);
}

int trace_pid(pid_t pid)
{
    if (pid < 0) {
        perror("fork failed");
        exit(84);
    } else if (pid == 0) {
        child_process();
    } else {
        parent_process(pid);
    }
    return 0; 
}