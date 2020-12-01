
NAME=test-libasm

SRCS=main.c utils.c strlen_unit.c strcpy_unit.c strncpy_unit.c strdup_unit.c strcmp_unit.c write_unit.c read_unit.c
OBJDIR=bin
OBJS=$(addprefix $(OBJDIR)/,$(SRCS:.c=.o))
CFLAGS=-Wall -Wextra -Werror

all: $(NAME)
	@echo Done.

$(NAME) : $(OBJDIR) $(OBJS)
	gcc -o $(NAME) -L../ $(OBJS) -lasm $(CFLAGS)

$(OBJDIR):
	@mkdir -p $@

$(OBJDIR)/%.o : %.c
	gcc -c -o $@ -I../inc/ -I./inc/ $< $(CFLAGS)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all

test:
	make -C .. re
	make re
	clear
	./$(NAME)

.PHONY:all re fclean clean test
