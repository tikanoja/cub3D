/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3D.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:12:00 by jaurasma          #+#    #+#             */
/*   Updated: 2023/07/12 18:45:06 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H
# include <unistd.h> //close, read, write
# include <stdlib.h> //malloc, free, exit
# include <stdio.h> //printf, perror
# include <math.h> //math library
# include <mlx.h> //minilibx library
# include <fcntl.h> //open
# include "./libft/libft.h"
# define WIN_W 960
# define WIN_H 720
# define RAYS 480
# define FOV 70
# define MOVEMENT_SPEED 12
# define GOD_MODE 1 //0 enables walking trough walls
# define WALLDIST 2
# define MINIMAP 1 //0 turns off minimap

typedef struct s_flood
{
	int	start_row;
	int	start_col;
	int	i;
	int	j;
	int	**visited;
}				t_flood;

typedef struct s_texture
{
	int	*array;
	int	width;
	int	height;
}				t_texture;

typedef struct s_update
{
	float	mspeed;
	int		updateflag;
	float	new_x;
	float	new_y;
	int		sign_x;
	int		sign_y;
}				t_update;

typedef struct s_raycast
{
	int			stripe_width;
	float		fov_rad;
	float		ray_angle;
	float		angle_between_rays;
	float		fisheye_angle;
	float		ray_y;
	float		ray_x;
	float		ray_len;
	int			wall_height;
	int			map_x;
	int			map_y;
	int			wall_top;
	int			wall_bottom;
	int			stripe_end;
	int			color;
	float		cos_angle;
	float		sin_angle;
	float		twopi;
	int			halfwin;
	int			y;
	int			x;
	int			i;
	t_texture	*texture;
	int			side;
	float		step;
	float		textpos;
	float		textx;
	float		texty;
	float		og_ray_x;
	float		og_ray_y;
	float		mod_step;
	int			txtindex;
	int			txtarrsize;
}				t_raycast;

typedef struct s_dda
{
	int		map_x;
	int		map_y;
	float	ray_x_h;
	float	ray_y_h;
	float	ray_x_v;
	float	ray_y_v;
	float	ray_len_horz;
	int		i;
	float	y_offset;
	float	x_offset;
	int		hit;
	float	ray_len_vert;
	float	ntan;
	float	atan;
}				t_dda;

typedef struct s_data
{
	int				fd;
	char			**wall;
	int				floor[3];
	unsigned int	f_int;
	int				sky[3];
	unsigned int	s_int;
	char			**map;
	int				mapsize[2];
	t_texture		north;
	t_texture		east;
	t_texture		south;
	t_texture		west;
}					t_data;

typedef struct s_player
{
	float	x;
	float	y;
	int		endx;
	int		endy;
	double	angle;
}				t_player;

typedef struct s_block
{
	int	end_x;
	int	end_y;
	int	color;
	int	og_x;
	int	og_y;
}				t_block;

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
	int	x;
	int	y;
	int	j;
	int	i;
	int	block;
}				t_minimap_coords;

typedef struct s_keylog
{
	int	w;
	int	a;
	int	s;
	int	d;
	int	up;
	int	left;
	int	down;
	int	right;
}				t_keylog;

typedef struct t_master
{
	t_data				data;
	t_mlxinfo			mlx;
	t_img				img;
	t_player			player;
	t_minimap_coords	minimap;
	t_keylog			keylog;
}				t_master;

//raycast_textured_utils.c
int			dda_arr_check(t_dda *d, t_master *m);
void		wall_handler(t_raycast *rc, t_dda *dda, t_master *m);
void		wall_scaler(t_raycast *rc, t_master *m);

//raycast_textured.c
void		init_raycast(t_raycast *raycast, t_master *m);
void		init_draw_stripe(t_raycast *rc);
void		draw_stripe(t_raycast *rc, t_img *img);
void		txt_raycaster(t_master *m, t_img *img);

//dda.c
void		dda_horizontal(t_dda *dda, t_raycast *rc, t_master *m);
void		dda_vertical(t_dda *dda, t_raycast *rc, t_master *m);
void		dda_loop_horizontal(t_dda *d, t_master *m);
void		dda_loop_vertical(t_dda *d, t_master *m);
void		dda(t_raycast *rc, t_master *m);

//movement.c
void		strafe_left(t_update *up, t_master *master);
void		strafe_right(t_update *up, t_master *master);
void		rotate_left(t_update *up, t_master *master);
void		rotate_right(t_update *up, t_master *master);

//movement2.c
int			window_check(t_update *up);
void		forward(t_update *up, t_master *master);
void		backward(t_update *up, t_master *master);

//process_textures.c
void		free_textures(t_master *master, int flag);
t_texture	load_image(t_master *master, char *path, t_img *img);
void		process_textures(t_master *master);

//update_game.c
int			is_wall(float x, float y, t_master *master, float buffer_distance);
void		init_update(t_update *up, t_master *master);
int			update_game(t_master *master);

//run_cub3d.c
void		run_cub3d(t_master *master);
void		init_rc(t_master *master);
void		init_cub3d(t_master master);

//keys.c
int			key_press(int keycode, t_master *master);
int			key_release(int keycode, t_master *master);

//draw.c
void		drawl(t_img *img, t_player *coords, int color);
void		draw_background(t_master *master, t_img *img);
void		draw_block(t_master *master, t_img *img, t_minimap_coords coords);
void		my_mlx_pixel_put(t_img *img, int x, int y, int color);

//minimap_utils.c
void		init_minimap_coords(t_minimap_coords *coords, t_master *master);
void		init_get_player_coords(int *flag, int *i, t_master *m);
void		init_draw_player(int *start_y, int *start_x, t_master *master);

//minimap.c
void		get_angle(t_master *master, char c);
void		get_player_coords(t_master *m);
void		draw_direction_arrow(t_master *master, t_img *img);
void		draw_player(t_master *master, t_img *img);
void		draw_minimap(t_master *master, t_img *img);

//errors.c
int			exit_gracefully(t_master *master);
void		free_data(t_data *data, char *msg);
void		free_data_closed_fd(t_data *data, char *msg);
void		free_char_arr(char **arr);
void		exitmsg(char *msg);

//map_validator_utils.c
int			is_it_a_valid_element(char c);
int			player_check(char c);
int			check_first_or_last_row(char *row);
int			check_valid_surroundings(char **map, int i, int j);

//map_validator.c
void		texture_rights_checker(t_data *data);
void		map_element_checker(t_data *data);
void		check_surrounding_walls(t_data *data);
void		map_validator(t_data *data);

//flood.c
int			is_map_connected(t_data *data);
void		flood_fill(t_data *data, int row, int col, t_flood *f);

//map_parser_utlis5.c
void		fill_wall_elements(char **wall, char *save, t_data *data, \
			char *line);
int			free_save_ret_happened(char *save, int happened, \
			int save_pointer_index);

//map_parser_utils4.c
void		init_map_parser(int *flag, char **line, char **map);
int			rgb_to_int(int rgb[3]);
void		check_double_map(t_data *data, char *line);
void		init_parsing(t_data *data);
int			check_empty_line(char *line);

//map_parser_utils3.c
void		trim_and_split_color(t_data *data, char *color, int flag);
int			check_for_color(t_data *data, char *line);
int			check_if_filled(t_data *data, int hap);
int			fill_to_struct(t_data *data, char *line);

//map_parser_utils2.c
void		split_colors(char **temp, int *data, t_data *datastruct);
void		free_color_args(char **temp, t_data *data);
int			check_for_num(char c);
int			check_for_correct_number(char *num);
void		check_for_color_argument(char **temp, t_data *data);

//map_parser_utils.c
int			change_happened(int *happened);
char		*trim_direction(char *direction);
int			dupcheck(char *wall, char *line, t_data *data);
int			check_for_direction(t_data *data, char *line);

//map_parser.c
void		map_parser(t_data *data);
int			rgb_to_int(int rgb[3]);

//arg_checker.c
int			get_fd(char *map);
int			is_it_whitespace(char c);
int			are_there_any_whitespaces(char *str);
void		arg_checker(int ac, char **av);

//main.c
int			freeandexit(t_master *master);
void		init_cub3d(t_master master);
int			main(int ac, char **av);

#endif
