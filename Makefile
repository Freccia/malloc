
ifeq ($(HOSTTYPE),)
		HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME				= libft_malloc_$(HOSTTYPE).so
NAME_SLINK	= libft_malloc.so

NAME_TEST		= malloc_test
SRC_TEST		= main.c
SRC_T				= $(addprefix $(SRC_PATH),$(SRC_TEST))

SRC_NAME		= malloc.c
OBJ_NAME		= $(SRC_NAME:.c=.o)
LIB_NAME		= -lft -lft_malloc

SRC_PATH		= ./src/
OBJ_PATH		= ./obj/
LIB_PATH		= ./libft/ .
INC_PATH		= ./include ./libft/include ./libft/libft

SRC					= $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ					= $(SRC:.c=.o)
LIB 				= $(addprefix -L, $(LIB_PATH))
INC 				= $(addprefix -I ,$(INC_PATH))

CC					= gcc
CFLAGS			= -Wall -Wextra -Werror

RED					= \033[31m
GREEN				= \033[32m
ENDC				= \033[0m

.PHONY: all lib clean fclean re libfclean libclean

all: $(NAME)

$(NAME): lib $(OBJ)
	ar -rcs $(NAME) $(OBJ)
	ranlib $(NAME)
	ln -sf libft_malloc_$(HOSTTYPE).so $(NAME_SLINK)
	@printf "$(GREEN) Make $(NAME) $(ENDC)\n"
	gcc -I include/ -I libft/libft/  -o test_malloc src/main.c -L libft -L . -lft -lft_malloc
	@printf "$(GREEN) Compiled test_malloc $(ENDC)\n"

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(INC)

test:
	@printf "$(GREEN) Make $(NAME_TEST) $(ENDC)\n"
	$(CC) $(CFLAGS) $(INC) $(SRC_T) -o $(NAME_TEST) $(LIB) $(LIB_NAME)

clean:
	@printf "$(RED) Removing $(NAME) objects $(ENDC)\n"
	@rm -rfv $(OBJ) $(OBJ_PATH) $(SRC_PATH)/*.o

fclean: clean libfclean
	@printf "$(RED) Removing $(NAME) $(ENDC)\n"
	@printf "$(RED) Removing $(NAME_SLINK) $(ENDC)\n"
	@printf "$(RED) Removing $(NAME_TEST) $(ENDC)\n"
	@rm -fv $(NAME) $(NAME_SLINK) $(NAME_TEST)

lib:
	@make -C ./libft

libclean:
	@make -C ./libft clean

libfclean:
	@make -C ./libft fclean

re: fclean
	@make all
