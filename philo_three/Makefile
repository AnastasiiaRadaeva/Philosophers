# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbatwoma <kbatwoma@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/01/20 22:47:41 by kbatwoma          #+#    #+#              #
#    Updated: 2021/01/17 23:19:42 by kbatwoma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME 		= 	philo_three
CC 			= 	clang -g
FLAGS 		= 	-Wall -Wextra -Werror
HEADER_DIR  =	header/
SRCS_DIR    = 	srcs/
SRCS_LIST   =	philo.c\
				philo_inside.c\
				initialization.c\
				utils.c\
				timepad.c\
				dealings.c\
				dealings_utils.c\
				free_destroy.c
SRCS		= $(addprefix $(SRCS_DIR), $(SRCS_LIST))
OBJS		= $(patsubst %.c, %.o, $(SRCS))
D_FILES		= $(patsubst %.c, %.d, $(SRCS))

all: $(NAME)
$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME) -pthread
%.o : %.c
	$(CC) $(FLAGS) -I$(HEADER_DIR) -c $< -o $@ -MD
include $(wildcard $(D_FILES))
clean:
	rm -rf $(OBJS) $(D_FILES);
fclean: clean
	rm -rf $(NAME)
re: fclean all
.PHONY: all clean fclean re norm