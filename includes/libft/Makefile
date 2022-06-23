# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avillar <avillar@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/04 12:49:42 by avillar           #+#    #+#              #
#    Updated: 2022/06/22 13:35:34 by avillar          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= libft.a

SRCS		= 	ft_strlen.c			\
				ft_split_utils.c	\
				ft_isalnum.c 		\
				ft_isdigit.c 		\
				ft_memchr.c 		\
				ft_memset.c			\
				ft_strlcpy.c		\
				ft_strnstr.c		\
				ft_toupper.c		\
				ft_atoi.c			\
				ft_isalpha.c		\
				ft_isprint.c		\
				ft_memcpy.c			\
				ft_strchr.c			\
				ft_strrchr.c		\
				ft_bzero.c			\
				ft_isascii.c		\
				ft_memccpy.c		\
				ft_memmove.c		\
				ft_strlcat.c		\
				ft_strncmp.c		\
				ft_tolower.c		\
				ft_memcmp.c			\
				ft_calloc.c			\
				ft_strdup.c			\
				ft_substr.c			\
				ft_strjoin.c		\
				ft_strtrim.c		\
				ft_split.c			\
				ft_itoa.c			\
				ft_strmapi.c		\
				ft_putchar_fd.c		\
				ft_putstr_fd.c		\
				ft_putendl_fd.c		\
				ft_putnbr_fd.c		\
				ft_putnbr_fd.c		\
				ft_lstnew.c			\
				ft_lstadd_front.c	\
				ft_lstsize.c		\
				ft_lstlast.c		\
				ft_lstadd_back.c	\
				ft_lstdelone.c		\
				ft_lstclear.c		\
				ft_lstiter.c		\
				ft_lstmap.c			\

OBJS = $(addprefix src/, ${SRCS:.c=.o})

.c.o:
			gcc -Wall -Wextra -Werror -c -I./include/ $< -o $< -o ${<:.c=.o}

${NAME}:	${OBJS}
			ar -rcs $@ $^

bonus:		${OBJSB}
			ar -rcs ${NAME} $^

all:		${NAME}

clean:
			rm -f ${OBJS} ${OBJSB}

fclean:		clean
			rm -f ${NAME}

re:			fclean all

.PHONY:		all clean fclean re
