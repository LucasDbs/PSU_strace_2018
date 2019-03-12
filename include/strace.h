/*
** EPITECH PROJECT, 2019
** Lucas Duboisse
** File description:
** parsing.c
*/

#if !defined(STRACE_H)
#define STRACE_H

typedef struct syscalls
{
        char *name;
        size_t nb_args;
        char *args[6];
        char *return_value;
} syscalls_t;

extern const syscalls_t syscalls_list[];

#endif // STRACE_H
