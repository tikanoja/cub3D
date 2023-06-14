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
	float fisheye_angle;
	float ray_y;
	float ray_x;
	float ray_len;
	int wall_height;
	int map_x;
	int map_y;
	int wall_top;
	int wall_bottom;
	int stripe_end;


	int color;
	float increment;

	if (ray_angle < 0)
		ray_angle = 2 * M_PI + ray_angle;
	printf("/n/n/n/n new rays/n");
	// float max_wall_distance = count_max_ray(master);/* Calculate the maximum distance from the player to the farthest wall */;
	while (i < RAYS)
	{
		increment = 0.01;
		color = 0x000000;
		ray_len = 0.05;
		ray_x = master->player.x;
		ray_y = master->player.y;
		while (ray_x >= 0 && ray_x <= WIN_W && ray_y >= 0 && ray_y <= WIN_H)
		{
			ray_x = master->player.x + cos(ray_angle) * ray_len;
			ray_y = master->player.y + sin(ray_angle) * ray_len;
			map_x = ray_x / master->minimap.block;
			map_y = ray_y / master->minimap.block;
			if (map_x >= 0 && map_x < master->data.mapsize[0] && map_y >= 0 && map_y < master->data.mapsize[1] && master->data.map[map_y][map_x] == '1')
				break;
			ray_len += 0.05;
		}
		
		//fix fisheye
		fisheye_angle = master->player.angle - ray_angle;
		if (fisheye_angle < 0)
			fisheye_angle = 2 * M_PI + fisheye_angle;
		if (fisheye_angle > 2 * M_PI)
			fisheye_angle = fisheye_angle - 2 * M_PI;
		ray_len = ray_len * cos(fisheye_angle);

		// printf("wall dist %f\n", wall_distance);
		// printf("wall dist: %f\n", wall_distance);

		//these lines make it bretty psychedeilg
		// float perpendicular_distance = ray_len * cos(ray_angle - master->player.angle);
		// int wall_height = BLOCKSIZE / perpendicular_distance * 40;

		wall_height = 5000 / ray_len; // Scale the wall height based on the distance ratio
			printf("ray %d wall height %d\n",i,  wall_height);
		wall_top = WIN_H / 2 - wall_height / 2;
		wall_bottom = WIN_H / 2 + wall_height / 2;
		y = wall_top;
		stripe_end = x + stripe_width;

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

		ray_angle += angle_between_rays;
		if (ray_angle > 2 * M_PI)
			ray_angle = ray_angle - 2 * M_PI;
		i++;
	}
}