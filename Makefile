# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/03/17 13:12:34 by thbierne          #+#    #+#              #
#    Updated: 2022/06/13 13:58:29 by thbierne         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell
DIR_LIB = ./includes/libft
LIB = $(DIR_LIB)/libft.a

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

OBJS = $(SRCS:.c=.o)

CC = clang

INCLUDES = -I./includes -I./includes/libft
CFLAGS = -Wall -Wextra -Werror -g $(INCLUDES)

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS) $(LIB)
	$(CC) $(CFLAGS) -lreadline -o $(NAME) $(OBJS) $(LIB) 
	
$(LIB): $(DIR_LIB)
	@make -C $(DIR_LIB)

clean:
	$(RM) $(OBJS)
	$(MAKE) -C $(DIR_LIB) clean

fclean: clean
	$(RM) $(NAME) pwd echo env export
	$(MAKE) -C $(DIR_LIB) fclean

re: fclean all

.PHONY: all clean fclean re