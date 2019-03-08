NAME=test
ASM=nasm
LD=gcc
SRC=main.S
OBJ=$(SRC:.S=.o)
LDFLAGS=-fno -builtin
CFLAGS=-f elf

.S.o:
	$(ASM) $(CFLAGS) $< -c $@

$(NAME): $(OBJ)
	$(LD) $(OBJ) -o $(NAME) $(LDFLAGS)

all: $(NAME)

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)