/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 10:03:37 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/06/20 10:03:39 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	drawinit(t_bres *bres, t_player *coords)
{
	bres->x = coords->x;
	bres->y = coords->y;
	bres->dx = fabsf(coords->endx - coords->x);
	bres->dy = -fabsf(coords->endy - coords->y);
	if (bres->x < coords->endx)
		bres->stepx = 1;
	else
		bres->stepx = -1;
	if (bres->y < coords->endy)
		bres->stepy = 1;
	else
		bres->stepy = -1;
	bres->error = bres->dx + bres->dy;
}

void	drawl(t_img *img, t_player *coords, int color)
{
	t_bres	bre;

	drawinit(&bre, coords);
	while (1)
	{
		if (bre.x > 0 && bre.x < WIN_W && bre.y > 0 && bre.y < WIN_H)
			my_mlx_pixel_put(img, bre.x, bre.y, color);
		if (bre.x == coords->endx && bre.y == coords->endy)
			break ;
		bre.e2 = 2 * bre.error;
		if (bre.e2 >= bre.dy)
		{
			if (bre.x == coords->endx)
				break ;
			bre.error = bre.error + bre.dy;
			bre.x = bre.x + bre.stepx;
		}
		if (bre.e2 <= bre.dx)
		{
			if (bre.y == coords->endy)
				break ;
			bre.error = bre.error + bre.dx;
			bre.y = bre.y + bre.stepy;
		}
	}
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*pixel;

	pixel = img->addr + (y * img->llen + x * (img->bpp / 8));
	*(unsigned int *)pixel = color;
}

void	draw_background(t_master *master, t_img *img)
{
	int	x;
	int	y;

	x = 0;
	y = 0;
	while (y < WIN_H)
	{
		while (x < WIN_W)
		{
			if (y < WIN_H / 2)
				my_mlx_pixel_put(img, x, y, master->data.s_int);
			else
				my_mlx_pixel_put(img, x, y, master->data.f_int);
			x++;
		}
		x = 0;
		y++;
	}
}

void	draw_block(t_master *master, t_img *img, t_minimap_coords coords)
{
	t_block	block;

	if (master->data.map[coords.j][coords.i] == '1')
		block.color = 0xD18700;
	else
		block.color = 0x00A300;
	block.end_x = coords.x + coords.block;
	block.end_y = coords.y + coords.block;
	block.og_x = coords.x;
	block.og_y = coords.y;
	while (coords.y <= block.end_y)
	{
		while (coords.x <= block.end_x)
		{
			if (coords.x == block.og_x || coords.x == block.end_x || \
			coords.y == block.end_y || coords.y == block.og_y)
				my_mlx_pixel_put(img, coords.x, coords.y, 0xFFFFFF);
			else
				my_mlx_pixel_put(img, coords.x, coords.y, block.color);
			coords.x++;
		}
		coords.x = block.og_x;
		coords.y++;
	}
}
