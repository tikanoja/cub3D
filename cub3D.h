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
# define WIN_W 1280
# define WIN_H 960
# define RAYS 90
# define BLOCKSIZE 320
# define FOV 90

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

typedef struct s_player
{
	int x;
	int y;
	int endx;
	int endy;
	double angle;
}				t_player;

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

typedef struct s_minimap_coords
{
	int x;
	int y;
	int j;
	int i;
	int block;
}				t_minimap_coords;

typedef struct s_keylog
{
	int W;
	int A;
	int S;
	int D;
	int UP;
	int LEFT;
	int DOWN;
	int RIGHT;
}				t_keylog;

typedef struct t_master
{
	t_data			data;
	t_mlxinfo		mlx;
	t_img			img;
	t_player		player;
	t_minimap_coords minimap;
	t_keylog		keylog;
}				t_master;

//run_cub3d.c
int		update_game(t_master *master);
void	run_cub3d(t_master *master);
void	init_cub3d(t_master master);

//keys.c
int		key_press(int keycode, t_master *master);
int		key_release(int keycode, t_master *master);

//draw.c
void	drawl(t_img *img, t_player *coords, int color);
void	draw_background(t_master *master, t_img *img);
void	draw_block(t_master *master, t_img *img, t_minimap_coords coords);
void	my_mlx_pixel_put(t_img *img, int x, int y, int color);

//raycast.c
int 	count_max_ray(t_master *master);
void 	raycaster(t_master *master, t_img *img);

//minimap.c
void	init_minimap_coords(t_minimap_coords *coords, t_master *master);
void	draw_minimap(t_master *master, t_img *img);

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
int	freeandexit(t_master *master);
void	init_cub3d(t_master master);
int	main(int ac, char **av);

#endif