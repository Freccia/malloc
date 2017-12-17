# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: lfabbro <marvin@42.fr>                     +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/04 21:18:10 by lfabbro           #+#    #+#              #
#    Updated: 2017/12/17 16:30:09 by lfabbro          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #


ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME		= libft_malloc_$(HOSTTYPE).so
NAME_SLINK	= libft_malloc.so

NAME_TEST	= test_malloc
SRC_TEST	= main.c
SRC_T		= $(addprefix $(SRC_PATH),$(SRC_TEST))

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -fPIC -g3

SRC_NAME	= malloc.c free.c realloc.c show_alloc_mem.c alloc_mem.c utils.c find.c
OBJ_NAME	= $(SRC_NAME:.c=.o)
LIB_NAME	= -lft -lft_malloc

SRC_PATH	= ./src/
OBJ_PATH	= ./obj/
LIB_PATH	= ./libft/ .
INC_PATH	= ./include ./libft/include ./libft/libft

SRC			= $(addprefix $(SRC_PATH),$(SRC_NAME))
OBJ			= $(SRC:%.c=%.o)
LIB 		= $(addprefix -L, $(LIB_PATH))
INC 		= $(addprefix -I ,$(INC_PATH))

RED			= \033[0;31m
GREEN		= \033[0;32m
WHITE		= \033[1;37m
ENDC		= \033[0m

.PHONY: all clean fclean re lib libclean libfclean norme

all: lib $(NAME)

$(NAME): $(OBJ)
	@printf "$(WHITE) Making malloc $(ENDC)\n"
	$(CC) $(CFLAGS) -shared -o $@ $(OBJ) $(INC) $(LIB) -lft
	ln -sf $(NAME) $(NAME_SLINK)
	@printf "$(WHITE) [ $(GREEN)OK $(WHITE)] $(NAME) $(ENDC)\n"

%.o: %.c
	$(CC) $(CFLAGS) $(INC) -o $@ -c $<

test:
	@printf "$(WHITE) Making $(NAME_TEST) $(ENDC)\n"
	$(CC) -I include/ -I libft/libft/ -o $(NAME_TEST) tests/main.c -L libft -L. -lft -lft_malloc
	$(CC) -o test0 ./tests/test0.c
	$(CC) -o test1 ./tests/test1.c
	$(CC) -o test2 ./tests/test2.c
	$(CC) -o test3 ./tests/test3.c
	$(CC) -o test3+ ./tests/test3+.c
	$(CC) -o test4 ./tests/test4.c
	$(CC) -o test5 ./tests/test5.c -I include/ -I libft/libft/ -L. -lft_malloc 

clean:
	@rm -vrf $(OBJ) $(OBJ_PATH) $(SRC_PATH)/*.o
	@rm -vf test[0-9] test[0-9][+0-9] test_malloc

fclean: clean libfclean
	@rm -fv libft_malloc_*.so $(NAME_SLINK) $(NAME_TEST) test[0-9]
	@printf "$(WHITE) [ $(RED)REMOVED $(WHITE)] $(NAME_SLINK) $(ENDC)\n"

lib:
	@make -C ./libft

libclean:
	@make -C ./libft clean

libfclean:
	@make -C ./libft fclean

re: fclean all

norme :
	@printf "$(WHITE) Norminette $(ENDC)\n"
	norminette **/*.[ch]
