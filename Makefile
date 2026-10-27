NAME	= libasm.a

SRCS	= ft_strlen.s \
	  ft_strcpy.s \
	  ft_strcmp.s \
	  ft_write.s \
	  ft_read.s \
	  ft_strdup.s \
	  ft_calloc.s
OBJS	= $(SRCS:.s=.o)

TESTS	= strlen strcpy strcmp write read strdup calloc
TESTDIR	= tests
TESTBIN	= $(TESTDIR)/bin

NASM	= nasm
NASMFLAGS	= -f elf64
CC	= cc
CFLAGS	= -Wall -Wextra -Werror

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $@ $^

%.o: %.s
	$(NASM) $(NASMFLAGS) $< -o $@

tester: $(NAME)
	@mkdir -p $(TESTBIN)
	@fail=0; \
	for t in $(TESTS); do \
		echo "=== ft_$$t ==="; \
		if ! $(CC) $(CFLAGS) $(TESTDIR)/test_$$t.c $(NAME) -o $(TESTBIN)/test_$$t 2>/dev/null; then \
			echo "  FAIL: build/link error (not implemented?)"; fail=1; continue; \
		fi; \
		./$(TESTBIN)/test_$$t || { echo "  -> ft_$$t FAILED"; fail=1; }; \
	done; \
	echo; \
	if [ $$fail -eq 0 ]; then echo "ALL PASSED"; else echo "SOME FAILED"; fi; \
	exit $$fail

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)
	rm -rf $(TESTBIN)

re: fclean all

.PHONY: all clean fclean re tester
