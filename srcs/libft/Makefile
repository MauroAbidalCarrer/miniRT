# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: maabidal <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/29 20:08:50 by maabidal          #+#    #+#              #
#    Updated: 2022/05/30 17:07:58 by maabidal         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS =	ft_atoi.c\
		ft_bzero.c\
		ft_calloc.c\
		ft_isalnum.c\
		ft_isalpha.c\
		ft_isascii.c\
		ft_isdigit.c\
		ft_isprint.c\
		ft_itoa.c\
		ft_memchr.c\
		ft_memcmp.c\
		ft_memcpy.c\
		ft_memmove.c\
		ft_memset.c\
		ft_putchar_fd.c\
		ft_putendl_fd.c\
		ft_putnbr_fd.c\
		ft_putstr_fd.c\
		ft_split.c\
		ft_strchr.c\
		ft_strdup.c\
		ft_striteri.c\
		ft_strjoin.c\
		ft_strlcat.c\
		ft_strlcpy.c\
		ft_strlen.c\
		ft_strmapi.c\
		ft_strncmp.c\
		ft_strnstr.c\
		ft_strrchr.c\
		ft_strtrim.c\
		ft_substr.c\
		ft_tolower.c\
		ft_toupper.c\
		skip_spaces.c\

BONUSSRCS =	ft_lstadd_back.c\
		ft_lstclear.c\
	     	ft_lstiter.c\
	      	ft_lstmap.c\
	      	ft_lstsize.c\
		ft_lstadd_front.c\
	       	ft_lstdelone.c\
		ft_lstlast.c\
		ft_lstnew.c

NAME	= libft.a
CC	= gcc
CFLAGS	= -Wall -Wextra -Werror
RM	= rm -f
OBJS	= $(SRCS:.c=.o)
BNSOBJS	= $(BONUSSRCS:.c=.o)

all : $(NAME)

$(NAME) : $(OBJS) $(BNSOBJS)
	ar -rcs $@ $^

bonus : $(OBJS) $(BNSOBJS)
	ar -rcs $(NAME) $^

.o : .c
	$(CC) $(CFLAGS) -c $< -o $@ -I ./

clean : 
	$(RM) $(OBJS) $(BNSOBJS)

fclean : clean
	$(RM) $(NAME)

re :    fclean all

so:
	$(CC) -fPIC $(CFLAGS) -c $(SRCS) $(BONUSSRCS)
	gcc -shared -o libft.so $(OBJS) $(BNSOBJS)

.PHONY : all clean fclean re
