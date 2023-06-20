/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 10:03:54 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/06/20 10:03:57 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	key_press(int keycode, t_master *master)
{
	if (keycode == 53 || keycode == 6)
	{
		exit_gracefully(master);
	}
	else if (keycode == 13 || keycode == 126)
	{
		master->keylog.W = 1;
		master->keylog.UP = 1;
	}
	else if (keycode == 1 || keycode == 125)
	{
		master->keylog.S = 1;
		master->keylog.DOWN = 1;
	}
	else if (keycode == 0)
		master->keylog.A = 1;
	else if (keycode == 2)
		master->keylog.D = 1;
	else if (keycode == 123)
		master->keylog.LEFT = 1;
	else if (keycode == 124)
		master->keylog.RIGHT = 1;
	return (0);
}

int	key_release(int keycode, t_master *master)
{
	if (keycode == 13 || keycode == 126) //anglen suuntaan
	{
		master->keylog.W = 0;
		master->keylog.UP = 0;
	}
	else if (keycode == 1 || keycode == 125) //anglen suuntaan
	{
		master->keylog.S = 0;
		master->keylog.DOWN = 0;
	}
	else if (keycode == 0)
		master->keylog.A = 0;
	else if (keycode == 2)
		master->keylog.D = 0;
	else if (keycode == 123)
		master->keylog.LEFT = 0;
	else if (keycode == 124)
		master->keylog.RIGHT = 0;
	return (0);
}
