/*
** EPITECH PROJECT, 2019
** Lucas Duboisse
** File description:
** find_register.c
*/

#include "strace.h"

long long register_find(int i, struct user_regs_struct regs)
{
        switch (i) {
                case 0:
                        return regs.rdi;
                case 1:
                        return regs.rsi;
                case 2:
                        return regs.rdx;
                case 3:
                        return regs.r10;
                case 4: 
                        return regs.r8;
                case 5:
                        return regs.r9;
                default:
                        return (0);
        }
}
