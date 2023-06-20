# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ttikanoj <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/20 10:04:13 by ttikanoj          #+#    #+#              #
#    Updated: 2023/06/20 10:04:14 by ttikanoj         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = cub3D

SRC = ./main.c arg_checker.c map_parser.c errors.c draw.c map_validator.c\
	map_validator_utils.c minimap.c keys.c run_cub3d.c\
	process_textures.c raycast_textured.c movement.c movement2.c dda.c\
	raycast_textured_utils.c

OBJ = ./main.o arg_checker.o map_parser.o errors.o draw.o map_validator.o\
	map_validator_utils.o minimap.o keys.o run_cub3d.o\
	process_textures.o  raycast_textured.o movement.o movement2.o dda.o\
	raycast_textured_utils.o

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
