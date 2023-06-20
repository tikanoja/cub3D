/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cub3d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 10:06:10 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/06/20 16:07:59 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	run_cub3d(t_master *master)
{
	mlx_destroy_image(master->mlx.mlx_ptr, master->img.img);
	master->img.img = mlx_new_image(master->mlx.mlx_ptr, WIN_W, WIN_H);
	master->img.addr = mlx_get_data_addr(master->img.img, &master->img.bpp, \
	&master->img.llen, &master->img.en);
	draw_background(master, &master->img);
	txt_raycaster(master, &master->img);
	if (MINIMAP == 1)
		draw_minimap(master, &master->img);
	mlx_put_image_to_window(master->mlx.mlx_ptr, master->mlx.mlx_win, \
	master->img.img, 0, 0);
}

void	init_rc(t_master *master)
{
	int	x;
	int	y;

	x = WIN_W / master->data.mapsize[0] / 2;
	y = WIN_H / master->data.mapsize[1] / 2;
	if (x <= y)
		master->minimap.block = x;
	else
		master->minimap.block = y;
	get_player_coords(master);
}

void	init_cub3d(t_master master)
{
	master.img.img = mlx_new_image(master.mlx.mlx_ptr, WIN_W, WIN_H);
	master.img.addr = mlx_get_data_addr(master.img.img, &master.img.bpp, \
	&master.img.llen, &master.img.en);
	draw_background(&master, &master.img);
	init_rc(&master);
	txt_raycaster(&master, &master.img);
	if (MINIMAP == 1)
		draw_minimap(&master, &master.img);
	mlx_put_image_to_window(master.mlx.mlx_ptr, master.mlx.mlx_win, \
	master.img.img, 0, 0);
	mlx_hook(master.mlx.mlx_win, 17, 0, exit_gracefully, &master);
	mlx_hook(master.mlx.mlx_win, 2, 0, key_press, &master);
	mlx_hook(master.mlx.mlx_win, 3, 0, key_release, &master);
	mlx_loop_hook(master.mlx.mlx_ptr, update_game, &master);
	mlx_loop(master.mlx.mlx_ptr);
}
