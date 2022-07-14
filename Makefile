# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/17 13:12:34 by thbierne          #+#    #+#              #
#    Updated: 2022/07/14 17:01:39 by thbierne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRCS =	srcs/parsing/alloc_arg.c			\
		srcs/parsing/alloc_cmd.c			\
		srcs/parsing/alloc_llist_cmd_arg.c	\
		srcs/parsing/alloc_llist_env.c 		\
		srcs/parsing/alloc_pipe.c			\
		srcs/parsing/alloc_redi.c			\
		srcs/parsing/init_llist.c 			\
		srcs/builtins/list_del.c			\
		srcs/parsing/check_syntaxe.c		\
		srcs/parsing/ft_case_cmd.c			\
		srcs/parsing/ft_case_echo.c			\
		srcs/parsing/ft_free_llist.c		\
		srcs/parsing/heredoc.c				\
		srcs/main.c							\
		srcs/parsing/remove_quote.c			\
		srcs/parsing/replace_dollar.c		\
		srcs/parsing/test_cmd.c				\
		srcs/parsing/utils1.c				\
		srcs/parsing/utils2.c				\
		srcs/parsing/ft_redirection.c		\
		srcs/parsing/sort_redi.c			\
		srcs/builtins/echo.c				\
		srcs/builtins/fctnl_manager.c		\
		srcs/builtins/exit.c				\
		srcs/builtins/env.c					\
		srcs/builtins/pwd.c					\
		srcs/builtins/chdir.c				\
		srcs/builtins/unset.c				\
		srcs/builtins/ft_make_file.c		\
		srcs/parsing/create_redi.c			\
		srcs/builtins/export.c				\
		srcs/builtins/export_utils.c		\
		srcs/parsing/replace_home.c			\
		srcs/builtins/ft_exec_other.c		\
		srcs/parsing/add_last_redirection.c	\

OBJS_O = srcs/objs/alloc_arg.o				\
		srcs/objs/alloc_cmd.o				\
		srcs/objs/alloc_llist_cmd_arg.o		\
		srcs/objs/alloc_llist_env.o 		\
		srcs/objs/alloc_pipe.o				\
		srcs/objs/alloc_redi.o				\
		srcs/objs/init_llist.o 				\
		srcs/objs/list_del.o				\
		srcs/objs/check_syntaxe.o			\
		srcs/objs/ft_case_cmd.o				\
		srcs/objs/ft_case_echo.o			\
		srcs/objs/ft_free_llist.o			\
		srcs/objs/heredoc.o					\
		srcs/objs/main.o					\
		srcs/objs/remove_quote.o			\
		srcs/objs/replace_dollar.o			\
		srcs/objs/test_cmd.o				\
		srcs/objs/utils1.o					\
		srcs/objs/utils2.o					\
		srcs/objs/ft_redirection.o			\
		srcs/objs/sort_redi.o				\
		srcs/objs/echo.o					\
		srcs/objs/fctnl_manager.o			\
		srcs/objs/exit.o					\
		srcs/objs/env.o						\
		srcs/objs/pwd.o						\
		srcs/objs/chdir.o					\
		srcs/objs/unset.o					\
		srcs/objs/ft_make_file.o			\
		srcs/objs/create_redi.o				\
		srcs/objs/export.o					\
		srcs/objs/export_utils.o			\
		srcs/objs/replace_home.o			\
		srcs/objs/ft_exec_other.o			\
		srcs/objs/add_last_redirection.o	\

OBJS = $(SRCS:.c=.o)

D_OBJS = srcs/objs/

CC = gcc

FSAN = -fsanitize=address

CFLAG = -Wall -Wextra -Werror -g3

all: libft/libft.a ${NAME}

.c.o:
	$(CC) $(CFLAG) -Ilibft -c -I/includes/minishell.h $< -o $@

${NAME}: ${OBJS}
	${CC} ${OBJS} -Llibft -lft -lreadline -o $(NAME)
	mv $(OBJS) $(D_OBJS)


libft/libft.a:
	make -C libft

clean:
	rm -f ${OBJS_O}
	make -C libft clean

fclean: clean
	rm -f ${NAME}
	make -C libft fclean

re: fclean all

.PHONY: all clean fclean re
