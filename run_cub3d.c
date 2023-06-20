/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cub3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 10:06:10 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/06/20 10:06:12 by ttikanoj         ###   ########.fr       */
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

void	init_update(t_update *up)
{
	up->mspeed = 1.5;
	up->updateflag = 0;
	up->sign_x = 0;
	up->sign_y = 0;
}

int	update_game(t_master *master)
{
	t_update	up;

	init_update(&up);
	if (master->keylog.W == 1 || master->keylog.UP == 1)
		forward(&up, master);
	if (master->keylog.S == 1 || master->keylog.DOWN == 1)
		backward(&up, master);
	if (master->keylog.A == 1)
		strafe_left(&up, master);
	if (master->keylog.D == 1)
		strafe_right(&up, master);
	if (master->keylog.LEFT == 1)
		rotate_left(&up, master);
	if (master->keylog.RIGHT == 1)
		rotate_right(&up, master);
	if (up.updateflag == 1)
		run_cub3d(master);
	return (0);
}

void	run_cub3d(t_master *master)
{
	mlx_destroy_image(master->mlx.mlx_ptr, master->img.img);
	master->img.img = mlx_new_image(master->mlx.mlx_ptr, WIN_W, WIN_H);
	master->img.addr = mlx_get_data_addr(master->img.img, &master->img.bpp, \
	&master->img.llen, &master->img.en);
	draw_background(master, &master->img);
	txt_raycaster(master, &master->img);
	draw_minimap(master, &master->img);
	mlx_put_image_to_window(master->mlx.mlx_ptr, master->mlx.mlx_win, \
	master->img.img, 0, 0);
}

void	init_cub3d(t_master master)
{
	master.img.img = mlx_new_image(master.mlx.mlx_ptr, WIN_W, WIN_H);
	master.img.addr = mlx_get_data_addr(master.img.img, &master.img.bpp, \
	&master.img.llen, &master.img.en);
	draw_background(&master, &master.img);
	draw_minimap(&master, &master.img);
	txt_raycaster(&master, &master.img);
	mlx_put_image_to_window(master.mlx.mlx_ptr, master.mlx.mlx_win, \
	master.img.img, 0, 0);
	mlx_hook(master.mlx.mlx_win, 17, 0, exit_gracefully, &master);
	mlx_hook(master.mlx.mlx_win, 2, 0, key_press, &master);
	mlx_hook(master.mlx.mlx_win, 3, 0, key_release, &master);
	mlx_loop_hook(master.mlx.mlx_ptr, update_game, &master);
	mlx_loop(master.mlx.mlx_ptr);
}
