NAME = cub3D

SRC = ./main.c arg_checker.c map_parser.c errors.c draw.c map_validator.c\
	map_validator_utils.c minimap.c raycast.c

OBJ = ./main.o arg_checker.o map_parser.o errors.o draw.o map_validator.o\
	map_validator_utils.o minimap.o raycast.o

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
