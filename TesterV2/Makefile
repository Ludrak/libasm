
NAME=test-libasm

SRCS=main.c test_strlen.c test_strcmp.c test_strcpy.c test_strncpy.c test_strdup.c test_write.c test_read.c
OBJDIR=bin
OBJS=$(addprefix $(OBJDIR)/,$(SRCS:.c=.o))


all: $(NAME)
	@echo Done.

$(NAME) : $(OBJDIR) $(OBJS)
	gcc -o $(NAME) -L../ $(OBJS) -lasm

$(OBJDIR):
	@mkdir -p $@

$(OBJDIR)/%.o : %.c
	gcc -c -o $@ -I../inc/ -I./ $<

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all
