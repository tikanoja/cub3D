/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validator.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 10:04:37 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/06/20 10:05:04 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"
#include <stdbool.h>

void    texture_rights_checker(t_data *data)
{
	int i;
	int fd;

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
			ft_putstr_fd("Please fix path/rights & thank you for your patience! :)\n", 2);
			exit(1);
		}
		close(fd);
		i++;
	}
}

void    map_element_checker(t_data *data)
{
	int i;
	int j;
	int player;

	i = 0;
	j = 0;
	player = 0;
	while(data->map[j])
	{
		while(data->map[j][i])
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
		free_data_closed_fd(data, "Please provide one (1) spawn point. (N/S/E/W)\n");
}

void    check_surrounding_walls(t_data *data)
{
	int i;
	int j;

	i = 0;
	j = 1;
	if (check_first_or_last_row(data->map[0]))
		free_data_closed_fd(data, "Unclosed map!\n");
	while(data->map[j] && data->map[j + 1])
	{
		while(data->map[j][i])
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
void flood_fill(char **map, int row, int col, int **visited, int numRows, int numCols)
{
	if (row < 0 || row >= numRows || col < 0 || col >= numCols)
		return ;
	if (map[row][col] != '0' && map[row][col] != '1' && map[row][col] != 'E' && map[row][col] != 'W' && map[row][col] != 'S' && map[row][col] != 'N')
		return ;
	if (visited[row][col] != 0)
		return ;
	visited[row][col] = 1;
	flood_fill(map, row - 1, col, visited, numRows, numCols); // Up
	flood_fill(map, row + 1, col, visited, numRows, numCols); // Down
	flood_fill(map, row, col - 1, visited, numRows, numCols); // Left
	flood_fill(map, row, col + 1, visited, numRows, numCols); // Right
}


int is_map_connected(t_data *data)
{
	// Create a visited matrix to track visited cells
	int start_row = -1;
	int start_col = -1;
	int i;
	int j;
	int **visited;

	start_row = -1;
	start_col = -1;
	i = 0;
	j = 0;
	visited = ft_calloc(data->mapsize[1], sizeof(int *));
	if (visited == NULL)
		free_data_closed_fd(data, "Malloc failed!\n");
	while(i < data->mapsize[1])
	{
		visited[i] = ft_calloc(data->mapsize[0], sizeof(int)); // number of columns
		if (visited[i] == NULL)
		{
			while (--i >= 0)
				free(visited[i]);
			free(visited);
			free_data_closed_fd(data, "Malloc failed!\n");
		}
		i++;
	}
	i = 0;
	while (i < data->mapsize[1])
	{
		j = 0;
		while (j < data->mapsize[0])
		{
			if (data->map[i][j] == '1' || data->map[i][j] == '0' ||
				data->map[i][j] == 'E' || data->map[i][j] == 'W' ||
				data->map[i][j] == 'S' || data->map[i][j] == 'N')
			{
				start_row = i;
				start_col = j;
				break ;
			}
			j++;
		}
		if (start_row != -1 && start_col != -1)
			break ;
		i++;
	}
	i = 0;
	if (start_row == -1 || start_col == -1)
	{
		while(i < data->mapsize[1])
		{
			free(visited[i]);
			i++;
		}
		free(visited);
		return (0);
	}
	flood_fill(data->map, start_row, start_col, visited, data->mapsize[1], data->mapsize[0]);
	i = 0;
	while (i < data->mapsize[1])
	{
		j = 0;
		while ((size_t)j < ft_strlen(data->map[i]))
		{
			if ((data->map[i][j] == '1' || data->map[i][j] == '0' || \
				 data->map[i][j] == 'E' || data->map[i][j] == 'W' || \
				 data->map[i][j] == 'S' || data->map[i][j] == 'N') && \
				!visited[i][j])
			{
				j = 0;
			   while (j < data->mapsize[1])
			   {
					free(visited[j]);
					j++;
			   }
				free(visited);
				return (0);
			}
			j++;
		}
		i++;
	}

	i = 0;
	while(i < data->mapsize[1])
	{
		free(visited[i]);
		i++;
	}
	free(visited);
	return (1);
}


void map_validator(t_data *data)
{
	texture_rights_checker(data);
	map_element_checker(data);
	if(is_map_connected(data) == 0)
	{
		free_data_closed_fd(data, "Map not connected\n");
		exit(1);
	}
	check_surrounding_walls(data);
}
