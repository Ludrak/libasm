
NAME=test-libasm

SRCS=main.c test_strlen.c
OBJDIR=bin
OBJS=$(addprefix $(OBJDIR)/,$(SRCS:.c=.o))


all: $(NAME)
	@echo Done.

$(NAME) : $(OBJDIR) $(OBJS)
	gcc -o $(NAME) -L../ $(OBJS) -lasm

$(OBJDIR):
	@mkdir -p $@

$(OBJDIR)/%.o : %.c
	@gcc -c -o $@ -L../ -I../inc/ -I./ $< -lasm

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all