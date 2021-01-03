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

NAME 			=	philo_one

CC 				=	gcc
FLAGS 			=	-Wall -Wextra -Werror

HEADER_DIR		=	header/

SRCS_DIR		=	srcs/
SRCS_LIST		=	philo.c\
					utils.c\
					timepad.c

SOURCE_SRCS		= $(addprefix $(SRCS_DIR), $(SRCS_LIST))
OBJ				= $(patsubst %.c, %.o,	$(SOURCE_SRCS))
D_FILES 		= $(patsubst %.c, %.d,	$(SOURCE_SRCS))

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(OBJ) -o $(NAME) -pthread

%.o : %.c
	$(CC) $(FLAGS) -I$(HEADER_DIR) -c $< -o $@ -MD
include $(wildcard $(D_FILE))

clean:
	rm -rf $(OBJ) $(D_FILES)

fclean : clean
	rm -rf $(NAME)

re : fclean all

.PHONY: all clean fclean re