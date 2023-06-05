/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:26:54 by jaurasma          #+#    #+#             */
/*   Updated: 2023/06/05 16:33:34 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	fill_to_struct(t_data *data, char *line, int status)
{
	// // static int filling_stage;

	// // if (status != 0)
	// //     filling_stage = status;
	// // while(is_it)
	// if (status == 0)
	// 	//check_for_ilmasnuunta
	// else if (status == 1)
	// 	//ceck_for_colors
	// else if (status == 2)
	// 	//fill map
	return  ;
}

int	check_status(t_data *data)
{
	static int	status;
	int			i;

	i = 0;
	if (status == 0)
	{
		while (i < 4)
		{
			if (data->wall[i] == NULL)
				return (status);
			i++;
		}
		status = 1;
		return (1);
	}
	if (status == 1)
	{
		if (!data->floor[0] || !data->sky[0])
			return (status);
		status = 2;
		return (status);
	}
	return (status);
}


void	map_parser(t_data *data)
{
	char	*line;
	int		status;

	line = NULL;
	status = 0;
	data->wall = malloc(sizeof(char *) * 5);
	if (data->wall == NULL)
		free_data(data, "Malloc failed!\n");
	data->wall[4] = NULL;
	line = get_next_line(data->fd);
	if (line == NULL)
		free_data(data, "Malloc failed!\n");
	while (line != NULL)
	{
		printf("%s\n", line);
		status = check_status(data);
		fill_to_struct(data, line, status);
		free(line);
		line = get_next_line(data->fd);
		if (line == NULL)
			free_data(data, "Malloc failed!\n");
	}
	close(data->fd);
}
