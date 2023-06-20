/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 10:04:37 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/06/20 12:31:08 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	texture_rights_checker(t_data *data)
{
	int	i;
	int	fd;

	i = 0;
	while (data->wall[i])
	{
		fd = open(data->wall[i], O_RDONLY);
		if (fd == -1)
		{
			if (data && data->map)
				free_char_arr(data->map);
			if (data && data->wall)
				free_char_arr(data->wall);
			ft_putstr_fd("Error\n", 2);
			perror("Error opening wall texture");
			ft_putstr_fd("Please fix path/rights\n", 2);
			exit(1);
		}
		close(fd);
		i++;
	}
}

void	map_element_checker(t_data *data)
{
	int	i;
	int	j;
	int	player;

	i = 0;
	j = 0;
	player = 0;
	while (data->map[j])
	{
		while (data->map[j][i])
		{
			if (player_check(data->map[j][i]) == 0)
				player++;
			if (is_it_a_valid_element(data->map[j][i]) == 0)
				i++;
			else
				free_data_closed_fd(data, "Invalid map element!\n");
		}
		i = 0;
		j++;
	}
	if (player != 1)
		free_data_closed_fd(data, "Provide one (1) spawn point (N/S/E/W)\n");
}

void	check_surrounding_walls(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (check_first_or_last_row(data->map[0]))
		free_data_closed_fd(data, "Unclosed map!\n");
	while (data->map[j] && data->map[j + 1])
	{
		while (data->map[j][i])
		{
			if ((data->map[j][i] == '0' || !player_check(data->map[j][i])) \
			&& check_valid_surroundings(data->map, i, j) == 1)
				free_data_closed_fd(data, "Unclosed map!\n");
			i++;
		}
		i = 0;
		j++;
	}
	if (check_first_or_last_row(data->map[j]))
		free_data_closed_fd(data, "Unclosed map!\n");
}

void	map_validator(t_data *data)
{
	texture_rights_checker(data);
	map_element_checker(data);
	if (is_map_connected(data) == 0)
	{
		free_data_closed_fd(data, "Map not connected\n");
		exit(1);
	}
	check_surrounding_walls(data);
}
