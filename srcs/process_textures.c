/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_textures.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 10:05:38 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/06/20 10:59:49 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

t_texture	load_image(t_master *master, char *path, t_img *i)
{
	int			y;
	int			x;
	t_texture	txt;

	y = 0;
	x = 0;
	i->img = mlx_xpm_file_to_image(master->mlx.mlx_ptr, path, \
	&i->img_width, &i->img_height);
	i->data = (int *)mlx_get_data_addr(i->img, &i->bpp, \
	&i->llen, &i->en);
	txt.array = malloc(sizeof(int *) * (i->img_height * i->img_width));
	while (y < i->img_height)
	{
		x = 0;
		while (x < i->img_width)
		{
			txt.array[i->img_width * y + x] = i->data[i->img_width * y + x];
			x++;
		}
		y++;
	}
	txt.width = i->img_width;
	txt.height = i->img_height;
	mlx_destroy_image(master->mlx.mlx_ptr, i->img);
	return (txt);
}

void	texture_extension_check(t_master *master)
{
	int	str_end;
	int	i;

	i = 0;
	while (i < 4)
	{
		str_end = ft_strlen(master->data.wall[i]);
		str_end = str_end - 4;
		if (ft_strncmp(&master->data.wall[i][str_end], ".xpm", 4))
			free_data_closed_fd(&master->data, \
			"Please provide textures in .xpm\n");
		i++;
	}
}

void	free_textures(t_master *master, int flag)
{
	if (flag == 1)
		free(master->data.north.array);
	else if (flag == 2)
	{
		free(master->data.north.array);
		free(master->data.east.array);
	}
	else if (flag == 3)
	{
		free(master->data.north.array);
		free(master->data.east.array);
		free(master->data.west.array);
	}
	else if (flag == 4)
	{
		free(master->data.north.array);
		free(master->data.south.array);
		free(master->data.east.array);
		free(master->data.west.array);
	}
	if (flag != 4)
		free_data_closed_fd(&master->data, "Malloc failed!\n");
}

void	process_textures(t_master *master)
{
	t_img	img;

	texture_extension_check(master);
	master->data.north = load_image(master, master->data.wall[0], &img);
	if (master->data.north.array == NULL)
		free_data_closed_fd(&master->data, "Malloc failed!\n");
	master->data.east = load_image(master, master->data.wall[1], &img);
	if (master->data.east.array == NULL)
		free_textures(master, 1);
	master->data.south = load_image(master, master->data.wall[2], &img);
	if (master->data.south.array == NULL)
		free_textures(master, 2);
	master->data.west = load_image(master, master->data.wall[3], &img);
	if (master->data.west.array == NULL)
		free_textures(master, 3);
}
