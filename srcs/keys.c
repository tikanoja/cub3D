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
		master->keylog.w = 1;
		master->keylog.up = 1;
	}
	else if (keycode == 1 || keycode == 125)
	{
		master->keylog.s = 1;
		master->keylog.down = 1;
	}
	else if (keycode == 0)
		master->keylog.a = 1;
	else if (keycode == 2)
		master->keylog.d = 1;
	else if (keycode == 123)
		master->keylog.left = 1;
	else if (keycode == 124)
		master->keylog.right = 1;
	return (0);
}

int	key_release(int keycode, t_master *master)
{
	if (keycode == 13 || keycode == 126)
	{
		master->keylog.w = 0;
		master->keylog.up = 0;
	}
	else if (keycode == 1 || keycode == 125)
	{
		master->keylog.s = 0;
		master->keylog.down = 0;
	}
	else if (keycode == 0)
		master->keylog.a = 0;
	else if (keycode == 2)
		master->keylog.d = 0;
	else if (keycode == 123)
		master->keylog.left = 0;
	else if (keycode == 124)
		master->keylog.right = 0;
	return (0);
}
