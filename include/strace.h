/*
** EPITECH PROJECT, 2019
** Lucas Duboisse
** File description:
** parsing.c
*/

#if !defined(STRACE_H)
#define STRACE_H

#include <sys/types.h>
#include <sys/user.h>

typedef struct syscalls
{
        char *name;
        size_t nb_args;
        char *args[6];
        char *return_value;
} syscalls_t;

extern const syscalls_t syscalls_list[];

int launch(char **av);
int launch_pid(pid_t pid);
int strace(int ac, char **av);
long long register_find(int i, struct user_regs_struct regs);

#endif
