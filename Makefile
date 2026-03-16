NAME		= miniRT
BONUS_NAME	= miniRT_bonus

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -I. -Iinc -Iinc/libft -Iinc/libmlx -I$(GNL_DIR)
LDFLAGS		= -Linc/libft -lft -Linc/libmlx -lmlx -lXext -lX11 -lm

SRC_DIR		= src
BONUS_DIR	= bonus
OBJ_DIR		= obj
LIBFT_DIR	= inc/libft
MLX_DIR		= inc/libmlx
GNL_DIR		= inc/gnl

PARSE_DIR	= src/parse
MINILIB_DIR	= src/minilib
MATH_DIR	= src/math
MAIN_DIR	= src/main
RENDER_DIR	= src/render

B_PARSE_DIR	  = bonus/parse
B_MINILIB_DIR = bonus/minilib
B_MATH_DIR	  = bonus/math
B_MAIN_DIR	  = bonus/main
B_RENDER_DIR  = bonus/render

MANDATORY_SRCS	= $(MAIN_DIR)/main.c \
				  $(PARSE_DIR)/parse_utils.c $(PARSE_DIR)/parse_things.c \
				  $(PARSE_DIR)/parse_objects.c $(PARSE_DIR)/parse_free.c \
				  $(MINILIB_DIR)/mlx_setup.c $(PARSE_DIR)/parser.c \
				  $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c \
				  $(MATH_DIR)/vec.c $(MATH_DIR)/vec2.c $(MATH_DIR)/cam_in_obj.c \
				  $(RENDER_DIR)/render.c $(MATH_DIR)/hit_and_ray.c \
				  $(MATH_DIR)/cylinder.c $(MATH_DIR)/plane_and_sphere.c \
				  $(MATH_DIR)/utils.c $(MATH_DIR)/light.c $(MATH_DIR)/normal.c
MANDATORY_OBJS	= $(patsubst %.c,$(OBJ_DIR)/%.o,$(MANDATORY_SRCS))

BONUS_SRCS		= $(B_MAIN_DIR)/main_bonus.c \
				  $(B_PARSE_DIR)/parse_utils_bonus.c $(B_PARSE_DIR)/parse_things_bonus.c \
				  $(B_PARSE_DIR)/parse_cone_bonus.c $(B_PARSE_DIR)/parse_objects_bonus.c $(B_PARSE_DIR)/parse_free_bonus.c \
				  $(B_MINILIB_DIR)/mlx_setup_bonus.c $(B_PARSE_DIR)/parser_bonus.c \
				  $(GNL_DIR)/get_next_line.c $(GNL_DIR)/get_next_line_utils.c \
				  $(B_MATH_DIR)/vec_bonus.c $(B_MATH_DIR)/vec2_bonus.c \
				  $(B_MATH_DIR)/cam_in_obj_bonus.c $(B_RENDER_DIR)/render_bonus.c \
				  $(B_MINILIB_DIR)/mlx_texture_bonus.c $(B_MATH_DIR)/textrure_bonus.c \
				  $(B_MATH_DIR)/hit_and_ray_bonus.c $(B_MATH_DIR)/cylinder_bonus.c \
				  $(B_MATH_DIR)/plane_and_sphere_bonus.c $(B_MATH_DIR)/utils_bonus.c \
				  $(B_MATH_DIR)/light_bonus.c $(B_MATH_DIR)/normal_bonus.c $(B_MATH_DIR)/cone_bonus.c $(B_MATH_DIR)/tex_cone_bonus.c
BONUS_OBJS		= $(patsubst %.c,$(OBJ_DIR)/%.o,$(BONUS_SRCS))

# --- Colors ---
BLUE		= \033[0;34m
CYAN		= \033[0;36m
RESET		= \033[0m

# --- Rules ---
all: $(NAME)

$(LIBFT_DIR)/libft.a:
	@echo "$(BLUE)Compiling libft...$(RESET)"
	@make -C $(LIBFT_DIR) > /dev/null

$(MLX_DIR)/libmlx.a:
	@echo "$(BLUE)Compiling libmlx silently...$(RESET)"
	@make -C $(MLX_DIR) > /dev/null 2>&1

# Compile Mandatory
$(NAME): $(LIBFT_DIR)/libft.a $(MLX_DIR)/libmlx.a $(MANDATORY_OBJS)
	@echo "$(BLUE)Linking $(NAME)...$(RESET)"
	@$(CC) $(MANDATORY_OBJS) $(LDFLAGS) -o $(NAME)
	@echo "$(CYAN)Done!$(RESET)"

# Compile Bonus
bonus: $(LIBFT_DIR)/libft.a $(MLX_DIR)/libmlx.a $(BONUS_OBJS)
	@echo "$(BLUE)Linking $(BONUS_NAME)...$(RESET)"
	@$(CC) $(BONUS_OBJS) $(LDFLAGS) -o $(BONUS_NAME)
	@echo "$(CYAN)Bonus Done!$(RESET)"

# Generic object compilation rule
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(dir $@)
	@echo "$(BLUE)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@echo "$(BLUE)Cleaning obj files$(RESET)"
	@rm -rf $(OBJ_DIR)
	@make -C $(LIBFT_DIR) clean > /dev/null
	@make -C $(MLX_DIR) clean > /dev/null

fclean: clean
	@echo "$(BLUE)cleaned everything$(RESET)"
	@rm -f $(NAME) $(BONUS_NAME)
	@rm -f $(LIBFT_DIR)/libft.a
	@rm -f $(MLX_DIR)/libmlx.a

re: fclean all

.PHONY: all clean fclean re bonus