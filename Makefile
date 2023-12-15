# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttikanoj <ttikanoj@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/20 10:04:13 by ttikanoj          #+#    #+#              #
#    Updated: 2023/12/15 09:23:18 by ttikanoj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRCS_DIR = srcs
OBJS_DIR = objs
LIBFT_DIR = $(SRCS_DIR)/libft

SRC_FILES = main.c arg_checker.c map_parser.c errors.c draw.c map_validator.c \
			map_validator_utils.c minimap.c keys.c run_cub3d.c process_textures.c \
			raycast_textured.c movement.c movement2.c dda.c raycast_textured_utils.c \
			flood.c minimap_utils.c update_game.c map_parser_utils.c map_parser_utils2.c \
			map_parser_utils3.c map_parser_utils4.c map_parser_utils5.c

SRCS := $(addprefix $(SRCS_DIR)/, $(SRC_FILES))
HEADERS := srcs/cub3d.h
OBJ := $(patsubst $(SRCS_DIR)/%.c, $(OBJS_DIR)/%.o, $(SRCS))

FLAGS = -Wall -Werror -Wextra
LIBFT = -L $(LIBFT_DIR) -lft
MLX_FLAGS = -lmlx -framework OpenGL -framework AppKit
INCLUDES = -I $(SRCS_DIR) -I $(HEADERS)

all: $(NAME)

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c
	mkdir -p $(OBJS_DIR)
	cc $(FLAGS) $(INCLUDES) -c $< -o $@

$(NAME): $(OBJ)
	$(MAKE) -C $(LIBFT_DIR)
	cc $(FLAGS) $(OBJ) $(MLX_FLAGS) $(LIBFT) -o $(NAME)

clean:
	$(MAKE) clean -C $(LIBFT_DIR)
	rm -rf $(OBJS_DIR)

fclean: clean
	$(MAKE) fclean -C $(LIBFT_DIR)
	rm -f $(NAME)

re: fclean all
