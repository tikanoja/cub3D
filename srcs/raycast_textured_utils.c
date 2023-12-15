/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast_textured_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:31:07 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/06/20 11:31:20 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	dda_arr_check(t_dda *d, t_master *m)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (m->data.map[y][x])
	{
		if (x < d->map_x)
			x++;
		if (y < d->map_y)
			y++;
		if (x == d->map_x && y == d->map_y)
			return (1);
	}
	return (0);
}

void	wall_handler(t_raycast *rc, t_dda *dda, t_master *m)
{
	if (dda->ray_len_horz < dda->ray_len_vert)
	{
		rc->side = 0;
		rc->ray_len = dda->ray_len_horz;
		rc->ray_y = (int)dda->ray_y_h;
		rc->ray_x = (int)dda->ray_x_h;
		rc->og_ray_x = dda->ray_x_h;
		rc->og_ray_y = dda->ray_y_h;
		if (m->player.y < rc->ray_y)
			rc->texture = &m->data.south;
		else
			rc->texture = &m->data.north;
		return ;
	}
	rc->side = 1;
	rc->ray_len = dda->ray_len_vert;
	rc->ray_y = (int)dda->ray_y_v;
	rc->ray_x = (int)dda->ray_x_v;
	rc->og_ray_x = dda->ray_x_v;
	rc->og_ray_y = dda->ray_y_v;
	if (m->player.x < rc->ray_x)
		rc->texture = &m->data.east;
	else
		rc->texture = &m->data.west;
}

void	wall_scaler(t_raycast *rc, t_master *m)
{
	if (rc->side == 0)
	{
		rc->textx = fmod(rc->og_ray_x, m->minimap.block);
		rc->textx = rc->textx / m->minimap.block * rc->texture->width;
	}
	else
	{
		rc->textx = fmod(rc->og_ray_y, m->minimap.block);
		rc->textx = rc->textx / m->minimap.block * rc->texture->width;
	}
	rc->fisheye_angle = m->player.angle - rc->ray_angle;
	if (rc->fisheye_angle < 0)
		rc->fisheye_angle = 2 * M_PI + rc->fisheye_angle;
	if (rc->fisheye_angle > 2 * M_PI)
		rc->fisheye_angle = 2 * M_PI - rc->fisheye_angle;
	rc->ray_len = rc->ray_len * cos(rc->fisheye_angle);
	rc->wall_height = m->minimap.block * 700 / rc->ray_len;
	rc->wall_top = rc->halfwin - rc->wall_height / 2;
	rc->wall_bottom = rc->halfwin + rc->wall_height / 2;
	rc->y = rc->wall_top;
	rc->stripe_end = rc->x + rc->stripe_width;
}
