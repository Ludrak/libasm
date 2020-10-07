
NAME =		libasm.a

SRC_DIR =	src
SRCS =		io/ft_write.s				\
			io/ft_read.s				\
			str/ft_strlen.s				\
			str/ft_strcmp.s				\
			str/ft_strcpy.s				\
			str/ft_strncpy.s			\
			str/ft_strdup.s				\
			list/ft_list_push_front.s	\
			list/ft_list_size.s

OBJ_DIR =	bin
OBJS =		$(addprefix $(OBJ_DIR)/,$(SRCS:.s=.o))

HEADERS =	inc/libasm.h

ASM =		nasm

ifeq ($(shell uname), Linux)
FORMAT =	elf64
endif
ifeq ($(shell uname), Darwin)
FORMAT =	macho64
endif

all: $(NAME)
	@echo "Done."

$(NAME) : $(OBJ_DIR) $(OBJS)
	@ar rcs $@ $(OBJS)

$(OBJ_DIR) : 
	@echo "Missing bin directory, creating it."
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.s $(HEADERS)
	@mkdir -p $(shell dirname $@)
	@$(ASM) -f $(FORMAT) -g $< -o $@
	@echo "Compiled : $(shell basename $<)"

clean :
	@echo "Cleaning binaries"
	@rm -rf $(OBJ_DIR)

fclean : clean clean_test
	@echo "Cleaning library"
	@rm -rf $(NAME)

re : fclean all

test:
	@make -C Tester
	@./Tester/test-libasm

clean_test:
	@rm -rf Tester/bin
	@rm -rf Tester/test-libasm