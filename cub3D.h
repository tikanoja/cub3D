#ifndef CUB3D_H
# define CUB3D_H
# include <unistd.h> //close, read, write
# include <stdlib.h> //malloc, free, exit
# include <stdio.h> //printf, perror
# include <string.h> //strerror
# include <math.h> //you already know
# include <mlx.h> //unfortunately you already know
# include <fcntl.h> //open
# include "./libft/libft.h"
# define WIN_W 640
# define WIN_H 400

typedef struct s_data
{
    int fd;
    int wall[4]; //north, east, south, west fd vai path????
    int floor[3]; //r, g, b
    int sky[3]; //r, g, b
    char **map;
}               t_data;

typedef struct s_bres
{
	int	x;
	int	y;
	int	dx;
	int	dy;
	int	stepy;
	int	stepx;
	int	error;
	int	e2;
}				t_bres;

typedef struct s_mlxinfo
{
	void			*mlx_ptr;
	void			*mlx_win;
	void			*currentimg;
}				t_mlxinfo;

typedef struct s_img
{
	void			*img;
	char			*addr;
	int				bpp;
	int				llen;
	int				en;
}				t_img;

//map_parser.c
void    map_parser(t_data *data);

//arg_checker.c
int    get_fd(char *map);
int	is_it_whitespace(char c);
int are_there_any_whitespaces(char *str);
void    arg_checker(int ac, char **av);
void    validity_checker(int ac, char **av);

//main.c
int	main(int ac, char **av);

#endif