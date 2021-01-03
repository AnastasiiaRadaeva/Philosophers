# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kbatwoma <kbatwoma@student.21-school.ru>   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/12/28 18:56:41 by kbatwoma          #+#    #+#              #
#    Updated: 2020/12/28 19:14:20 by kbatwoma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

CC = gcc
OPFLAGS = -O2
FLAGS = -Wall -Wextra -Werror

LIBFT_DIR			=	libft/
HEADER_DIR			=	header/

MAJOR_DIR			=	srcs/major_functions/
MAJOR_LIST			=	minishell.c\
						promt_string.c\
						signal.c\
						read_cmd.c\
						creat_env.c\
						init_struct_data.c\
						error_output.c\
						program_exit.c\
						check_syntax.c

LEXER_DIR			=	srcs/lexer/
LEXER_LIST			=	lexer.c\
						lexer_2.c\
						lexer_3.c\
						lexer_4.c\
						freeing_memory_from_lexer.c
		
PARSER_DIR			=	srcs/parser/
PARSER_LIST			=	parse.c\
						add_lst_to_node.c\
						init.c\
						init_cmd.c\
						init_struct_commands.c

EXECUTOR_DIR		=	srcs/executor/
EXECUTOR_LIST		=	executor.c\
						executor_selection_cmd.c\
						check_syntax_error.c

BUILTIN_CMD_DIR		= 	srcs/builtin_commands/
BUILTIN_CMD_LIST	= 	pwd.c\
						env.c\
						cd.c\
						echo.c\
						export.c\
						export_2.c\
						export_3.c\
						unset.c\
						unset_2.c\
						unset_3.c\
						exit.c\
						ft_check_cmd_in_path.c \
						error_case.c

SOURCE_MAJOR			= $(addprefix $(MAJOR_DIR), $(MAJOR_LIST))
SOURCE_PARSER		= $(addprefix $(PARSER_DIR), $(PARSER_LIST))
SOURCE_EXECUTOR		= $(addprefix $(EXECUTOR_DIR), $(EXECUTOR_LIST))
SOURCE_LEXER		= $(addprefix $(LEXER_DIR), $(LEXER_LIST))
SOURCE_BUILTIN		= $(addprefix $(BUILTIN_CMD_DIR), $(BUILTIN_CMD_LIST))


OBJ	= $(patsubst %.c, %.o,	$(SOURCE_MAJOR)\
							$(SOURCE_PARSER)\
							$(SOURCE_EXECUTOR)\
							$(SOURCE_LEXER)\
							$(SOURCE_BUILTIN))
							
D_FILES = $(patsubst %.c, %.d,	$(SOURCE_MAJOR)\
								$(SOURCE_PARSER)\
								$(SOURCE_EXECUTOR)\
								$(SOURCE_LEXER)\
								$(SOURCE_BUILTIN))

.PHONY: all clean fclean re test norm

all: lib  $(NAME)

lib:
	make -C $(LIBFT_DIR)

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(FLAGS) $(OPFLAGS) -L$(LIBFT_DIR) -lft $(OBJ)
	
%.o: %.c 
	$(CC) $(FLAGS) $(OPFLAGS) -I$(HEADER_DIR) -c $< -o $@ -MD

include $(wildcard $(D_FILE))

clean:
	rm -rf $(OBJ) $(D_FILES)
	$(MAKE) clean -C $(LIBFT_DIR)


fclean : clean
	rm -rf $(LIBFT_DIR)/libft.a

	rm -rf $(NAME)


re : fclean all

norm:
	norminette $(HEADER_DIR). $(MAJOR_DIR). $(LEXER_DIR). $(PARSER_DIR). $(EXECUTOR_DIR). $(BUILTIN_CMD_DIR). $(MAKE) norm -C $(LIBFT_DIR)