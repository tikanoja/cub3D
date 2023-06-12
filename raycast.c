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

// void		wall_analyzer(float ray_y, float ray_x, t_master *master, int *color)
// {
// 	if (master->player.angle >= M_PI && master->player.angle < 2 * M_PI) // looking up
// 	{
// 		if ((int)ceilf(ray_y) % master->minimap.block == 0) // north
// 		{
// 			(*color) = 0x1C2951;
// 		}
// 		else if ((int)floorf(ray_x) % master->minimap.block == 0 && ray_x > master->player.x) // east
// 		{
// 			(*color) = 0x2E8B57;
// 		}
// 		else if ((int)ceilf(ray_x) % master->minimap.block == 0 && ray_x < master->player.x) //west
// 		{
// 			(*color) = 0x3CB371;
// 		}
// 	}
// 	if (master->player.angle >= 0 && master->player.angle < M_PI) // looking down
// 	{
// 		if ((int)floorf(ray_y) % master->minimap.block == 0) // south
// 			(*color) = 0xFD673A;
// 		else if ((int)floorf(ray_x) % master->minimap.block == 0&& ray_x > master->player.x) // east
// 		{
// 			(*color) = 0x2E8B57;
// 		}
// 		else if ((int)ceilf(ray_x) % master->minimap.block == 0&& ray_x < master->player.x) //west
// 		{
// 			(*color) = 0x3CB371;
// 		}
// 	}
// }

void		wall_analyzerv2(float ray_y, float ray_x, float ray_angle, t_master *master, int *color)
{
	if (ray_angle >= M_PI && ray_angle <= 2 * M_PI) // looking up
	{
		if ((int)ceilf(ray_y) % master->minimap.block == 0) // north
			(*color) = 0x1C2951;
		else if ((int)floorf(ray_x) % master->minimap.block == 0 && ray_x > master->player.x) // east
			(*color) = 0x2E8B57;
		else if ((int)ceilf(ray_x) % master->minimap.block == 0 && ray_x < master->player.x) //west
			(*color) = 0x3CB371;
	}
	else if (ray_angle >= 0 && ray_angle < M_PI) // looking down
	{
		if ((int)floorf(ray_y) % master->minimap.block == 0) // south
			(*color) = 0xFD673A;
		else if ((int)floorf(ray_x) % master->minimap.block == 0 && ray_x > master->player.x) // east
			(*color) = 0x2E8B57;
		else if ((int)ceilf(ray_x) % master->minimap.block == 0 && ray_x < master->player.x) //west
			(*color) = 0x3CB371;
	}
}

void raycaster(t_master *master, t_img *img)
{
	int x = 0;
	int i = 0;
	int y;

	int stripe_width = WIN_W / RAYS;
	float fov_rad = FOV * (M_PI / 180);
	float ray_angle = master->player.angle - (fov_rad / 2);
	float angle_between_rays = fov_rad / RAYS;
	int color;
	// float max_wall_distance = count_max_ray(master);/* Calculate the maximum distance from the player to the farthest wall */;
	while (i < RAYS)
	{
		color = 0x000000;
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
				break;
			ray_len++;
		}
		float wall_distance = sqrt(pow((ray_x - master->player.x), 2) + pow((ray_y - master->player.y), 2));
		// float wall_distance = ray_len * cos(ray_angle - master->player.angle);
		//float scaled_wall_distance = wall_distance / max_wall_distance; // Calculate the ratio of actual distance to maximum distance
		printf("rayx %f ray y %f player angle %f ray angle %f block %d player x %d\n", ray_x, ray_y, master->player.angle, ray_angle, master->minimap.block, master->player.x);

		//fix fisheye
		// float fisheye_angle = ray_angle - master->player.angle;
		// if (fisheye_angle < 0)
		// 	fisheye_angle = fisheye_angle + 2 * M_PI;
		// if (fisheye_angle > 2 * M_PI)
		// 	fisheye_angle = fisheye_angle - 2 * M_PI;
		// wall_distance = wall_distance * cos(fisheye_angle);

		int wall_height = 10 * BLOCKSIZE / wall_distance; // Scale the wall height based on the distance ratio
		int wall_top = WIN_H / 2 - wall_height / 2;
		int wall_bottom = WIN_H / 2 + wall_height / 2;
		y = wall_top;
		int stripe_end = x + stripe_width;
		// wall_analyzer(ray_y, ray_x, master, &color);
		wall_analyzerv2(ray_y, ray_x, ray_angle, master, &color);
		while(x < stripe_end && x < WIN_W && y < WIN_H)
		{
			y = wall_top;
			while (y < wall_bottom)
			{
				if (x > 0 && y > 0 && x < WIN_W && y < WIN_H)
					my_mlx_pixel_put(img, x, y, color);
				y++;
			}
			x++;
		}
		// x = x + stripe_width;

		ray_angle += angle_between_rays;
		i++;
	}
}