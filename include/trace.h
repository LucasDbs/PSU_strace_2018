/*
** EPITECH PROJECT, 2019
** Lucas Duboisse
** File description:
** parsing.c
*/

#if !defined(TRACE_H)
#define TRACE_H

#include <sys/types.h>

int pars_command(int ac, char **av);
int launch(char **av);
int launch_pid(pid_t pid);
int strace(int ac, char **av);


#endif // TRACE_H
