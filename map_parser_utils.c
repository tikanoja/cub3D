/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuukka <tuukka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:46:57 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/06/21 12:04:18 by tuukka           ###   ########.fr       */
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
	while (direction[i] && direction[i] != '\n' && \
	!is_it_whitespace(direction[i]))
		i++;
	if (direction[i] && (direction[i] == '\n' \
	|| is_it_whitespace(direction[i])))
		direction [i] = '\0';
	return (direction);
}

int	dupcheck(char *wall, char *line, t_data *data)
{
	if (wall)
	{
		free_data(data, "Duplicate point of compass!\n");
		free(line);
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

int    check_for_direction(t_data *data, char *line)
{
    char    	*save;
    int        happened;
    int        save_pointer_index;

    happened = 0;
    save_pointer_index = 0;
    save = ft_strdup(line);
    if (save == NULL)
    {
        free(line);
        free_data(data, "Malloc failed\n");
    }
    while (is_it_whitespace(*save) == 1)
    {
        save++;
        save_pointer_index++;
    }
    if (ft_strncmp(save, "NO", 2) == 0 && \
    !dupcheck(data->wall[0], save, data) && change_happened(&happened))
        data->wall[0] = ft_strdup(trim_direction(save));
    else if (ft_strncmp(save, "EA", 2) == 0 && \
    !dupcheck(data->wall[1], save, data) && change_happened(&happened))
        data->wall[1] = ft_strdup(trim_direction(save));
    else if (ft_strncmp(save, "SO", 2) == 0 && \
    !dupcheck(data->wall[2], save, data) && change_happened(&happened))
        data->wall[2] = ft_strdup(trim_direction(save));
    else if (ft_strncmp(save, "WE", 2) == 0 && \
    !dupcheck(data->wall[3], save, data) && change_happened(&happened))
        data->wall[3] = ft_strdup(trim_direction(save));
    save -= save_pointer_index;
    return (free_save_ret_happened(save, happened));
}
