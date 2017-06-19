# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgallois <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/04/11 16:35:34 by fgallois          #+#    #+#              #
#    Updated: 2017/05/11 17:32:33 by fgallois         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = rtv1
CC = gcc
OPTI = -g -O3
CFLAGS_DEBUG = -g3 -O0
CFLAGS = -c -Wall -Werror -Wextra -pedantic $(OPTI)

#Headers
LIBFT_INC_PATH = libft
LIBFT_INC_FILES = libft.h
INC_PATH = include
INC_FILES = rtv1.h vector.h object.h event.h
INCS = -I include -I framework/SDL2/include -I ./libft/libft.h
HEADERS =  $(LIBFT_INC_FILES:%.h=$(LIBFT_INC_PATH)/%.h)
HEADERS += $(INC_FILES:%.h=$(INC_PATH)/%.h)
CFLAGS += $(addprefix -I, $(INC_PATH) $(LIBFT_INC_PATH))

#Sources
SRC_PATH = srcs/
vpath %.c $(SRC_PATH)

SOURCES = average1.c average2.c change_view1.c change_view2.c cone1.c cone2.c creation.c cylinder1.c cylinder2.c \
display1.c display2.c error.c event.c init_env.c light.c main.c modify.c object.c parser.c plan.c read_object.c read.c register_object.c sphere.c \
thread.c vector1.c vector2.c vector3.c vector4.c \
virtual_screen.c
SRCS = $(addprefix srcs/, $(SOURCES))

# Libft
LIBFT_PATH = libft
LIBFT = $(LIBFT_PATH)/libft.a

LIB = -framework SDL2 -framework OpenGL -framework AppKit -lm
LIB_PATH = -F framework


#Objects
OBJ_PATH = ./objs
DIR_OBJ = objs/
#OBJ = $(SOURCES:.c = .o);
OBJS = $(addprefix objs/, $(FILES:.c=.o))
OBJECT = $(addprefix $(DIR_OBJ)/, $(SOURCES:%.c=%.o));

all: $(NAME)

$(NAME): $(OBJECTS)
	make -C ./libft
	$(CC) $(CFLAGS) $(SRCS) $(INCS)
	mkdir objs
	mv average1.o average2.o change_view1.o change_view2.o cone1.o cone2.o creation.o cylinder1.o cylinder2.o \
	display1.o display2.o error.o event.o init_env.o light.o main.o modify.o object.o parser.o plan.o read_object.o read.o register_object.o  \
	sphere.o thread.o vector1.o vector2.o vector3.o vector4.o virtual_screen.o $(DIR_OBJ)
	$(CC) $(LIB_PATH) $(LIB) $(LIBFT) -o $(NAME) $(OBJECT)

	@echo "\n-----------------------------------------"
	@echo "|\033[32;1m\t$(NAME) has been created !\t\t\033[0m|"
	@echo "-----------------------------------------\n"

$(OBJECTS): $(HEADERS) | $(OBJ_PATH)

$(OBJECTS): $(OBJ_PATH)/%.o: %.c
	$(CC) -c $(CFLAGS) $< -fsanitize=address -o $@
	@-mkdir -p $@

clean:
	@rm -rf $(OBJ_PATH)
	@echo "\n-------------------------------------------------"
	@echo "|\t\033[31mall $(NAME) files.o are deleted\033[0m\t\t|"
	@echo "-------------------------------------------------\n"

fclean: clean
	@rm -f $(NAME)
	@echo "\n---------------------------------"
	@echo "|\t\033[31m$(NAME) is deleted\033[0m\t\t|"
	@echo "---------------------------------\n"

re: fclean all

libs:
	@make -C libft

libs-clean:
	@make -C libft clean

libs-fclean:
	@make -C libft fclean

libs-re: libs-fclean
	@make -C libft re

fclean-all: fclean libs-fclean

debug: CFLAGS := $(filter-out $(OPTI),$(CFLAGS) $(CFLAGS_DEBUG))
debug: re
	@echo "\n-----------------------------------------------------------------"
	@echo "|\033[32;1m\tDebug mode for $(NAME) with $(CFLAGS_DEBUG)!\t\033[0m|"
	@echo "-----------------------------------------------------------------\n"

norme:
	norminette $(SRC)
	norminette $(INC_PATH)*.h

.PHONY:  all, clean, fclean, re, libs, libs-clean, libs-fclean, libs-re \
		fclean-all, debug, norme
