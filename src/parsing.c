/*
** EPITECH PROJECT, 2019
** Lucas Duboisse
** File description:
** parsing.c
*/

#include <unistd.h>
#include <stdio.h>
#include <getopt.h>

int pars_h(int ac)
{
        if (ac != 2)
                return (84);
        printf("USAGE: ./strace [-s] [-p <pid>|<command>]\n");
        return (0);
}

int pars_p(int ac)
{
        if (ac != 3)
                return (84);
        return (0);
}

int pars_s(int ac)
{
        if (ac != 3)
                return (84);
        return (0);
}

int pars_command(int ac, char **av)
{
        int opt = 0;
        static struct option options[] = {
                {"help", no_argument, 0, 'h'},
                {0, 0, 0, 0}
        };

        while ((opt = getopt_long(ac, av, "p:s:", options, NULL)) != -1) {
                if (opt == 'h')
                        return (pars_h(ac));
                else if (opt == 'p')
                        return (pars_p(ac));
                else if (opt == 's')
                        return (pars_s(ac));
        }
        return (84);
}
