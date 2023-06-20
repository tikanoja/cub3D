/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   movement.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 10:24:36 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/06/20 10:24:52 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	strafe_left(t_update *up, t_master *master)
{
	up->new_x = master->player.x + up->mspeed * sin(master->player.angle);
	up->new_y = master->player.y - up->mspeed * cos(master->player.angle);
	up->sign_x = WALLDIST;
	up->sign_y = WALLDIST;
	if (cos(master->player.angle) >= 0)
		up->sign_x = -WALLDIST;
	if (sin(master->player.angle) >= 0)
		up->sign_y = -WALLDIST;
	if (!is_wall(up->new_x - up->sign_x, up->new_y - \
	up->sign_y, master, master->minimap.block) || GOD_MODE == 0)
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
	if (cos(master->player.angle) >= 0)
		up->sign_x = WALLDIST;
	if (sin(master->player.angle) >= 0)
		up->sign_y = WALLDIST;
	if (!is_wall(up->new_x - up->sign_x, up->new_y - \
	up->sign_y, master, master->minimap.block) || GOD_MODE == 0)
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
