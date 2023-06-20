/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 10:05:27 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/06/20 10:05:29 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_minimap_coords(t_minimap_coords *coords, t_master *master)
{
	coords->x = WIN_W / master->data.mapsize[0] / 2;
	coords->y = WIN_H / master->data.mapsize[1] / 2;
	if (coords->x <= coords->y)
		coords->block = coords->x;
	else
		coords->block = coords->y;
	coords->x = 0;
	coords->y = 0;
	coords->i = 0;
	coords->j = 0;
}
void	get_angle(t_master *master, char c)
{
	if (c == 'S')
		master->player.angle = M_PI / 2;
	else if (c == 'E')
		master->player.angle = 0.0;
	else if (c == 'N')
		master->player.angle = 3 * M_PI / 2;
	else if (c == 'W')
		master->player.angle = M_PI;
}
void    get_player_coords(t_master *master)
{
	char *poc = "NEWS";
	int i;
	int flag;

	flag = 0;
	i = 0;
	master->player.y = 0;
	while(master->data.map[(int)master->player.y] && flag == 0)
	{
		master->player.x = 0;
		while(master->data.map[(int)master->player.y][(int)master->player.x] && flag == 0)
		{
			while(poc[i] && flag == 0)
			{
				if (master->data.map[(int)master->player.y][(int)master->player.x] == poc[i])
					flag = 1;
				i++;
			}
			i = 0;
			master->player.x++;
		}
		master->player.y++;
	}
	get_angle(master, master->data.map[(int)master->player.y - 1][(int)master->player.x - 1]);
	master->player.y = ((master->player.y - 1) * master->minimap.block) + master->minimap.block / 2;
	master->player.x = ((master->player.x - 1) * master->minimap.block) + master->minimap.block / 2;
}


// void draw_direction(t_master *master, t_img *img)
// {
// 	float	ray_angle;
// 	float	angle_between_rays;
// 	float 	fov_rad;
// 	int		map_x;
// 	int		map_y;
// 	float	ray_x;
// 	float	ray_y;
// 	int		ray_len; //actually pixel but who cares
// 	int		i;

// 	i = 0;
// 	fov_rad = FOV * (M_PI / 180);
// 	ray_angle = master->player.angle - (fov_rad / 2);
// 	angle_between_rays = fov_rad / RAYS;
// 	while(i < RAYS)
// 	{
// 		ray_len = 1;
// 		ray_x = (int)master->player.x;
// 		ray_y = (int)master->player.y;
// 		while (ray_x >= 0 && ray_x <= WIN_W && ray_y >= 0 && ray_y <= WIN_H)
// 		{
// 			ray_x = master->player.x + cos(ray_angle) * ray_len;
// 			ray_y = master->player.y + sin(ray_angle) * ray_len;
// 			map_x = ray_x / master->minimap.block;
// 			map_y = ray_y / master->minimap.block;
// 			if (map_x >= 0 && map_x < master->data.mapsize[0] && map_y >= 0 && \
// 			map_y < master->data.mapsize[1] && \
// 			master->data.map[map_y][map_x] == '1')
// 				break;
// 			ray_len++;
// 		}
// 		master->player.endx = master->player.x + cos(ray_angle) * ray_len;
// 		master->player.endy = master->player.y + sin(ray_angle) * ray_len;
// 		drawl(img, &master->player, 0xFF0000);
// 		ray_angle += angle_between_rays;
// 		i++;
// 	}
// }

