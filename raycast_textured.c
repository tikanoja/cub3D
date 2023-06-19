#include "cub3D.h"

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
	if (dda->ray_len_horz < dda->ray_len_vert)
	{
		rc->side = 0;
		rc->ray_len = dda->ray_len_horz;
		rc->ray_y = (int)dda->ray_y_h;
		rc->ray_x = (int)dda->ray_x_h;
		rc->og_ray_x = dda->ray_x_h;
		rc->og_ray_y = dda->ray_y_h;

		if (master->player.y < rc->ray_y)
			rc->texture = &master->data.south;
		else 
			rc->texture = &master->data.north;
	}
	else
	{
		rc->side = 1;
		rc->ray_len = dda->ray_len_vert;
		rc->ray_y = (int)dda->ray_y_v;
		rc->ray_x = (int)dda->ray_x_v;
		rc->og_ray_x = dda->ray_x_v;
		rc->og_ray_y = dda->ray_y_v;
		if (master->player.x < rc->ray_x)
			rc->texture = &master->data.east;
		else
			rc->texture = &master->data.west; 
		}
}

void dda_horizontal(t_dda *dda, t_raycast *rc, t_master *master)
{
	dda->hit = 0;
	dda->aTan = -1 / tan(rc->ray_angle);
	if (rc->ray_angle > M_PI)
	{
		dda->ray_y_h = (int)master->player.y - ((int)master->player.y % master->minimap.block) - 0.0001;
		dda->ray_x_h = (master->player.y - dda->ray_y_h) * dda->aTan + master->player.x;
		dda->y_offset = -master->minimap.block;
		dda->x_offset = -dda->y_offset *dda->aTan;
	}
	if (rc->ray_angle < M_PI)
	{
		dda->ray_y_h = (int)master->player.y - ((int)master->player.y % master->minimap.block) + master->minimap.block;
		dda->ray_x_h = (master->player.y - dda->ray_y_h) * dda->aTan + master->player.x;
		dda->y_offset = master->minimap.block;
		dda->x_offset = -dda->y_offset * dda->aTan;
	}
	if (rc->ray_angle == (float)M_PI || rc->ray_angle == 0)
	{
		dda->ray_x_h = master->player.x;
		dda->ray_y_h = master->player.y;
		dda->hit = 1;
	}
}

void dda_vertical(t_dda *dda, t_raycast *rc, t_master *master)
{
	dda->hit = 0;
	dda->nTan = -tan(rc->ray_angle);
	if (rc->ray_angle > M_PI / 2 && rc->ray_angle < 3 * M_PI / 2)
	{
		dda->ray_x_v = (int)master->player.x - ((int)master->player.x % master->minimap.block) - 0.0001;
		dda->ray_y_v = (master->player.x - dda->ray_x_v) * dda->nTan + master->player.y;
		dda->x_offset = -master->minimap.block;
		dda->y_offset = -dda->x_offset * dda->nTan;
	}
	if (rc->ray_angle < M_PI / 2 || rc->ray_angle > 3 * M_PI / 2)
	{
		dda->ray_x_v = (int)master->player.x - ((int)master->player.x % master->minimap.block) + master->minimap.block;
		dda->ray_y_v = (master->player.x - dda->ray_x_v) * dda->nTan + master->player.y;
		dda->x_offset = master->minimap.block;
		dda->y_offset = -dda->x_offset * dda->nTan;
	}
	if (rc->ray_angle == 0 || rc->ray_angle == (float)M_PI)
	{
		dda->ray_x_v = master->player.x;
		dda->ray_y_v = master->player.y;
		dda->hit = 1;
	}
}

void dda_loop_horizontal(t_dda *dda, t_master *master)
{
	dda->ray_len_horz = 0;
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
	if (dda->ray_x_h > WIN_W || dda->ray_x_h < 0)
		dda->ray_x_h = master->player.x;
	if (dda->ray_y_h > WIN_H || dda->ray_y_h < 0)
		dda->ray_y_h = master->player.y;
	if (dda->ray_y_h == master->player.y || dda->ray_x_h == master->player.x)
		dda->ray_len_horz = 2147483647;
	else
		dda->ray_len_horz = sqrt(pow(dda->ray_y_h - master->player.y, 2) + pow(dda->ray_x_h - master->player.x, 2));
}

void dda_loop_vertical(t_dda *dda, t_master *master)
{
	dda->ray_len_vert = 0;
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
	dda_loop_horizontal(&dda, master);
	dda_vertical(&dda, rc, master);
	dda_loop_vertical(&dda, master);
	wall_handler(rc, &dda, master);
}

void	wall_scaler(t_raycast *rc, t_master *master)
{
	if (rc->side == 0)
	{
		rc->textx = fmod(rc->og_ray_x, master->minimap.block);
		rc->textx = rc->textx / master->minimap.block * rc->texture->width;
	}
	else
	{
		rc->textx = fmod(rc->og_ray_y, master->minimap.block);
		rc->textx = rc->textx / master->minimap.block * rc->texture->width;
	}
	rc->fisheye_angle = master->player.angle - rc->ray_angle;
	if (rc->fisheye_angle < 0)
		rc->fisheye_angle = 2 * M_PI + rc->fisheye_angle;
	if (rc->fisheye_angle > 2 * M_PI)
		rc->fisheye_angle = rc->fisheye_angle - 2 * M_PI;
	rc->ray_len = rc->ray_len * cos(rc->fisheye_angle);
	
	rc->wall_height = master->minimap.block * 700 / rc->ray_len;
	rc->wall_top = rc->halfwin - rc->wall_height / 2;
	rc->wall_bottom = rc->halfwin + rc->wall_height / 2;
	rc->y = rc->wall_top;
	rc->stripe_end = rc->x + rc->stripe_width;
}

void draw_stripe(t_raycast *rc, t_img *img)
{
	int txtindex;
	float mod_step;
	rc->step = 1.0 * rc->texture->height / (float)rc->wall_height;
	mod_step = rc->step;
	txtindex = rc->textx;

	while(rc->x <= rc->stripe_end)
	{
		rc->y = rc->wall_top;
		txtindex = floor(rc->textx);
		mod_step = rc->step;
		while (rc->y <= rc->wall_bottom)
		{
			if (rc->x > 0 && rc->y > 0 && rc->x < WIN_W && rc->y < WIN_H)
				my_mlx_pixel_put(img, rc->x, rc->y, rc->texture->array[txtindex]);
			rc->y++;
			if (mod_step < 1)
				mod_step = mod_step + rc->step;
			else
			{
				txtindex += floor(mod_step) * rc->texture->height;
				mod_step = rc->step + fmod(mod_step, 1.0);
			}
		}
		rc->x++;
		rc->textx += rc->step;
		if (rc->textx > rc->texture->height)
			rc->textx = 0;
	}
	rc->ray_angle += rc->angle_between_rays;
	if (rc->ray_angle > 2 * M_PI)
		rc->ray_angle = rc->ray_angle - 2 * M_PI;
	rc->i++;
}



void txt_raycaster(t_master *master, t_img *img)
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
