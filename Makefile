
ifeq ($(HOSTTYPE),)
		HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME				= libft_malloc_$(HOSTTYPE).so
NAME_SLINK	= libft_malloc.so

SRC_NAME		= main.c
OBJ_NAME		= $(SRC_NAME:.c=.o)
LIB_NAME		= -lft

SRC_PATH		= ./src/
OBJ_PATH		= ./obj/
LIB_PATH		= ./libft/
INC_PATH		= ./include ./libft/include ./libft/libft

SRC					= $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ					= $(SRC:.c=.o)
#OBJ				= $(addprefix $(OBJ_PATH),$(OBJ_NAME))
LIB 				= $(addprefix -L, $(LIB_PATH))
INC 				= $(addprefix -I ,$(INC_PATH))

CC					= gcc
CFLAGS			= -Wall -Wextra -Werror

RED					= \033[31;44m
GREEN				= \033[32;44m
ENDC				= \033[0m

.PHONY: all lib clean fclean re libfclean libclean

all: lib $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(INC) $(SRC) -o $(NAME) $(LIB) $(LIB_NAME)
	ln -sf libft_malloc_$(HOSTTYPE).so $(NAME_SLINK)
	@printf "$(GREEN) Make $(NAME) $(ENDC)\n"

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(INC)

lib:
	@make -C ./libft

clean:
	@printf "$(RED) Removing $(NAME) objects $(ENDC)\n"
	@rm -rfv $(OBJ) $(OBJ_PATH)

fclean: clean libfclean
	@printf "$(RED) Removing $(NAME) executables $(ENDC)\n"
	@rm -fv $(NAME) $(NAME_SLINK)

libclean:
	@printf "$(RED) Removing $(LIB_PATH) objects $(ENDC)\n"
	@make -C ./libft clean

libfclean:
	@printf "$(RED) Removing $(LIB_PATH) executables $(ENDC)\n"
	@make -C ./libft fclean

re: fclean
	@make all
