/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 10:05:27 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/06/20 10:05:29 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	get_angle(t_master *master, char c)
{
	if (c == 'S')
		master->player.angle = M_PI / 2;
	else if (c == 'E')
		master->player.angle = 0.0;
	else if (c == 'N')
		master->player.angle = 3 * M_PI / 2;
	else if (c == 'W')
		master->player.angle = M_PI;
}

void	get_player_coords(t_master *m)
{
	char	*poc;
	int		i;
	int		flag;

	init_get_player_coords(&flag, &i, m);
	poc = "NEWS\0";
	while (m->data.map[(int)m->player.y] && flag == 0)
	{
		m->player.x = 0;
		while (m->data.map[(int)m->player.y][(int)m->player.x] && flag == 0)
		{
			while (poc[i] && flag == 0)
			{
				if (m->data.map[(int)m->player.y][(int)m->player.x] == poc[i])
					flag = 1;
				i++;
			}
			i = 0;
			m->player.x++;
		}
		m->player.y++;
	}
	get_angle(m, m->data.map[(int)m->player.y - 1][(int)m->player.x - 1]);
	m->player.y = (m->player.y - 1) * m->minimap.block + m->minimap.block / 2;
	m->player.x = (m->player.x - 1) * m->minimap.block + m->minimap.block / 2;
}

void	draw_direction_arrow(t_master *master, t_img *img)
{
	t_player	coords;

	coords.x = master->player.x - 1;
	coords.y = master->player.y;
	coords.endx = coords.x + 1 + 8 * cos(master->player.angle);
	coords.endy = coords.y + 8 * sin(master->player.angle);
	drawl(img, &coords, 0x000000);
	coords.x = master->player.x;
	coords.y = master->player.y;
	coords.endx = coords.x + 8 * cos(master->player.angle);
	coords.endy = coords.y + 8 * sin(master->player.angle);
	drawl(img, &coords, 0x000000);
	coords.x = master->player.x + 1;
	coords.y = master->player.y;
	coords.endx = coords.x - 1 + 8 * cos(master->player.angle);
	coords.endy = coords.y + 8 * sin(master->player.angle);
	drawl(img, &coords, 0x000000);
	coords.x = master->player.x + 2;
	coords.y = master->player.y;
	coords.endx = coords.x - 2 + 8 * cos(master->player.angle);
	coords.endy = coords.y + 8 * sin(master->player.angle);
	drawl(img, &coords, 0x000000);
}

void	draw_player(t_master *master, t_img *img)
{
	int			start_y;
	int			end_y;
	int			start_x;
	int			end_x;
	static int	flag;

	if (flag == 0)
	{
		get_player_coords(master);
		flag = 1;
	}
	init_draw_player(&start_y, &start_x, master);
	end_y = start_y + 5;
	end_x = start_x + 5;
	while (start_y <= end_y)
	{
		while (start_x <= end_x)
		{
			my_mlx_pixel_put(img, start_x, start_y, 0x000000);
			start_x++;
		}
		start_x = end_x - 5;
		start_y++;
	}
	draw_direction_arrow(master, img);
}

void	draw_minimap(t_master *master, t_img *img)
{
	t_minimap_coords	coords;
	int					og_x;

	init_minimap_coords(&coords, master);
	og_x = coords.x;
	while (master->data.map[coords.j])
	{
		while (master->data.map[coords.j][coords.i])
		{
			if (master->data.map[coords.j][coords.i] != 32)
				draw_block(master, img, coords);
			coords.i++;
			coords.x = coords.i * coords.block;
		}
		coords.i = 0;
		coords.x = og_x;
		coords.j++;
		coords.y = coords.j * coords.block;
	}
	master->minimap = coords;
	draw_player(master, img);
}
