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
# define RAYS 320
# define BLOCKSIZE 320
# define FOV 80
# define GOD_MODE 1 //0 enables walking trough walls
# define WALLDIST 4


typedef struct s_raycast
{
	int		stripe_width;
	float	fov_rad;
	float	ray_angle;
	float	angle_between_rays;
	float	fisheye_angle;
	float	ray_y;
	float	ray_x;
	float	ray_len;
	int		wall_height;
	int		map_x;
	int		map_y;
	int		wall_top;
	int		wall_bottom;
	int		stripe_end;
	int		color;
	float	cos_angle;
	float	sin_angle;
	float	twopi;
	int		halfwin;
	int		y;
	int		x;
	int		i;
	int		*texture;
	int		side; // 0 on ns 1 on ew
	float	step;
	float	textpos;
	float	textx;
	float	texty;
	float	og_ray_x;
	float	og_ray_y;

}				t_raycast;

typedef struct s_dda
{
	int		map_x;
	int		map_y;
	float	ray_x_h;
	float	ray_y_h;
	float	ray_x_v;
	float	ray_y_v;
	float 	ray_len_horz;
	int		i;
	float 	y_offset;
	float	x_offset;
	int 	hit;
	float 	ray_len_vert;
	float 	nTan;
	float 	aTan;
}				t_dda;

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
	int *north;
	int *east;
	int *south;
	int *west;
}               t_data;

typedef struct s_player
{
	float x; //float??
	float y; //float??
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
	int				*data;
	char			*addr;
	int				bpp;
	int				llen;
	int				en;
	int				img_width;
	int				img_height;
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

//process_textures.c
int    *load_image(t_master *master, char *path, t_img *img);
void    process_textures(t_master *master);

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
void	get_player_coords(t_master *master);

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

void txt_raycaster(t_master *master, t_img *img);


#endif
