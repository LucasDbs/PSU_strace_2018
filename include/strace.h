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
        int nb_args;
        char **args;
        char *return_value;
} syscalls_t;

#endif // STRACE_H
