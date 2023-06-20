/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 10:05:18 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/06/20 11:02:33 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	is_it_a_valid_element(char c)
{
	if (c == '0' || c == '1' || c == 'N' || c == 'S' || c == 'E' || c == 'W' \
		|| c == ' ')
		return (0);
	else
		return (1);
}

int	player_check(char c)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		return (0);
	else
		return (1);
}

int	check_first_or_last_row(char *row)
{
	int	i;

	i = 0;
	while (row[i])
	{
		if (row[i] == ' ' || row[i] == '1')
			i++;
		else
			return (1);
	}
	return (0);
}

int	check_valid_surroundings(char **map, int i, int j)
{
	if (i == 0 || map[j][i + 1] == '\0')
		return (1);
	else if (i >= (int)ft_strlen(map[j - 1]) || i >= (int)ft_strlen(map[j + 1]))
		return (1);
	else if (map[j - 1][i] == ' ' || map[j + 1][i] == ' ')
		return (1);
	else if (map[j][i - 1] == ' ' || map[j][i + 1] == ' ')
		return (1);
	else
		return (0);
}
