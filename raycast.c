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

int		*wall_analyzerv3(float ray_y, float ray_x, float ray_angle, t_master *master, t_raycast *raycast)
{
	if (ray_angle >= M_PI && ray_angle <= 2 * M_PI) // looking up
	{
		if ((int)ceilf(ray_y) % master->minimap.block == 0 && master->data.map[(int)(raycast->ray_y + master->minimap.block) / master->minimap.block][(int)raycast->ray_x / master->minimap.block] == '0') // north
			return (master->data.north);
		else if ((int)floorf(ray_x) % master->minimap.block == 0 && ray_x > master->player.x) // east
			return (master->data.east);
		else if ((int)ceilf(ray_x) % master->minimap.block == 0 && ray_x < master->player.x) //west
			return (master->data.west);
	}
	else if (ray_angle >= 0 && ray_angle < M_PI) // looking down
	{
		if ((int)floorf(ray_y) % master->minimap.block == 0 && master->data.map[(int)(raycast->ray_y - master->minimap.block) / master->minimap.block][(int)raycast->ray_x / master->minimap.block] == '0') // south
			return (master->data.south);
		else if ((int)floorf(ray_x) % master->minimap.block == 0 && ray_x > master->player.x) // east
			return (master->data.east);
		else if ((int)ceilf(ray_x) % master->minimap.block == 0 && ray_x < master->player.x) //west
			return (master->data.west);
	}
	return (master->data.north);
}

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



// void raycaster(t_master *master, t_img *img) //untextured
// {
// 	int x = 0;
// 	int i = 0;
// 	int y;
// 	t_raycast raycast;

// 	init_raycast(&raycast, master);

// 	if (raycast.ray_angle < 0)
// 		raycast.ray_angle = raycast.twopi + raycast.ray_angle;
// 	// float max_wall_distance = count_max_ray(master);/* Calculate the maximum distance from the player to the farthest wall */;
// 	while (i < RAYS)
// 	{
// 		raycast.color = 0x000000;
// 		raycast.ray_len = 0.05;
		
// 		raycast.cos_angle = cos(raycast.ray_angle);
// 		raycast.sin_angle = sin(raycast.ray_angle);
// 		while (raycast.ray_x >= 0 && raycast.ray_x <= WIN_W && raycast.ray_y >= 0 && raycast.ray_y <= WIN_H)
// 		{
// 			raycast.ray_x = master->player.x + raycast.cos_angle * raycast.ray_len;
// 			raycast.ray_y = master->player.y + raycast.sin_angle * raycast.ray_len;
// 			raycast.map_x = raycast.ray_x / master->minimap.block;
// 			raycast.map_y = raycast.ray_y / master->minimap.block;
// 			if (raycast.map_x >= 0 && raycast.map_x < master->data.mapsize[0] && raycast.map_y >= 0 && raycast.map_y < master->data.mapsize[1] && master->data.map[raycast.map_y][raycast.map_x] == '1')
// 				break;
// 			raycast.ray_len += 0.05;
// 		}

// 		//fix fisheye
// 		raycast.fisheye_angle = master->player.angle - raycast.ray_angle;
// 		if (raycast.fisheye_angle < 0)
// 			raycast.fisheye_angle = raycast.twopi + raycast.fisheye_angle;
// 		if (raycast.fisheye_angle > raycast.twopi)
// 			raycast.fisheye_angle = raycast.fisheye_angle - raycast.twopi;
// 		raycast.ray_len = raycast.ray_len * cos(raycast.fisheye_angle);

// 		raycast.wall_height = 5000 / raycast.ray_len; // give a nice constant for wall scaling
// 		raycast.wall_top = raycast.halfwin - raycast.wall_height / 2;
// 		raycast.wall_bottom = raycast.halfwin + raycast.wall_height / 2;
// 		y = raycast.wall_top;
// 		raycast.stripe_end = x + raycast.stripe_width;

// 		wall_analyzerv2(raycast.ray_y, raycast.ray_x, raycast.ray_angle, master, &raycast.color, &raycast);
// 		// printf("ray x: %f ray_y: %f color: %d wall hei %d\n", raycast.ray_x, raycast.ray_y, raycast.color, raycast.wall_height);
// 		while(x < raycast.stripe_end && x < WIN_W && y < WIN_H)
// 		{
// 			y = raycast.wall_top;
// 			while (y < raycast.wall_bottom)
// 			{
// 				if (x > 0 && y > 0 && x < WIN_W && y < WIN_H)
// 					my_mlx_pixel_put(img, x, y, raycast.color);
// 				y++;
// 			}
// 			x++;
// 		}
// 		raycast.ray_angle += raycast.angle_between_rays;
// 		if (raycast.ray_angle > raycast.twopi)
// 			raycast.ray_angle = raycast.ray_angle - raycast.twopi;
// 		i++;
// 	}
// }

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
	raycast->fov_rad = FOV * (M_PI / 180);
	raycast->ray_angle = master->player.angle - (raycast->fov_rad / 2);
	if (raycast->ray_angle < 0)
		raycast->ray_angle = 2 * M_PI + raycast->ray_angle;
	raycast->angle_between_rays = raycast->fov_rad / RAYS;
	raycast->i = 0;
	raycast->y = 0;
	raycast->x = 0;
}

