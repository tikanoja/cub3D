/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 10:24:36 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/07/03 12:39:38 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	strafe_left(t_update *up, t_master *master)
{
	up->new_x = master->player.x + up->mspeed * sin(master->player.angle);
	up->new_y = master->player.y - up->mspeed * cos(master->player.angle);
	up->sign_x = WALLDIST;
	up->sign_y = WALLDIST;
	if (master->player.angle <= M_PI / 2 && master->player.angle >= 0)
		up->sign_x = -WALLDIST;
	else if (master->player.angle > M_PI / 2 && master->player.angle <= M_PI)
	{
		up->sign_x = -WALLDIST;
		up->sign_y = -WALLDIST;
	}
	else if (master->player.angle > M_PI && \
	master->player.angle <= 3 * M_PI / 2)
		up->sign_y = -WALLDIST;
	if ((!is_wall(up->new_x - up->sign_x, up->new_y - up->sign_y \
	, master, master->minimap.block) && !window_check(up)) || \
	(GOD_MODE == 0 && !window_check(up)))
	{
		master->player.x = up->new_x;
		master->player.y = up->new_y;
		up->updateflag = 1;
	}
}

void	strafe_right(t_update *up, t_master *master)
{
	up->new_x = master->player.x - up->mspeed * sin(master->player.angle);
	up->new_y = master->player.y + up->mspeed * cos(master->player.angle);
	up->sign_x = -WALLDIST;
	up->sign_y = -WALLDIST;
	if (master->player.angle <= M_PI / 2 && master->player.angle >= 0)
		up->sign_x = WALLDIST;
	else if (master->player.angle > M_PI / 2 && master->player.angle <= M_PI)
	{
		up->sign_x = WALLDIST;
		up->sign_y = WALLDIST;
	}
	else if (master->player.angle > M_PI && \
	master->player.angle <= 3 * M_PI / 2)
		up->sign_y = WALLDIST;
	if ((!is_wall(up->new_x - up->sign_x, up->new_y - \
	up->sign_y, master, master->minimap.block) && !window_check(up)) || \
	(GOD_MODE == 0 && !window_check(up)))
	{
		master->player.x = up->new_x;
		master->player.y = up->new_y;
		up->updateflag = 1;
	}
}

void	rotate_left(t_update *up, t_master *master)
{
	master->player.angle -= 0.03;
	if (master->player.angle < 0)
		master->player.angle = 2 * M_PI + master->player.angle;
	up->updateflag = 1;
}

void	rotate_right(t_update *up, t_master *master)
{
	master->player.angle += 0.03;
	if (master->player.angle > 2 * M_PI)
		master->player.angle = master->player.angle - 2 * M_PI;
	up->updateflag = 1;
}
