/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_textured.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 10:05:49 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/06/20 10:05:55 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_raycast(t_raycast *raycast, t_master *m)
{
	raycast->stripe_width = WIN_W / RAYS;
	raycast->fov_rad = FOV * (M_PI / 180);
	raycast->ray_angle = m->player.angle - (raycast->fov_rad / 2);
	raycast->angle_between_rays = raycast->fov_rad / RAYS;
	raycast->ray_x = m->player.x;
	raycast->ray_y = m->player.y;
	raycast->twopi = 2 * M_PI;
	raycast->halfwin = WIN_H / 2;
	raycast->fov_rad = FOV * (M_PI / 180);
	raycast->ray_angle = m->player.angle - (raycast->fov_rad / 2);
	if (raycast->ray_angle < 0)
		raycast->ray_angle = 2 * M_PI + raycast->ray_angle;
	raycast->angle_between_rays = raycast->fov_rad / RAYS;
	raycast->i = 0;
	raycast->y = 0;
	raycast->x = 0;
}

void	init_draw_stripe(t_raycast *rc)
{
	rc->step = rc->texture->height / (float)rc->wall_height;
	rc->mod_step = rc->step;
	rc->txtindex = rc->textx;
	rc->txtarrsize = rc->texture->height * rc->texture->width;
}

void	draw_stripe_helper(t_raycast *rc)
{
	rc->y = rc->wall_top;
	rc->txtindex = rc->textx;
	rc->mod_step = 0;
}

void	draw_stripe(t_raycast *rc, t_img *img)
{
	init_draw_stripe(rc);
	while (rc->x < rc->stripe_end)
	{
		draw_stripe_helper(rc);
		while (rc->y <= rc->wall_bottom && rc->y < WIN_H)
		{
			if (rc->txtindex > rc->txtarrsize)
				rc->txtindex = rc->txtarrsize - rc->texture->width + rc->textx;
			if (rc->x >= 0 && rc->y >= 0 && rc->x < WIN_W && rc->y < WIN_H)
				my_mlx_pixel_put(img, rc->x, rc->y, \
				rc->texture->array[rc->txtindex]);
			rc->y++;
			if (rc->mod_step < 1)
				rc->mod_step = rc->mod_step + rc->step;
			else
			{
				rc->txtindex += (int)rc->mod_step * rc->texture->width;
				rc->mod_step = rc->step + fmod(rc->mod_step, 1.0);
			}
		}
		rc->x++;
		rc->textx += rc->step;
		if (rc->textx > rc->texture->height)
			rc->textx = 0;
	}
}

void	txt_raycaster(t_master *m, t_img *img)
{
	t_raycast	rc;

	init_raycast(&rc, m);
	while (rc.i < RAYS)
	{
		dda(&rc, m);
		wall_scaler(&rc, m);
		draw_stripe(&rc, img);
		rc.ray_angle += rc.angle_between_rays;
		if (rc.ray_angle > 2 * M_PI)
			rc.ray_angle = rc.ray_angle - 2 * M_PI;
		rc.i++;
	}
}
