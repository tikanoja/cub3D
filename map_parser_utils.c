/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:46:57 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/06/20 14:47:11 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*trim_direction(char *direction)
{
	int	i;

	i = 0;
	direction = direction + 2;
	while (is_it_whitespace(*direction) == 1)
		direction++;
	while (direction[i] && direction[i] != '\n')
		i++;
	if (direction[i] && direction[i] == '\n')
		direction [i] = '\0';
	return (direction);
}

int	dupcheck(char *wall, char *line, t_data *data)
{
	if (wall)
	{
		free(line);
		ft_putstr_fd("Error\n", 2);
		free_data(data, "Duplicate point of compass!\n");
	}
	return (0);
}

int	change_happened(int *happened)
{
	(*happened) = 1;
	return (1);
}

int	free_save_ret_happened(char *save, int happened)
{
	free(save);
	return (happened);
}

int	check_for_direction(t_data *data, char *line)
{
	char	*save;
	int		happened;

	happened = 0;
	save = ft_strdup(line);
	if (save == NULL)
	{
		free(line);
		free_data(data, "Malloc failed\n");
	}
	while (is_it_whitespace(*save) == 1)
		save++;
	if (ft_strncmp(line, "NO", 2) == 0 && \
	!dupcheck(data->wall[0], line, data) && change_happened(&happened))
		data->wall[0] = ft_strdup(trim_direction(save));
	else if (ft_strncmp(line, "EA", 2) == 0 && \
	!dupcheck(data->wall[1], line, data) && change_happened(&happened))
		data->wall[1] = ft_strdup(trim_direction(save));
	else if (ft_strncmp(line, "SO", 2) == 0 && \
	!dupcheck(data->wall[2], line, data) && change_happened(&happened))
		data->wall[2] = ft_strdup(trim_direction(save));
	else if (ft_strncmp(line, "WE", 2) == 0 && \
	!dupcheck(data->wall[3], line, data) && change_happened(&happened))
		data->wall[3] = ft_strdup(trim_direction(save));
	return (free_save_ret_happened(save, happened));
}
