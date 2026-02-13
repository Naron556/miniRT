NAME	=	miniRT

CC		=	cc
CFLAGS	=	-Wall -Wextra -Werror -I. -Iinc -Iinc/libft -Iinc/libmlx -I$(GNL_DIR)
LDFLAGS	=	-Linc/libft -lft -Linc/libmlx -lmlx -lXext -lX11 -lm

SRC_DIR		=	src
OBJ_DIR		=	obj
LIBFT_DIR	=	inc/libft
MLX_DIR		=	inc/libmlx
GNL_DIR		=	inc/gnl
PARSE_DIR	=	src/parse

VPATH		=	$(SRC_DIR) $(PARSE_DIR) $(GNL_DIR)

SRC_FILES	=	main.c \
				parse_utils.c \
				parse_struct.c \
				parse_scene.c \
				parse_objects.c \
				free_exit_error.c \
				parser.c \
				get_next_line.c \
				get_next_line_utils.c

OBJS		=	$(addprefix $(OBJ_DIR)/, $(SRC_FILES:.c=.o))

BLUE		=	\033[0;34m
CYAN		=	\033[0;36m
RESET		=	\033[0m

all: $(NAME)

$(LIBFT_DIR)/libft.a:
	@echo "$(BLUE)Compiling libft...$(RESET)"
	@make -C $(LIBFT_DIR) > /dev/null

$(MLX_DIR)/libmlx.a:
	@echo "$(BLUE)Compiling libmlx silently...$(RESET)"
	@make -C $(MLX_DIR) > /dev/null 2>&1

$(NAME): $(LIBFT_DIR)/libft.a $(MLX_DIR)/libmlx.a $(OBJS)
	@echo "$(BLUE)Linking $(NAME)...$(RESET)"
	@$(CC) $(OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(CYAN)Done!$(RESET)"

# This rule works for files in src/ AND inc/gnl/ because of VPATH
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(OBJ_DIR)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(BLUE)Cleaning obj files$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean > /dev/null
	@make -C $(MLX_DIR) clean > /dev/null

fclean: clean
	@echo "$(BLUE)cleaned everything$(RESET)"
	@rm -f $(NAME)
	@rm -f $(LIBFT_DIR)/libft.a
	@rm -f $(MLX_DIR)/libmlx.a

re: fclean all

.PHONY: all clean fclean re