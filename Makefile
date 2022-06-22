# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avillar <avillar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/17 13:12:34 by thbierne          #+#    #+#              #
#    Updated: 2022/06/22 13:41:36 by avillar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS =	srcs/alloc_arg.c			\
		srcs/alloc_cmd.c			\
		srcs/alloc_llist_cmd_arg.c	\
		srcs/alloc_llist_env.c 		\
		srcs/alloc_pipe.c			\
		srcs/alloc_redi.c			\
		srcs/init_llist.c 			\
		srcs/check_syntaxe.c		\
		srcs/ft_case_cmd.c			\
		srcs/ft_case_echo.c			\
		srcs/ft_free_llist.c		\
		srcs/heredoc.c				\
		srcs/main.c					\
		srcs/remove_quote.c			\
		srcs/replace_dollar.c		\
		srcs/test_cmd.c				\
		srcs/utils1.c				\
		srcs/utils2.c				\
		srcs/ft_redirection.c		\
		srcs/sort_redi.c			\
		srcs/exec_llist.c			\
		srcs/echo.c					\
		srcs/fctnl_manager.c		\
		srcs/exit.c					\
		srcs/env.c					\

OBJS = $(SRCS:.c=.o)

CC = gcc

CFLAG = -Wall -Wextra -Werror

all: libft/libft.a ${NAME}

.c.o:
	$(CC) $(CFLAG) -I./includes/libft -c -I/includes/minishell.h $< -o $@

${NAME}: ${OBJS}
	${CC} ${OBJS} -L./includes/libft -lft -lreadline -o $(NAME)


libft/libft.a:
	make -C ./includes/libft

clean:
	rm -f $(OBJS)
	make -C ./includes/libft clean

fclean: clean
	rm -f ${NAME}
	make -C ./includes/libft fclean

re: fclean all

.PHONY: all clean fclean re
