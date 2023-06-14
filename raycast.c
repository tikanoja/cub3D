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

void		wall_analyzerv2(float ray_y, float ray_x, float ray_angle, t_master *master, int *color, t_raycast *raycast)
{
	if (ray_angle >= M_PI && ray_angle <= 2 * M_PI) // looking up
	{
		if ((int)ceilf(ray_y) % master->minimap.block == 0 && master->data.map[(int)(raycast->ray_y + master->minimap.block) / master->minimap.block][(int)raycast->ray_x / master->minimap.block] == '0') // north
			(*color) = 0x1C2951;
		else if ((int)floorf(ray_x) % master->minimap.block == 0 && ray_x > master->player.x) // east
			(*color) = 0x2E8B57;
		else if ((int)ceilf(ray_x) % master->minimap.block == 0 && ray_x < master->player.x) //west
			(*color) = 0x3CB371;
	}
	else if (ray_angle >= 0 && ray_angle < M_PI) // looking down
	{
		if ((int)floorf(ray_y) % master->minimap.block == 0 && master->data.map[(int)(raycast->ray_y - master->minimap.block) / master->minimap.block][(int)raycast->ray_x / master->minimap.block] == '0') // south
			(*color) = 0xFD673A;
		else if ((int)floorf(ray_x) % master->minimap.block == 0 && ray_x > master->player.x) // east
			(*color) = 0x2E8B57;
		else if ((int)ceilf(ray_x) % master->minimap.block == 0 && ray_x < master->player.x) //west
			(*color) = 0x3CB371;
	}
}

void	init_raycast(t_raycast *raycast, t_master *master)
{
	raycast->stripe_width = WIN_W / RAYS;
	raycast->fov_rad = FOV * (M_PI / 180);
	raycast->ray_angle = master->player.angle - (raycast->fov_rad / 2);
	raycast->angle_between_rays = raycast->fov_rad / RAYS;
	raycast->ray_x = master->player.x;
	raycast->ray_y = master->player.y;
	raycast->twopi = 2 * M_PI;
	raycast->halfwin = WIN_H / 2;
}


void raycaster_untextured(t_master *master, t_img *img) //untextured
{
	int x = 0;
	int i = 0;
	int y;
	t_raycast raycast;

	init_raycast(&raycast, master);

	if (raycast.ray_angle < 0)
		raycast.ray_angle = raycast.twopi + raycast.ray_angle;
	// float max_wall_distance = count_max_ray(master);/* Calculate the maximum distance from the player to the farthest wall */;
	while (i < RAYS)
	{
		raycast.color = 0x000000;
		raycast.ray_len = 0.05;
		
		raycast.cos_angle = cos(raycast.ray_angle);
		raycast.sin_angle = sin(raycast.ray_angle);
		while (raycast.ray_x >= 0 && raycast.ray_x <= WIN_W && raycast.ray_y >= 0 && raycast.ray_y <= WIN_H)
		{
			raycast.ray_x = master->player.x + raycast.cos_angle * raycast.ray_len;
			raycast.ray_y = master->player.y + raycast.sin_angle * raycast.ray_len;
			raycast.map_x = raycast.ray_x / master->minimap.block;
			raycast.map_y = raycast.ray_y / master->minimap.block;
			if (raycast.map_x >= 0 && raycast.map_x < master->data.mapsize[0] && raycast.map_y >= 0 && raycast.map_y < master->data.mapsize[1] && master->data.map[raycast.map_y][raycast.map_x] == '1')
				break;
			raycast.ray_len += 0.05;
		}

		//fix fisheye
		raycast.fisheye_angle = master->player.angle - raycast.ray_angle;
		if (raycast.fisheye_angle < 0)
			raycast.fisheye_angle = raycast.twopi + raycast.fisheye_angle;
		if (raycast.fisheye_angle > raycast.twopi)
			raycast.fisheye_angle = raycast.fisheye_angle - raycast.twopi;
		raycast.ray_len = raycast.ray_len * cos(raycast.fisheye_angle);

		raycast.wall_height = 5000 / raycast.ray_len; // give a nice constant for wall scaling
		raycast.wall_top = raycast.halfwin - raycast.wall_height / 2;
		raycast.wall_bottom = raycast.halfwin + raycast.wall_height / 2;
		y = raycast.wall_top;
		raycast.stripe_end = x + raycast.stripe_width;

		wall_analyzerv2(raycast.ray_y, raycast.ray_x, raycast.ray_angle, master, &raycast.color, &raycast);
		printf("ray x: %f ray_y: %f color: %d wall hei %d\n", raycast.ray_x, raycast.ray_y, raycast.color, raycast.wall_height);
		while(x < raycast.stripe_end && x < WIN_W && y < WIN_H)
		{
			y = raycast.wall_top;
			while (y < raycast.wall_bottom)
			{
				if (x > 0 && y > 0 && x < WIN_W && y < WIN_H)
					my_mlx_pixel_put(img, x, y, raycast.color);
				y++;
			}
			x++;
		}
		raycast.ray_angle += raycast.angle_between_rays;
		if (raycast.ray_angle > raycast.twopi)
			raycast.ray_angle = raycast.ray_angle - raycast.twopi;
		i++;
	}
}