void draw_direction(t_master *master, t_img *img)
{
	float	ray_angle;
	double	angle_between_rays;
	float 	fov_rad;
	int		map_x;
	int		map_y;
	float	ray_x_h;
	float	ray_y_h;
	float	ray_x_v;
	float	ray_y_v;
	float ray_len_horz;
	int		i;
	float 	y_offset;
	float	x_offset;
	int 	hit;
	float ray_len_vert;
	float nTan;
	float aTan;

	i = 0;
	fov_rad = FOV * (M_PI / 180);
	ray_angle = master->player.angle - (fov_rad / 2);
	if (ray_angle < 0)
		ray_angle = 2 * M_PI + ray_angle;
	angle_between_rays = fov_rad / RAYS;
	while(i < RAYS)
	{
		hit = 0;
		//HORIZONTAL
		aTan = -1 / tan(ray_angle);
		if (ray_angle > M_PI) // looking up
		{
			ray_y_h = master->player.y - ((int)master->player.y % master->minimap.block) - 1.0001;
			ray_x_h = (master->player.y - ray_y_h) * aTan + master->player.x;
			y_offset = -master->minimap.block;
			x_offset = -y_offset * aTan;
		}
		if (ray_angle < M_PI) // looking down
		{
			ray_y_h = master->player.y - ((int)master->player.y % master->minimap.block) + master->minimap.block;
			ray_x_h = (master->player.y - ray_y_h) * aTan + master->player.x;
			y_offset = master->minimap.block;
			x_offset = -y_offset * aTan;
		}
		if (ray_angle == (float)M_PI || ray_angle == 0) // looking directly down
		{
			ray_x_h = master->player.x;
			ray_y_h = master->player.y;
			hit = 1;
		}

		map_x = 0;
		map_y = 0;
		while (!hit && ray_x_h >= 0 && ray_y_h >= 0)
		{
			map_x = (int)ray_x_h / master->minimap.block;
			map_y = (int)ray_y_h / master->minimap.block;
			if (map_x >= 0 && map_x < master->data.mapsize[0] && map_y >= 0 && map_y < master->data.mapsize[1] && master->data.map[map_y][map_x] == '1')
				hit = 1;
			else
			{
				ray_x_h += x_offset;
				ray_y_h += y_offset;
			}
			if (ray_x_h > WIN_W || ray_y_h > WIN_H)
				break;
		}
		if (ray_x_h > WIN_W || ray_x_h < 0)
			ray_x_h = master->player.x;
		if (ray_y_h > WIN_H || ray_y_h < 0)
			ray_y_h = master->player.y;
		if (ray_y_h == master->player.y || ray_x_h == master->player.x)
			ray_len_horz = 2147483647;
		else
			ray_len_horz = sqrt(pow(ray_y_h - master->player.y, 2) + pow(ray_x_h - master->player.x, 2));


		hit = 0;
		//VERTICAL
		nTan = -tan(ray_angle);
		if (ray_angle > M_PI / 2 && ray_angle < 3 * M_PI / 2) // looking left
		{
			ray_x_v = master->player.x - ((int)master->player.x % master->minimap.block) - 1.0001;
			ray_y_v = (master->player.x - ray_x_v) * nTan + master->player.y;
			x_offset = -master->minimap.block;
			y_offset = -x_offset * nTan;
		}
		if (ray_angle < M_PI / 2 || ray_angle > 3 * M_PI / 2) // looking right
		{
			ray_x_v = master->player.x - ((int)master->player.x % master->minimap.block) + master->minimap.block;
			ray_y_v = (master->player.x - ray_x_v) * nTan + master->player.y;
			x_offset = master->minimap.block;
			y_offset = -x_offset * nTan;
		}
		if (ray_angle == 0 || ray_angle == (float)M_PI) // looking directly up
		{
			ray_x_v = master->player.x;
			ray_y_v = master->player.y;
			hit = 1;
		}

		map_x = 0;
		map_y = 0;
		while (!hit && ray_x_v >= 0 && ray_y_v >= 0)
		{
			map_x = (int)ray_x_v / master->minimap.block;
			map_y = (int)ray_y_v / master->minimap.block;
			if (map_x >= 0 && map_x < master->data.mapsize[0] && map_y >= 0 && map_y < master->data.mapsize[1] && master->data.map[map_y][map_x] == '1')
				hit = 1;
			else
			{
				ray_x_v += x_offset;
				ray_y_v += y_offset;
			}
			if (ray_x_v > WIN_W || ray_y_v > WIN_H)
				break;
		}
		if (ray_x_v > WIN_W || ray_x_v < 0)
			ray_x_v = master->player.x;
		if (ray_y_v > WIN_H || ray_y_v < 0)
			ray_y_v = master->player.y;
		if (ray_y_v == master->player.y || ray_x_v == master->player.x)
			ray_len_vert = 2147483647;
		else
			ray_len_vert = sqrt(pow(ray_x_v - master->player.x, 2) + pow(ray_y_v - master->player.y, 2));
	
		if (ray_len_horz < ray_len_vert)
		{
			master->player.endy = (int)ray_y_h;
			master->player.endx = (int)ray_x_h;
		}
		else
		{
			master->player.endy = (int)ray_y_v;
			master->player.endx = (int)ray_x_v;
		}
		// if (ray_angle == 0 || ray_angle == M_PI)
		// {
		// 	master->player.endx = ray_x_v;
		// 	master->player.endy = ray_y_v;
		// }
		// if (ray_angle == 2 * M_PI || ray_angle == 3 * M_PI / 2)
		// {
		// 	master->player.endx = ray_x_h;
		// 	master->player.endy = ray_y_h;
		// }
		drawl(img, &master->player, 0xFF0000);
		ray_angle += angle_between_rays;
		if (ray_angle > 2 * M_PI)
			ray_angle = ray_angle - 2 * M_PI;
		i++;
	}
}



void    draw_player(t_master *master, t_img *img)
{  
	int start_y;
	int end_y;
	int start_x;
	int end_x;
	static int flag;

	if (flag == 0)
	{
		get_player_coords(master);
		flag = 1;
	}
	start_y = master->player.y - 2;
	end_y = start_y + 5;
	start_x = master->player.x - 2;
	end_x = start_x + 5;
	while(start_y <= end_y)
	{
		while(start_x <= end_x)
		{
			my_mlx_pixel_put(img, start_x, start_y, 0x000000);	
			start_x++;
		}
		start_x = end_x - 5;
		start_y++;
	}
	draw_direction(master, img); //piirtaa vaa pien nuoli
	//raycaster(master, img);
}

void	draw_minimap(t_master *master, t_img *img)
{
	t_minimap_coords coords;
	int og_x;

	init_minimap_coords(&coords, master);
	og_x = coords.x;
	while(master->data.map[coords.j])
	{
		while (master->data.map[coords.j][coords.i])
		{
			if (master->data.map[coords.j][coords.i] != 32)
				draw_block(master, img, coords);
			coords.i++;
			coords.x = coords.i * coords.block;
		}
		coords.i = 0;
		coords.x = og_x;
		coords.j++;
		coords.y = coords.j * coords.block;
	}
	master->minimap = coords;
	draw_player(master, img);
}