void	wall_handler(t_raycast *rc, t_dda *dda, t_master *master)
{
	rc->color = 0x000000;
	if (dda->ray_len_horz < dda->ray_len_vert) //NORTH OR SOUTH
	{
		rc->ray_len = dda->ray_len_horz;
		rc->ray_y = (int)dda->ray_y_h;
		rc->ray_x = (int)dda->ray_x_h;
		if (master->player.y < rc->ray_y) //south
			rc->color = 0x4d9078; //green
		else //north
			rc->color = 0xf78154; //orange
	}
	else //EAST OR WEST
	{
		rc->ray_len = dda->ray_len_vert;
		rc->ray_y = (int)dda->ray_y_v;
		rc->ray_x = (int)dda->ray_x_v;
		if (master->player.x < rc->ray_x) //east
			rc->color = 0x3d405b; //gray
		else //west
			rc->color = 0x084b83; //blue
		}
}

void dda_horizontal(t_dda *dda, t_raycast *rc, t_master *master)
{
	dda->hit = 0;
	dda->aTan = -1 / tan(rc->ray_angle);
	if (rc->ray_angle > M_PI) // looking up
	{
		dda->ray_y_h = (int)master->player.y - ((int)master->player.y % master->minimap.block) - 0.0001;
		dda->ray_x_h = (master->player.y - dda->ray_y_h) * dda->aTan + master->player.x;
		dda->y_offset = -master->minimap.block;
		dda->x_offset = -dda->y_offset *dda->aTan;
	}
	if (rc->ray_angle < M_PI) // looking down
	{
		dda->ray_y_h = (int)master->player.y - ((int)master->player.y % master->minimap.block) + master->minimap.block;
		dda->ray_x_h = (master->player.y - dda->ray_y_h) * dda->aTan + master->player.x;
		dda->y_offset = master->minimap.block;
		dda->x_offset = -dda->y_offset * dda->aTan;
	}
	if (rc->ray_angle == (float)M_PI || rc->ray_angle == 0) // looking directly down
	{
		dda->ray_x_h = master->player.x;
		dda->ray_y_h = master->player.y;
		dda->hit = 1;
	}
}

void dda_vertical(t_dda *dda, t_raycast *rc, t_master *master)
{
	dda->hit = 0;
	//VERTICAL
	dda->nTan = -tan(rc->ray_angle);
	if (rc->ray_angle > M_PI / 2 && rc->ray_angle < 3 * M_PI / 2) // looking left
	{
		dda->ray_x_v = (int)master->player.x - ((int)master->player.x % master->minimap.block) - 0.0001;
		dda->ray_y_v = (master->player.x - dda->ray_x_v) * dda->nTan + master->player.y;
		dda->x_offset = -master->minimap.block;
		dda->y_offset = -dda->x_offset * dda->nTan;
	}
	if (rc->ray_angle < M_PI / 2 || rc->ray_angle > 3 * M_PI / 2) // looking right
	{
		dda->ray_x_v = (int)master->player.x - ((int)master->player.x % master->minimap.block) + master->minimap.block;
		dda->ray_y_v = (master->player.x - dda->ray_x_v) * dda->nTan + master->player.y;
		dda->x_offset = master->minimap.block;
		dda->y_offset = -dda->x_offset * dda->nTan;
	}
	if (rc->ray_angle == 0 || rc->ray_angle == (float)M_PI) // looking directly up
	{
		dda->ray_x_v = master->player.x;
		dda->ray_y_v = master->player.y;
		dda->hit = 1;
	}
}

