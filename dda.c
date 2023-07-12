/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dda.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 11:28:39 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/06/20 11:28:55 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	dda_horizontal(t_dda *dda, t_raycast *rc, t_master *m)
{
	dda->hit = 0;
	dda->atan = -1 / tan(rc->ray_angle);
	if (rc->ray_angle > M_PI)
	{
		dda->ray_y_h = (int)m->player.y - ((int)m->player.y % \
		m->minimap.block) - 0.0001;
		dda->ray_x_h = (m->player.y - dda->ray_y_h) * dda->atan + m->player.x;
		dda->y_offset = -m->minimap.block;
		dda->x_offset = -dda->y_offset * dda->atan;
	}
	if (rc->ray_angle < M_PI)
	{
		dda->ray_y_h = (int)m->player.y - ((int)m->player.y % \
		m->minimap.block) + m->minimap.block;
		dda->ray_x_h = (m->player.y - dda->ray_y_h) * dda->atan + m->player.x;
		dda->y_offset = m->minimap.block;
		dda->x_offset = -dda->y_offset * dda->atan;
	}
	if (rc->ray_angle == (float)M_PI || rc->ray_angle == 0)
	{
		dda->ray_x_h = m->player.x;
		dda->ray_y_h = m->player.y;
		dda->hit = 1;
	}
}

void	dda_vertical(t_dda *dda, t_raycast *rc, t_master *m)
{
	dda->hit = 0;
	dda->ntan = -tan(rc->ray_angle);
	if (rc->ray_angle > M_PI / 2 && rc->ray_angle < 3 * M_PI / 2)
	{
		dda->ray_x_v = (int)m->player.x - ((int)m->player.x % \
		m->minimap.block) - 0.0001;
		dda->ray_y_v = (m->player.x - dda->ray_x_v) * dda->ntan + m->player.y;
		dda->x_offset = -m->minimap.block;
		dda->y_offset = -dda->x_offset * dda->ntan;
	}
	if (rc->ray_angle < M_PI / 2 || rc->ray_angle > 3 * M_PI / 2)
	{
		dda->ray_x_v = (int)m->player.x - ((int)m->player.x % \
		m->minimap.block) + m->minimap.block;
		dda->ray_y_v = (m->player.x - dda->ray_x_v) * dda->ntan + m->player.y;
		dda->x_offset = m->minimap.block;
		dda->y_offset = -dda->x_offset * dda->ntan;
	}
	if (rc->ray_angle == 0 || rc->ray_angle == (float)M_PI)
	{
		dda->ray_x_v = m->player.x;
		dda->ray_y_v = m->player.y;
		dda->hit = 1;
	}
}

void	dda_loop_horizontal(t_dda *d, t_master *m)
{
	while (!d->hit && d->ray_x_h >= 0 && d->ray_y_h >= 0)
	{
		d->map_x = (int)d->ray_x_h / m->minimap.block;
		d->map_y = (int)d->ray_y_h / m->minimap.block;
		if (d->map_x >= 0 && d->map_x < m->data.mapsize[0] && d->map_y >= 0 \
		&& d->map_y < m->data.mapsize[1] && dda_arr_check(d, m) && \
		m->data.map[d->map_y][d->map_x] == '1')
			d->hit = 1;
		else
		{
			d->ray_x_h += d->x_offset;
			d->ray_y_h += d->y_offset;
		}
		if (d->ray_x_h > WIN_W || d->ray_y_h > WIN_H)
			break ;
	}
	if (d->ray_x_h > WIN_W || d->ray_x_h < 0)
		d->ray_x_h = m->player.x;
	if (d->ray_y_h > WIN_H || d->ray_y_h < 0)
		d->ray_y_h = m->player.y;
	if (d->hit == 0 && (d->ray_y_h == m->player.y || d->ray_x_h == m->player.x))
		d->ray_len_horz = 2147483647;
	else
		d->ray_len_horz = sqrt(pow((d->ray_y_h + 0.0001) - m->player.y, 2) + \
		pow(d->ray_x_h - m->player.x, 2));
}

void	dda_loop_vertical(t_dda *d, t_master *m)
{
	while (!d->hit && d->ray_x_v >= 0 && d->ray_y_v >= 0)
	{
		d->map_x = (int)d->ray_x_v / m->minimap.block;
		d->map_y = (int)d->ray_y_v / m->minimap.block;
		if (d->map_x >= 0 && d->map_x < m->data.mapsize[0] && d->map_y >= 0 \
		&& d->map_y < m->data.mapsize[1] && dda_arr_check(d, m) && \
		m->data.map[d->map_y][d->map_x] == '1')
			d->hit = 1;
		else
		{
			d->ray_x_v += d->x_offset;
			d->ray_y_v += d->y_offset;
		}
		if (d->ray_x_v > WIN_W || d->ray_y_v > WIN_H)
			break ;
	}
	if (d->ray_x_v > WIN_W || d->ray_x_v < 0)
		d->ray_x_v = m->player.x;
	if (d->ray_y_v > WIN_H || d->ray_y_v < 0)
		d->ray_y_v = m->player.y;
	if (d->ray_y_v == m->player.y || d->ray_x_v == m->player.x)
		d->ray_len_vert = 2147483647;
	else
		d->ray_len_vert = sqrt(pow((d->ray_x_v + 0.0001) - m->player.x, 2) + \
		pow(d->ray_y_v - m->player.y, 2));
}

void	dda(t_raycast *rc, t_master *m)
{
	t_dda	dda;

	dda_horizontal(&dda, rc, m);
	dda_loop_horizontal(&dda, m);
	dda_vertical(&dda, rc, m);
	dda_loop_vertical(&dda, m);
	wall_handler(rc, &dda, m);
}
