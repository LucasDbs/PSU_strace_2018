/*
** EPITECH PROJECT, 2019
** Sabri Ouaked
** File description:
** parsing.c
*/

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
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

int pars_s(void)
{
        return (0);
}

int strace(int ac, char **av)
{
        int opt = 0;
        static struct option options[] = {
                {"help", no_argument, 0, 'h'}, {0, 0, 0, 0}
        };

        while ((opt = getopt_long(ac, av, "p:s:", options, NULL)) != -1) {
                if (opt == 'h')
                        return (helper(ac));
                else if (opt == 'p')
                        return (pid_tracer(ac, av));
                else if (opt == 's')
                        return (pars_s());
        }
        return (launch(av));
}