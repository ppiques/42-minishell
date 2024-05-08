CC			= gcc
CFLAGS		= -Wall -Wextra -Werror

RM			= rm -f
RD			= rm -fd

FILE_DIR	= srcs
INC_DIR		= inc
OBJ_DIR		= objs

FILE_NAMES	= ft_atoi.c ft_itoa.c ft_putendl_fd.c ft_strlcpy.c ft_tolower.c \
			ft_bzero.c ft_memccpy.c ft_putnbr_fd.c ft_strlen.c ft_toupper.c \
			ft_calloc.c ft_memchr.c ft_putstr_fd.c ft_strmapi.c ft_isalnum.c \
			ft_memcmp.c ft_split.c ft_strncmp.c ft_isalpha.c ft_memcpy.c \
			ft_strchr.c ft_strnstr.c ft_isascii.c ft_memmove.c ft_strdup.c \
			ft_strrchr.c ft_isdigit.c ft_memset.c ft_strjoin.c ft_strtrim.c \
			ft_isprint.c ft_putchar_fd.c ft_strlcat.c ft_substr.c ft_lstadd_back.c \
			ft_lstclear.c ft_lstiter.c ft_lstmap.c ft_lstsize.c ft_lstadd_front.c \
			ft_lstdelone.c ft_lstlast.c ft_lstnew.c ft_lstconcat.c
OBJ_NAMES	= $(FILE_NAMES:.c=.o)
OBJS		= $(addprefix $(OBJ_DIR)/, $(OBJ_NAMES))

NAME		= libft.a

printheader :		
			@echo ---------------LIBFT COMPILING---------------
			@$(MAKE) --no-print-directory $(NAME)

all :		$(NAME)

$(NAME) :	$(OBJS)
			@echo Compiling library...
			@ar rc $(NAME) $(OBJS)
			@ranlib $(NAME)
			@echo All done !

$(OBJ_DIR)/%.o :	$(FILE_DIR)/%.c | $(OBJ_DIR)
					@echo Compiling $<
					@$(CC) $(CFLAGS) -c $< -o $@ -I./$(INC_DIR)/

$(OBJ_DIR) :	
				@mkdir -p $(OBJ_DIR)

hushclean :		
			@echo Removing .o files...
			@$(RM) $(OBJS)
			@$(RD) $(OBJ_DIR)

clean :		
			@echo Removing .o files...
			@$(RM) $(OBJS)
			@$(RD) $(OBJ_DIR)
			@echo All done !

fclean :	hushclean
			@echo Removing $(NAME)...
			@$(RM) $(NAME)
			@echo All done !

re :	fclean all

.PHONY :	all clean fclean re printheader hushclean
