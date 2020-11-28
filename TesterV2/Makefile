
NAME=test-libasm

SRCS=main.c test_strlen.c test_strcmp.c test_strcpy.c test_strncpy.c test_strdup.c test_write.c test_read.c
OBJDIR=bin
OBJS=$(addprefix $(OBJDIR)/,$(SRCS:.c=.o))
CFLAGS=-g3 -fsanitize=address

all: $(NAME)
	@echo Done.

$(NAME) : $(OBJDIR) $(OBJS)
	gcc -o $(NAME) -L../ $(OBJS) -lasm $(CFLAGS)

$(OBJDIR):
	@mkdir -p $@

$(OBJDIR)/%.o : %.c
	gcc -c -o $@ -I../inc/ -I./ $< $(CFLAGS)

clean:
	rm -rf $(OBJDIR)

fclean: clean
	rm -rf $(NAME)

re: fclean all
