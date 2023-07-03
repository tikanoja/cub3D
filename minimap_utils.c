/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:47:08 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/06/20 13:47:28 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_minimap_coords(t_minimap_coords *coords, t_master *master)
{
	coords->x = WIN_W / master->data.mapsize[0] / 2;
	coords->y = WIN_H / master->data.mapsize[1] / 2;
	if (coords->x <= coords->y)
		coords->block = coords->x / 2;
	else
		coords->block = coords->y / 2;
	coords->x = 0;
	coords->y = 0;
	coords->i = 0;
	coords->j = 0;
}

void	init_get_player_coords(int *flag, int *i, t_master *m)
{
	(*flag) = 0;
	(*i) = 0;
	m->player.y = 0;
}

void	init_draw_player(int *start_y, int *start_x, t_master *master)
{
	(*start_y) = (int)master->player.y - 2;
	(*start_x) = (int)master->player.x - 2;
}
