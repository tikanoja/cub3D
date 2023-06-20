# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/20 10:04:13 by ttikanoj          #+#    #+#              #
#    Updated: 2023/06/20 12:32:02 by jaurasma         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC = ./main.c arg_checker.c map_parser.c errors.c draw.c map_validator.c\
	map_validator_utils.c minimap.c keys.c run_cub3d.c\
	process_textures.c raycast_textured.c movement.c movement2.c dda.c\
	raycast_textured_utils.c flood.c minimap_utils.c update_game.c\
	map_parser_utils.c map_parser_utils2.c map_parser_utils3.c \
	map_parser_utils4.c

OBJ = ./main.o arg_checker.o map_parser.o errors.o draw.o map_validator.o\
	map_validator_utils.o minimap.o keys.o run_cub3d.o\
	process_textures.o  raycast_textured.o movement.o movement2.o dda.o\
	raycast_textured_utils.o flood.o minimap_utils.o update_game.o\
	map_parser_utils.o map_parser_utils2.o map_parser_utils3.o \
	map_parser_utils4.o

HEADERS = -I ./mlx

FLAGS = -Wall -Werror -Wextra

all: $(NAME)

%.o: %.c
	cc $(FLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(OBJ)
	$(MAKE) -C libft
	cc $(FLAGS) $(OBJ) -lmlx -L./libft -lft -framework OpenGL -framework AppKit -o $(NAME)

clean:
	$(MAKE) clean -C libft
	rm -f $(OBJ)

fclean: clean
	$(MAKE) fclean -C libft
	rm -f $(NAME)

re: fclean all
