# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbatwoma <kbatwoma@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/28 18:56:41 by kbatwoma          #+#    #+#              #
#    Updated: 2020/12/28 19:29:42 by kbatwoma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#NAME 			=	philo_one
#
#CC 				=	clang
#FLAGS 			=	-Wall -Wextra -Werror
#
#HEADER_DIR		=	header/
#
#SRCS_DIR		=	srcs/
#SRCS_LIST		=	philo.c\
#					utils.c\
#					timepad.c\
#					dealings.c
#
#SOURCE_SRCS		= $(addprefix $(SRCS_DIR), $(SRCS_LIST))
#OBJ				= $(patsubst %.c, %.o,	$(SOURCE_SRCS))
#D_FILES 		= $(patsubst %.c, %.d,	$(SOURCE_SRCS))
#
#all: $(NAME)
#
#$(NAME): $(OBJ)
#	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -pthread -g
#
#%.o : %.c
#	$(CC) $(FLAGS) -I$(HEADER_DIR) -c $< -o $@ -MD -g
#include $(wildcard $(D_FILE))
#
#clean:
#	rm -rf $(OBJ) $(D_FILES)
#
#fclean : clean
#	rm -rf $(NAME)
#
#re : fclean all
#
#.PHONY: all clean fclean re

NAME = philo_one
CC = clang -g
FLAGS = -Wall -Wextra -Werror
HEADER_DIR  = header/
SRCS_DIR    = srcs/
SRCS_LIST   = philo.c\
              utils.c\
              timepad.c\
              dealings.c\
              dealings_utils.c
SOURCE      = $(addprefix $(SRCS_DIR), $(SRCS_LIST))
OBJ         = $(patsubst %.c, %.o, $(SOURCE))
D_FILE      = $(patsubst %.c, %.d, $(SOURCE))

all: $(NAME)
$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -pthread
%.o : %.c
	$(CC) $(FLAGS) -I$(HEADER_DIR) -c $< -o $@ -MD
include $(wildcard $(D_FILE))
clean:
	rm -rf $(OBJ) $(D_FILE);
fclean: clean
	rm -rf $(NAME)
re: fclean all
.PHONY: all clean fclean re norm