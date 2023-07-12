/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   flood.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:30:28 by jaurasma          #+#    #+#             */
/*   Updated: 2023/07/12 11:55:51 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_connect(t_flood *f, t_data *data)
{
	f->start_row = -1;
	f->start_col = -1;
	f->i = 0;
	f->j = 0;
	f->visited = ft_calloc(data->mapsize[1], sizeof(int *));
	if (f->visited == NULL)
		free_data_closed_fd(data, "Malloc failed!\n");
	while (f->i < data->mapsize[1])
	{
		f->visited[f->i] = ft_calloc(ft_strlen(data->map[f->i]), sizeof(int));
		if (f->visited[f->i] == NULL)
		{
			while (--f->i >= 0)
				free(f->visited[f->i]);
			free(f->visited);
			free_data_closed_fd(data, "Malloc failed!\n");
		}
		f->i++;
	}
	f->i = 0;
}

void	connect_starpoint(t_flood *f, t_data *d)
{
	while (f->i < d->mapsize[1])
	{
		f->j = 0;
		while (f->j < d->mapsize[0])
		{
			if (d->map[f->i][f->j] == '1' || d->map[f->i][f->j] == '0' ||
				d->map[f->i][f->j] == 'E' || d->map[f->i][f->j] == 'W' ||
				d->map[f->i][f->j] == 'S' || d->map[f->i][f->j] == 'N')
			{
				f->start_row = f->i;
				f->start_col = f->j;
				break ;
			}
			f->j++;
		}
		if (f->start_row != -1 && f->start_col != -1)
			break ;
		f->i++;
	}
	f->i = 0;
}

int	connect_map(t_flood *f, t_data *d)
{
	while (f->i < d->mapsize[1])
	{
		f->j = 0;
		while ((size_t)f->j < ft_strlen(d->map[f->i]))
		{
			if ((d->map[f->i][f->j] == '1' || d->map[f->i][f->j] == '0' || \
				d->map[f->i][f->j] == 'E' || d->map[f->i][f->j] == 'W' || \
				d->map[f->i][f->j] == 'S' || d->map[f->i][f->j] == 'N') && \
				!f->visited[f->i][f->j])
			{
				f->j = 0;
				while (f->j < d->mapsize[1])
				{
					free(f->visited[f->j]);
					f->j++;
				}
				free(f->visited);
				return (0);
			}
			f->j++;
		}
		f->i++;
	}
	f->i = 0;
	return (1);
}

void	flood_fill(t_data *data, int row, int col, t_flood *f)
{
	if (row < 0 || row >= data->mapsize[1] || \
	col < 0 || col >= data->mapsize[0])
		return ;
	if (data->map[row][col] != '0' && data->map[row][col] != '1' \
	&& data->map[row][col] != 'E' && data->map[row][col] != 'W' \
	&& data->map[row][col] != 'S' && data->map[row][col] != 'N')
		return ;
	if (f->visited[row][col] != 0)
		return ;
	f->visited[row][col] = 1;
	flood_fill(data, row - 1, col, f);
	flood_fill(data, row + 1, col, f);
	flood_fill(data, row, col - 1, f);
	flood_fill(data, row, col + 1, f);
}

int	is_map_connected(t_data *data)
{
	t_flood	f;

	init_connect(&f, data);
	connect_starpoint(&f, data);
	if (f.start_row == -1 || f.start_col == -1)
	{
		while (f.i < data->mapsize[1])
		{
			free(f.visited[f.i]);
			f.i++;
		}
		free(f.visited);
		return (0);
	}
	flood_fill(data, f.start_row, f.start_col, &f);
	f.i = 0;
	if (connect_map(&f, data) == 0)
		return (0);
	while (f.i < data->mapsize[1])
	{
		free(f.visited[f.i]);
		f.i++;
	}
	free(f.visited);
	return (1);
}
