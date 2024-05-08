# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ppiques <ppiques@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/01 20:31:03 by cferrari          #+#    #+#              #
#    Updated: 2022/05/01 05:47:26 by ppiques          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= minishell

RM			= rm -f
RD			= rm -fr

FILE_DIR	= srcs
INC_DIR		= inc
OBJ_DIR		= objs
LIBFT_DIR	= libft

FILE_NAMES	= builtin.c builtin_utils.c cmd_create_args.c \
cmd_parser.c cmd_smart_split.c \
cmd_redirs.c cmd_redirs_utils.c \
cmd_redirs_utils2.c echo.c \
envp.c envp_utils.c exit.c export.c export2.c \
forks.c heredoc.c heredoc_utils.c heredoc_utils2.c \
list_var_handler.c list_var_handler_utils.c memfree.c \
memfree2.c minishell.c nopipe.c open_redirs.c\
pipe_handler.c pipe_split.c pipe_split_utils.c \
prompt.c safe_atol.c special_chars.c \
str_counter.c str_extractor.c str_extractor_utils.c\
str_utils.c syntax_checker.c \
tryexec.c unset.c utils.c utils2.c var_utils.c

OBJ_NAMES	= ${FILE_NAMES:.c=.o}
OBJS		= $(addprefix $(OBJ_DIR)/, $(OBJ_NAMES))

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror -g
#CFLAGS	+= -g3 -fsanitize=address
#CFLAGS	+= -g3 -fsanitize=thread

LIBR		= ranlib

all:		${NAME}

$(NAME):	${OBJS} 
			@echo "\033[1;32mCreating lib ...\033[0m"
			@$(MAKE) -C ./libft
			@echo "\033[1;32mCompiling ...\033[0m"
			@$(CC) $(CFLAGS) $(OBJS) -I./$(INC_DIR)/ -L./$(LIBFT_DIR)/ -lft -lreadline -o $(NAME) > /dev/null
			@echo "\033[1;32mDone\033[0m"

$(OBJ_DIR)/%.o :	$(FILE_DIR)/%.c ${INC_DIR}/minishell.h | $(OBJ_DIR)
					@echo "\033[1;32mCompiling $<\033[0m"
					@$(CC) $(CFLAGS) -c $< -o $@ -I./$(INC_DIR)/

$(OBJ_DIR) :
				@mkdir -p $(OBJ_DIR)

clean:
			@echo "\033[1;32mDeleting objects ...\033[0m"
			@${RM} ${OBJS}
			@$(RD) $(OBJ_DIR)
			@echo "\033[1;32mCleaning libft ...\033[0m"
			@$(MAKE) clean -C ./libft/ > /dev/null
			@echo "\033[1;32mDone\033[0m"

fclean:		clean
			@echo "\033[1;32mDeleting libraries and executable\033[0m"
			@${RM} ${NAME} > /dev/null
			@$(RM) ./minishell > /dev/null
			@$(MAKE) fclean -C ./libft/ > /dev/null
			@echo "\033[1;32mDone\033[0m"

re:			fclean all

.PHONY: 	all clean fclean re
