#*************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgallois <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2016/11/17 13:57:26 by fgallois          #+#    #+#              #
#    Updated: 2017/10/13 18:55:14 by fgallois         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME= libft.a

SRC_NAME=	ft_lstadd.c \
			ft_lstnew.c \
			ft_lstdelone.c \
			ft_lstdel.c \
			ft_lstmap.c \
			ft_lstiter.c \
			ft_memset.c \
			ft_bzero.c \
			ft_memcpy.c \
			ft_memccpy.c \
			ft_putchar.c \
			ft_putstr.c \
			ft_strlen.c \
			ft_strcmp.c \
			ft_strncmp.c \
			ft_strcpy.c \
			ft_strncpy.c \
			ft_strcat.c \
			ft_strncat.c \
			ft_strdup.c \
			ft_strstr.c \
			ft_strnstr.c \
			ft_memmove.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_strlcat.c \
			ft_strchr.c \
			ft_strrchr.c \
			ft_atoi.c \
			ft_atof.c \
			ft_isalpha.c \
			ft_isdigit.c \
			ft_isalnum.c \
			ft_isascii.c \
			ft_isprint.c \
			ft_isspace.c \
			ft_toupper.c \
			ft_tolower.c \
			ft_memalloc.c \
			ft_memdel.c \
			ft_strnew.c \
			ft_strdel.c \
			ft_strclr.c \
			ft_striter.c \
			ft_striteri.c \
			ft_strmap.c \
			ft_putnbr.c \
			ft_putendl.c \
			ft_strequ.c \
			ft_strnequ.c \
			ft_putchar_fd.c \
			ft_putstr_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_itoa.c \
			ft_strsub.c \
			ft_strjoin.c \
			ft_strmapi.c \
			ft_strtrim.c \
			ft_strsplit.c \
			ft_splitlen.c \
			ft_realloc.c \
			ft_hextoint.c \
			get_next_line.c \
			ft_ispresent.c \
			ft_isnumber.c \
			ft_freetab.c

HEADER= ./includes/
OBJ= $(SRC_NAME:.c=.o)

all: $(NAME)

$(NAME):
	@gcc -Wall -Wextra -Werror -g -c $(SRC_NAME) -I $(HEADER)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@echo "\033[32;1mlibft is ready\033[0m"

clean:
	@rm -rf $(OBJ)
	@echo "\033[37mall files.o are removed\033[0m"

fclean: clean
	@rm -rf $(NAME)
	@echo "\033[31m$(NAME) is deleted\033[0m"

re: fclean all

.PHONY: all clean fclean re
