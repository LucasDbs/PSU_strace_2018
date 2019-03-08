##
## EPITECH PROJECT, 2018
## Makefile
## File description:
## Sabri Ouaked
##

NAME	=	strace

SRC	=	src/main.c	\
		src/parsing.c

OBJ	=	$(SRC:.c=.o)

CFLAGS	=	-g -W -Wall -Wextra -Iinclude/

all:		$(NAME)

$(NAME):
		gcc -o $(NAME) $(SRC) $(CFLAGS)

clean:
		rm -f $(OBJ)

fclean:		clean
		rm -f $(NAME)

re:		fclean all