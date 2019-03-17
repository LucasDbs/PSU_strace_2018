/*
** EPITECH PROJECT, 2019
** Sabri Ouaked
** File description:
** parsing.c
*/

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <string.h>
#include "strace.h"

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

int strace(int ac, char **av)
{
        if (strcmp(av[1], "--help") == 0)
                return (helper(ac));
        else if (strcmp(av[1], "-p") == 0)
                return (pid_tracer(ac, av));
        else
                return (launch(av));
}