void raycaster(t_master *master, t_img *img) //textured
{
	int x = 0;
	int i = 0;
	int y;
	t_raycast raycast;

	init_raycast(&raycast, master);

	if (raycast.ray_angle < 0)
		raycast.ray_angle = raycast.twopi + raycast.ray_angle;
	// float max_wall_distance = count_max_ray(master);/* Calculate the maximum distance from the player to the farthest wall */;
	while (i < RAYS)
	{
		raycast.color = 0x000000;
		raycast.ray_len = 0.05;
		
		raycast.cos_angle = cos(raycast.ray_angle);
		raycast.sin_angle = sin(raycast.ray_angle);
		while (raycast.ray_x >= 0 && raycast.ray_x <= WIN_W && raycast.ray_y >= 0 && raycast.ray_y <= WIN_H)
		{
			raycast.ray_x = master->player.x + raycast.cos_angle * raycast.ray_len;
			raycast.ray_y = master->player.y + raycast.sin_angle * raycast.ray_len;
			raycast.map_x = raycast.ray_x / master->minimap.block;
			raycast.map_y = raycast.ray_y / master->minimap.block;
			if (raycast.map_x >= 0 && raycast.map_x < master->data.mapsize[0] && raycast.map_y >= 0 && raycast.map_y < master->data.mapsize[1] && master->data.map[raycast.map_y][raycast.map_x] == '1')
				break;
			raycast.ray_len += 0.05;
		}

		//fix fisheye
		raycast.fisheye_angle = master->player.angle - raycast.ray_angle;
		if (raycast.fisheye_angle < 0)
			raycast.fisheye_angle = raycast.twopi + raycast.fisheye_angle;
		if (raycast.fisheye_angle > raycast.twopi)
			raycast.fisheye_angle = raycast.fisheye_angle - raycast.twopi;
		raycast.ray_len = raycast.ray_len * cos(raycast.fisheye_angle);

		raycast.wall_height = 5000 / raycast.ray_len; // give a nice constant for wall scaling
		raycast.wall_top = raycast.halfwin - raycast.wall_height / 2;
		raycast.wall_bottom = raycast.halfwin + raycast.wall_height / 2;
		y = raycast.wall_top;
		raycast.stripe_end = x + raycast.stripe_width;

		wall_analyzerv2(raycast.ray_y, raycast.ray_x, raycast.ray_angle, master, &raycast.color, &raycast);
		printf("ray x: %f ray_y: %f color: %d wall hei %d\n", raycast.ray_x, raycast.ray_y, raycast.color, raycast.wall_height);
		while(x < raycast.stripe_end && x < WIN_W && y < WIN_H)
		{
			y = raycast.wall_top;
			while (y < raycast.wall_bottom)
			{
				if (x > 0 && y > 0 && x < WIN_W && y < WIN_H)
					my_mlx_pixel_put(img, x, y, raycast.color);
				y++;
			}
			x++;
		}
		raycast.ray_angle += raycast.angle_between_rays;
		if (raycast.ray_angle > raycast.twopi)
			raycast.ray_angle = raycast.ray_angle - raycast.twopi;
		i++;
	}
}