void dda_loop_horizontal(t_dda *dda, t_master *master)//, t_raycast *rc)
{
	while (!dda->hit && dda->ray_x_h >= 0 && dda->ray_y_h >= 0)
	{
		dda->map_x = (int)dda->ray_x_h / master->minimap.block;
		dda->map_y = (int)dda->ray_y_h / master->minimap.block;
		if (dda->map_x >= 0 && dda->map_x < master->data.mapsize[0] && dda->map_y >= 0 && dda->map_y < master->data.mapsize[1] && master->data.map[dda->map_y][dda->map_x] == '1')
			dda->hit = 1;
		else
		{
			dda->ray_x_h += dda->x_offset;
			dda->ray_y_h += dda->y_offset;
		}
		if (dda->ray_x_h > WIN_W || dda->ray_y_h > WIN_H)
			break;
	}
	// if (rc->ray_angle > M_PI)
	// 	dda->ray_y_h += 1.0001;
	if (dda->ray_x_h > WIN_W || dda->ray_x_h < 0)
		dda->ray_x_h = master->player.x;
	if (dda->ray_y_h > WIN_H || dda->ray_y_h < 0)
		dda->ray_y_h = master->player.y;
	if (dda->ray_y_h == master->player.y || dda->ray_x_h == master->player.x)
		dda->ray_len_horz = 2147483647;
	else
		dda->ray_len_horz = sqrt(pow(dda->ray_y_h - master->player.y, 2) + pow(dda->ray_x_h - master->player.x, 2));
}

void dda_loop_vertical(t_dda *dda, t_master *master)//, t_raycast *rc)
{
	while (!dda->hit && dda->ray_x_v >= 0 && dda->ray_y_v >= 0)
	{
		dda->map_x = (int)dda->ray_x_v / master->minimap.block;
		dda->map_y = (int)dda->ray_y_v / master->minimap.block;
		if (dda->map_x >= 0 && dda->map_x < master->data.mapsize[0] && dda->map_y >= 0 && dda->map_y < master->data.mapsize[1] && master->data.map[dda->map_y][dda->map_x] == '1')
			dda->hit = 1;
		else
		{
			dda->ray_x_v += dda->x_offset;
			dda->ray_y_v += dda->y_offset;
		}
		if (dda->ray_x_v > WIN_W || dda->ray_y_v > WIN_H)
			break;
	}
	// if (rc->ray_angle > M_PI / 2 && rc->ray_angle < 3 * M_PI / 2)
	// 	dda->ray_x_v += 1.0001;
	if (dda->ray_x_v > WIN_W || dda->ray_x_v < 0)
		dda->ray_x_v = master->player.x;
	if (dda->ray_y_v > WIN_H || dda->ray_y_v < 0)
		dda->ray_y_v = master->player.y;
	if (dda->ray_y_v == master->player.y || dda->ray_x_v == master->player.x)
		dda->ray_len_vert = 2147483647;
	else
		dda->ray_len_vert = sqrt(pow(dda->ray_x_v - master->player.x, 2) + pow(dda->ray_y_v - master->player.y, 2));
}

void dda(t_raycast *rc, t_master *master)
{
	t_dda dda;

	dda_horizontal(&dda, rc, master);
	dda_loop_horizontal(&dda, master);//, rc);
	dda_vertical(&dda, rc, master);
	dda_loop_vertical(&dda, master);//, rc);
	wall_handler(rc, &dda, master);
}

void	wall_scaler(t_raycast *rc, t_master *master)
{
	rc->fisheye_angle = master->player.angle - rc->ray_angle;
	if (rc->fisheye_angle < 0)
		rc->fisheye_angle = 2 * M_PI + rc->fisheye_angle;
	if (rc->fisheye_angle > 2 * M_PI)
		rc->fisheye_angle = rc->fisheye_angle - 2 * M_PI;
	rc->ray_len = rc->ray_len * cos(rc->fisheye_angle);
	
	rc->wall_height = 7000 / rc->ray_len; // give a nice constant for wall scaling
	rc->wall_top = rc->halfwin - rc->wall_height / 2;
	rc->wall_bottom = rc->halfwin + rc->wall_height / 2;
	rc->y = rc->wall_top;
	rc->stripe_end = rc->x + rc->stripe_width;
}

void	draw_stripe(t_raycast *rc, t_img *img)
{
	while(rc->x < rc->stripe_end)
	{
		rc->y = rc->wall_top;
		while (rc->y < rc->wall_bottom)
		{
			if (rc->x > 0 && rc->y > 0 && rc->x < WIN_W && rc->y < WIN_H)
				my_mlx_pixel_put(img, rc->x, rc->y, rc->color);
			rc->y++;
		}
		rc->x++;
	}
	rc->ray_angle += rc->angle_between_rays;
	if (rc->ray_angle > 2 * M_PI)
		rc->ray_angle = rc->ray_angle - 2 * M_PI;
	rc->i++;
}

void raycaster(t_master *master, t_img *img)
{
	t_raycast rc;
	init_raycast(&rc, master);
	while(rc.i < RAYS)
	{
		dda(&rc, master);
		wall_scaler(&rc, master);
		draw_stripe(&rc, img);
	}
}
