/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:55:34 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/06/20 14:55:47 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	init_map_parser(int *flag, char **line, char **map)
{
	*flag = 0;
	*line = NULL;
	*map = NULL;
}

int	rgb_to_int(int rgb[3])
{
	int	combinedvalue;

	combinedvalue = rgb[0] * 65536 + rgb[1] * 256 + rgb[2];
	return (combinedvalue);
}

void	check_double_map(t_data *data, char *line)
{
	while (line != NULL)
	{
		if (*line != '\n' && *line != ' ')
			free_data(data, "Double map!\n");
		free(line);
		line = get_next_line(data->fd);
	}
}

void	init_parsing(t_data *data)
{
	data->wall[0] = NULL;
	data->wall[1] = NULL;
	data->wall[2] = NULL;
	data->wall[3] = NULL;
	data->wall[4] = NULL;
	data->floor[0] = -1;
	data->floor[1] = -1;
	data->floor[2] = -1;
	data->sky[0] = -1;
	data->sky[1] = -1;
	data->sky[2] = -1;
}

int	check_empty_line(char *line)
{
	int	i;

	i = 0;
	while (line[i])
	{
		if (is_it_whitespace(line[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
