#include "cub3D.h"

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