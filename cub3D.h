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
# define WIN_W 1920
# define WIN_H 1080

typedef struct s_data
{
    int fd;
    char **wall; //north, east, south, west
    int floor[3]; //r, g, b
	unsigned int f_int;
    int sky[3]; //r, g, b
	unsigned int s_int;
    char **map;
	int mapsize[2]; //wid, hei
}               t_data;

typedef struct s_coords
{
	int x;
	int y;
	int angle;
}				t_coords;

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

typedef struct t_master
{
	t_data			data;
	t_mlxinfo		mlx;
	t_img			img;
	t_coords		coords;
}				t_master;

//draw.c
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

//errors.c
void free_data(t_data *data, char *msg);
void free_data_closed_fd(t_data *data, char *msg);
void free_char_arr(char **arr);
void exitmsg(char *msg);

//map_validator_utils.c
int     is_it_a_valid_element(char c);
int     player_check(char c);
int     check_first_or_last_row(char *row);
int     check_valid_surroundings(char **map, int i, int j);

//map_validator.c
void    texture_rights_checker(t_data *data);
void    map_element_checker(t_data *data);
void    check_surrounding_walls(t_data *data);
void 	map_validator(t_data *data);

//map_parser.c
void    map_parser(t_data *data);
int		rgb_to_int(int rgb[3]);

//arg_checker.c
int    get_fd(char *map);
int	is_it_whitespace(char c);
int are_there_any_whitespaces(char *str);
void    arg_checker(int ac, char **av);
void    validity_checker(int ac, char **av);

//main.c
int	main(int ac, char **av);

#endif