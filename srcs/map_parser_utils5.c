/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils5.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/12 17:52:02 by jaurasma          #+#    #+#             */
/*   Updated: 2023/07/12 18:06:45 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	free_save_ret_happened(char *save, int happened, int save_pointer_index)
{
	save -= save_pointer_index;
	free(save);
	return (happened);
}

void	fill_wall_elements(char **wall, char *save, t_data *data, char *line)
{
	*wall = ft_strdup(trim_direction(save));
	if (*wall == NULL)
	{
		free(line);
		free_data(data, "Wall element malloc failed!\n");
	}
}
