/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   update_game.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 13:55:51 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/06/20 13:56:06 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_wall(float x, float y, t_master *master, float buffer_distance)
{
	int		map_x;
	int		map_y;
	float	dist_x;
	float	dist_y;

	map_x = x / master->minimap.block;
	map_y = y / master->minimap.block;
	if (map_x >= 0 && map_x < master->data.mapsize[0] && \
	map_y >= 0 && map_y < master->data.mapsize[1] && \
	master->data.map[map_y][map_x] == '1')
	{
		dist_x = fmod(x, master->minimap.block);
		dist_y = fmod(y, master->minimap.block);
		if (dist_x <= buffer_distance || dist_x >= \
		master->minimap.block - buffer_distance || dist_y <= \
		buffer_distance || dist_y >= master->minimap.block - buffer_distance)
			return (1);
	}
	return (0);
}

void	init_update(t_update *up, t_master *master)
{
	up->mspeed = (float)master->minimap.block / MOVEMENT_SPEED;
	up->updateflag = 0;
	up->sign_x = 0;
	up->sign_y = 0;
}

int	update_game(t_master *master)
{
	t_update	up;

	init_update(&up, master);
	if (master->keylog.w == 1 || master->keylog.up == 1)
		forward(&up, master);
	if (master->keylog.s == 1 || master->keylog.down == 1)
		backward(&up, master);
	if (master->keylog.a == 1)
		strafe_left(&up, master);
	if (master->keylog.d == 1)
		strafe_right(&up, master);
	if (master->keylog.left == 1)
		rotate_left(&up, master);
	if (master->keylog.right == 1)
		rotate_right(&up, master);
	if (up.updateflag == 1)
		run_cub3d(master);
	return (0);
}
