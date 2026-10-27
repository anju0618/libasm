NAME	= libasm.a
TEST	= test

SRCS	= ft_strlen.s \
	  ft_strcpy.s \
	  ft_strcmp.s \
	  ft_write.s \
	  ft_read.s \
	  ft_strdup.s \
	  ft_calloc.s
OBJS	= $(SRCS:.s=.o)

NASM	= nasm
NASMFLAGS	= -f elf64
CC	= cc
CFLAGS	= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^

%.o: %.s
	$(NASM) $(NASMFLAGS) $< -o $@

$(TEST): $(NAME) main.c
	$(CC) $(CFLAGS) main.c $(NAME) -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME) $(TEST)

re: fclean all

.PHONY: all clean fclean re
