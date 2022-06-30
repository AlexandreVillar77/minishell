# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avillar <avillar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/17 13:12:34 by thbierne          #+#    #+#              #
#    Updated: 2022/06/27 15:43:40 by avillar          ###   ########.fr        #
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
		srcs/list_del.c				\
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
		srcs/pwd.c					\
		srcs/chdir.c				\
		srcs/unset.c				\
		srcs/ft_make_file.c			\
		srcs/create_redi.c			\
		srcs/export.c				\
		srcs/export_utils.c			\

OBJS = $(SRCS:.c=.o)

CC = gcc

FSAN = -fsanitize=address

CFLAG = -Wall -Wextra -Werror -g3

all: libft/libft.a ${NAME}

.c.o:
	$(CC) $(CFLAG) -Ilibft -c -I/includes/minishell.h $< -o $@

${NAME}: ${OBJS}
	${CC} ${OBJS} -Llibft -lft -lreadline -o $(NAME)


libft/libft.a:
	make -C libft

clean:
	rm -f ${OBJS}

fclean: clean
	rm -f ${NAME}
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
