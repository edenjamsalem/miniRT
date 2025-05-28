# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eamsalem <eamsalem@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/06/17 14:04:43 by eamsalem          #+#    #+#              #
#    Updated: 2025/05/28 05:42:15 by eamsalem         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	miniRT

INCLUDES = ./includes
SRC_DIR = ./srcs
OBJ_DIR = ./bin
LIBS = ./libs

LIBFT = $(LIBS)/Libft
INCLUDEFLAGS = -I$(INCLUDES) -I$(LIBFT)/includes

CC = cc
CFLAGS = -Wall -Werror -Wextra

# Platform-specific settings
MLX_LINUX = $(LIBS)/minilibx-linux
MLX_MAC = $(LIBS)/minilibx-macos

LINKFLAGS_LINUX = -lmlx -lXext -lX11 -lm -lft
LINKFLAGS_MAC = -lmlx -framework OpenGL -framework AppKit -lm -lft

RED = \033[0;31m
GREEN = \033[0;32m
YELLOW = \033[0;33m
NC = \033[0m

SRCS = \
    $(SRC_DIR)/main.c \
    $(SRC_DIR)/init.c \
    $(SRC_DIR)/utils.c \
    $(SRC_DIR)/display/events.c \
    $(SRC_DIR)/display/mlx_utils.c \
    $(SRC_DIR)/display/rgb_utils.c \
    $(SRC_DIR)/display/rgb_utils2.c \
	$(SRC_DIR)/intersections/cy_curve.c \
	$(SRC_DIR)/intersections/cylinder.c \
	$(SRC_DIR)/intersections/intersections.c \
	$(SRC_DIR)/intersections/plane.c \
	$(SRC_DIR)/intersections/sphere.c \
    $(SRC_DIR)/math/misc.c \
    $(SRC_DIR)/math/basis.c \
    $(SRC_DIR)/math/vec_utils.c \
    $(SRC_DIR)/math/vec_utils2.c \
    $(SRC_DIR)/parse/assign_data.c \
    $(SRC_DIR)/parse/check_data.c \
    $(SRC_DIR)/parse/parse_objects.c \
    $(SRC_DIR)/parse/parse_scene.c \
    $(SRC_DIR)/parse/parse.c \
	$(SRC_DIR)/raytrace/blinn_phong.c \
    $(SRC_DIR)/raytrace/raytrace.c \
	$(SRC_DIR)/raytrace/shadow.c

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

#Main Targets
all: linux

linux: MLX_DIR = $(MLX_LINUX)
linux: LINKFLAGS = $(LINKFLAGS_LINUX)
linux: INCLUDEFLAGS += -I$(MLX_LINUX)
linux: build

mac: MLX_DIR = $(MLX_MAC)
mac: LINKFLAGS = $(LINKFLAGS_MAC)
mac: INCLUDEFLAGS += -I$(MLX_MAC)
mac: build

build: $(OBJ_DIR) $(OBJS)
	@make -C $(MLX_DIR)
	@make -C $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT) -L$(MLX_DIR) $(LINKFLAGS) -o $(NAME)
	@echo "${GREEN} $(NAME) created.${NC}"
	
$(OBJ_DIR):
	@echo "${YELLOW}Creating object directory $(OBJ_DIR)...${NC}"
	@mkdir -p $(OBJ_DIR)
	@echo "${GREEN}Object directory $(OBJ_DIR) created.${NC}"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) $(INCLUDEFLAGS) -c $< -o $@

${NAME}: $(OBJS)
	@make -C $(MLX)
	@make -C $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJS) -L$(LIBFT) -L$(MLX) $(LINKFLAGS) -o $(NAME)
	@echo "${GREEN}$(NAME) created.${NC}"

clean:
	@make clean -C $(MLX_LINUX) || true
	@make clean -C $(MLX_MAC) || true
	@make clean -C $(LIBFT)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@make fclean -C $(LIBFT)
	@rm -f $(NAME)
	@echo "${GREEN}$(NAME) cleaned.${NC}"

re: fclean all
	@echo "${GREEN}Target 're' completed.${NC}"

libs:
	@echo "${YELLOW}Updating submodules...${NC}"
	@git submodule update --init --recursive --remote
	@echo "${GREEN}Submodules updated.${NC}"

.PHONY: all clean fclean re libs
