NAME		=	miniRT

CC			=	cc
CFLAGS		=	-Wall -Wextra -Werror -I. -Iinc -Iinc/libft -Iinc/libmlx
LDFLAGS		=	-Linc/libft -lft -Linc/libmlx -lmlx -lXext -lX11 -lm

SRC_DIR		=	src
OBJ_DIR		=	obj
LIBFT_DIR	=	inc/libft
MLX_DIR		=	inc/libmlx

VPATH	=	$(SRC_DIR)

SRC_FILES	:= main.c

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
