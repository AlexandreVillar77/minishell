# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/10/07 11:05:52 by alewalla          #+#    #+#              #
#    Updated: 2022/05/07 12:59:07 by alewalla         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_memset.c		\
	   ft_bzero.c		\
	   ft_memcpy.c		\
	   ft_memccpy.c		\
	   ft_memmove.c 	\
	   ft_memchr.c		\
	   ft_memcmp.c		\
	   ft_isalpha.c 	\
	   ft_isupper.c		\
	   ft_islower.c		\
	   ft_isdigit.c		\
	   ft_isalnum.c		\
	   ft_isalphanum.c	\
	   ft_isascii.c		\
	   ft_isspace.c		\
	   ft_isprint.c		\
	   ft_toupper.c		\
	   ft_tolower.c		\
	   ft_strchr.c		\
	   ft_strrchr.c		\
	   ft_strncmp.c		\
	   ft_strlcpy.c		\
	   ft_strlcat.c		\
	   ft_strnstr.c		\
	   ft_atoi.c		\
	   ft_calloc.c		\
	   ft_strdup.c		\
	   ft_substr.c		\
	   ft_strjoin.c 	\
	   ft_strtrim.c		\
	   ft_split.c		\
	   ft_itoa.c		\
	   ft_strmapi.c		\
	   ft_putchar_fd.c	\
	   ft_putstr_fd.c	\
	   ft_putendl_fd.c	\
	   ft_putnbr_fd.c	\
	   ft_strchr_int.c	\
	   ft_strlen.c		\
	   ft_intlen.c		\
	   ft_tablen.c		\
	   ft_strstr.c		\
	   ft_findstr.c		\
	   ft_strcmp.c		\
	   ft_puttab.c		\
	   ft_putstr.c		\

NAME = libft.a

OBJS = $(SRCS:.c=.o)

OBJSB = $(OBJS) $(SRCSB:.c=.o)

CC = gcc

CC_FLAGS = -c -Wall -Wextra -Werror -I .

$(NAME): $(OBJS)
	$(CC) $(SRCS) $(CC_FLAGS)
	ar r $(NAME) $(OBJS)

all: $(NAME)

clean:
	rm -f $(OBJSB)

fclean: clean
	rm -f $(NAME)

re: fclean all

bonus: $(OBJSB)
	$(CC) $(SRCS) $(SRCSB) $(CC_FLAGS)
	ar r $(NAME) $(OBJSB)
