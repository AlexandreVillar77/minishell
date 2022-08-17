# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avillar <avillar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/17 13:12:34 by thbierne          #+#    #+#              #
#    Updated: 2022/08/17 11:38:23 by avillar          ###   ########.fr        #
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
		srcs/replace_home.c			\
		srcs/ft_exec_other.c		\
		srcs/add_last_redirection.c	\
		srcs/rl_get.c				\
		srcs/ft_pipex.c				\
		srcs/alloc_heredoc.c		\
		srcs/del_arg.c				\
		srcs/export_h.c				\
		srcs/delete_empty_redi.c	\
		srcs/chdir_utils.c			\
		srcs/echo_utils.c			\
		srcs/export_h_utils.c		\
		srcs/export_utils2.c		\
		srcs/ft_exec_others_util.c	\
		srcs/child_manager.c		\
		srcs/ft_pipex_utils.c		\
		srcs/pip_utils.c			\
		srcs/pwd_utils.c			\
		srcs/unset_utils.c			\

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
	make -C libft clean

fclean: clean
	rm -f ${NAME}
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
