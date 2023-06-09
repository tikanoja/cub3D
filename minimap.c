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
	if (c == 'N')
		master->player.angle = 0.0;
	else if (c == 'E')
		master->player.angle = 3 * M_PI / 2;
	else if (c == 'S')
		master->player.angle = M_PI;
	else if (c == 'W')
		master->player.angle = M_PI / 2;
	printf("player angle %f and char is %c\n", master->player.angle, c);


}
void    get_player_coords(t_master *master)
{
	char *poc = "NEWS";
	int i;
	int flag;

	flag = 0;
	i = 0;
	master->player.y = 0;
	while(master->data.map[master->player.y] && flag == 0)
	{
		master->player.x = 0;
		while(master->data.map[master->player.y][master->player.x] && flag == 0)
		{
			while(poc[i] && flag == 0)
			{
				if (master->data.map[master->player.y][master->player.x] == poc[i])
					flag = 1;
				i++;
			}
			i = 0;
			master->player.x++;
		}
		master->player.y++;
	}
	printf("y is %d and x is %d\n", master->player.y , master->player.x);
	get_angle(master, master->data.map[master->player.y - 1][master->player.x - 1]);
	master->player.y = ((master->player.y - 1) * master->minimap.block) + master->minimap.block / 2;
	master->player.x = ((master->player.x - 1) * master->minimap.block) + master->minimap.block / 2;
}
int count_max_ray(t_master *master)
{
	int max_ray;
	int rays = 90;
	float ray_angle = master->player.angle - M_PI / 4;
	int i = 0;
	while (i < rays)
	{
		int ray_len = 1;
		float ray_x = master->player.x;
		float ray_y = master->player.y;
		while (ray_x >= 0 && ray_x <= WIN_W && ray_y >= 0 && ray_y <= WIN_H)
		{
			ray_x = master->player.x + cos(ray_angle) * ray_len;
			ray_y = master->player.y + sin(ray_angle) * ray_len;
			int map_x = ray_x / master->minimap.block;
			int map_y = ray_y / master->minimap.block;

			if (map_x >= 0 && map_x < master->data.mapsize[0] && map_y >= 0 && map_y < master->data.mapsize[1] && master->data.map[map_y][map_x] == '1')
			{
				break;
			}
			ray_len++;
		}
		if (ray_len >= max_ray)
			max_ray = ray_len;
		i++;
	}
	return (max_ray);
}
void raycaster(t_master *master, t_img *img)
{
	int rays = 90;
	float ray_angle = master->player.angle - M_PI / 4;
	int x = 0;
	int i = 0;
	int y;

	int stripe_width = WIN_W / rays;
	float max_wall_distance = count_max_ray(master);/* Calculate the maximum distance from the player to the farthest wall */;
	while (i < rays)
	{
		int ray_len = 1;
		float ray_x = master->player.x;
		float ray_y = master->player.y;
		while (ray_x >= 0 && ray_x <= WIN_W && ray_y >= 0 && ray_y <= WIN_H)
		{
			ray_x = master->player.x + cos(ray_angle) * ray_len;
			ray_y = master->player.y + sin(ray_angle) * ray_len;
			int map_x = ray_x / master->minimap.block;
			int map_y = ray_y / master->minimap.block;

			if (map_x >= 0 && map_x < master->data.mapsize[0] && map_y >= 0 && map_y < master->data.mapsize[1] && master->data.map[map_y][map_x] == '1')
			{
				break;
			}
			ray_len++;
		}
		// float wall_distance = ray_len * cos(ray_angle - master->player.angle);
		// int wall_height = (WIN_H / wall_distance) * 5;
		// int wall_top = WIN_H / 2 - wall_height / 2;
		// int wall_bottom = WIN_H / 2 + wall_height / 2;
		const int MAX_WALL_HEIGHT = WIN_H;/* Define the maximum desired wall height */;

		float wall_distance = ray_len * cos(ray_angle - master->player.angle);
		float scaled_wall_distance = wall_distance / max_wall_distance; // Calculate the ratio of actual distance to maximum distance

		int wall_height = MAX_WALL_HEIGHT * (1.0f / scaled_wall_distance); // Scale the wall height based on the distance ratio

		int wall_top = WIN_H / 2 - wall_height / 2;
		int wall_bottom = WIN_H / 2 + wall_height / 2;
		y = wall_top;
		while(x < stripe_width && x > 0 && y > 0 && x < WIN_W && y < WIN_H)
		{
			y = wall_top;
			while (y < wall_bottom)
			{
				int color;
				color = 0x435BFF;
				if (x > 0 && y > 0 && x < WIN_W && y < WIN_H)
					my_mlx_pixel_put(img, x, y, color);
				y++;
			}
			x++;
		}
		x = stripe_width;
		stripe_width = stripe_width + stripe_width;

		ray_angle += (M_PI / 2) / rays;
		i++;
	}
}

 void draw_direction(t_master *master, t_img *img)
{
	int		rays;
	float	ray_angle;
	int		map_x;
	int		map_y;
	float	ray_x;
	float	ray_y;
	int		ray_len; //actually pixel but who cares
	int		i;

	i = 0;
	rays = 365; //how many rays we want should this be a #define
	printf("player angle %f\n", master->player.angle);
	ray_angle = master->player.angle - M_PI / 4;
	while(i < rays)
	{
		ray_len = 1;
		ray_x = master->player.x;
		ray_y = master->player.y;
		while (ray_x >= 0 && ray_x <= WIN_W && ray_y >= 0 && ray_y <= WIN_H)
		{
			ray_x = master->player.x + cos(ray_angle) * ray_len;
			ray_y = master->player.y + sin(ray_angle) * ray_len;
			map_x = ray_x / master->minimap.block;
			map_y = ray_y / master->minimap.block;
			if (map_x >= 0 && map_x < master->data.mapsize[0] && map_y >= 0 && \
			map_y < master->data.mapsize[1] && \
			master->data.map[map_y][map_x] == '1')
				break;
			ray_len++;
		}
		master->player.endx = master->player.x + cos(ray_angle) * ray_len;
		master->player.endy = master->player.y + sin(ray_angle) * ray_len;
		drawl(img, &master->player, 0xFF0000);
		ray_angle += (M_PI / 2) / rays;
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
	draw_direction(master, img);
	raycaster(master, img);
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