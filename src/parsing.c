/*
** EPITECH PROJECT, 2019
** Lucas Duboisse
** File description:
** parsing.c
*/

#include <unistd.h>
#include <stdio.h>
#include <getopt.h>
#include <string.h>
#include <stdlib.h>
#include "trace.h"

int helper(int ac)
{
    if (ac != 2)
        return (84);
    printf("USAGE: ./strace [-s] [-p <pid>|<command>]\n");
    return (0);
}

int pid_tracer(int ac, char **av)
{
    pid_t pid;

    if (ac != 3)
        return (84);
    pid = atoi(av[2]);
    return (launch_pid(pid));
}

int pars_s(int ac)
{
    if (ac != 3)
        return (84);
    return (0);
}

int without_flag(int ac, char **av)
{
    if (ac != 2)
        return (84);
    return (launch(av));
}

int strace(int ac, char **av)
{
    int opt = 0;
    static struct option options[] = {{"help", no_argument, 0, 'h'}, {0, 0, 0, 0}};

    while ((opt = getopt_long(ac, av, "p:s:", options, NULL)) != -1) {
        if (opt == 'h') {
            return (helper(ac));
        } else if (opt == 'p') {
            return (pid_tracer(ac, av));
        } else if (opt == 's') {
            return (pars_s(ac));
        }
    }
    return (without_flag(ac, av));
}