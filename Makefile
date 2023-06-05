NAME = cub3D

SRC = ./main.c arg_checker.c map_parser.c

OBJ = ./main.o arg_checker.o map_parser.o

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
