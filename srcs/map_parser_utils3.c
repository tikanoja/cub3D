/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tuukka <tuukka@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:49:49 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/06/21 11:58:47 by tuukka           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	trim_colors(char **color)
{
	int	start;
	int	end;
	int	index;
	int	i;

	index = 0;
	while (color[index])
	{
		i = 0;
		start = 0;
		end = ft_strlen(color[index]) - 1;
		while (color[index][start] && is_it_whitespace(color[index][start]))
			start++;
		while (color[index][end] && is_it_whitespace(color[index][end]))
			end--;
		while (start <= end)
		{
			color[index][i] = color[index][start];
			i++;
			start++;
		}
		color[index][i] = '\0';
		index++;
	}
}

void	trim_and_split_color(t_data *data, char *color, int flag)
{
	char	**temp;

	color = color + 1;
	while (is_it_whitespace(*color) == 1)
		color++;
	temp = ft_split(color, ',');
	if (temp == NULL)
	{
		free(color);
		free_data(data, "Malloc failed!\n");
	}
	if (temp[2])
		temp[2][ft_strlen(temp[2]) - 1] = '\0';
	trim_colors(temp);
	check_for_color_argument(temp, data);
	if (flag == 1)
		split_colors(temp, data->floor, data);
	else
		split_colors(temp, data->sky, data);
	free(temp);
}

int	check_for_color(t_data *data, char *line)
{
	char	*save;

	save = ft_strdup(line);
	if (save == NULL)
	{
		free(line);
		free_data(data, "Malloc failed\n");
	}
	while (is_it_whitespace(*save) == 1)
		save++;
	if (ft_strncmp(line, "F", 1) == 0)
	{
		trim_and_split_color(data, save, 1);
		free(save);
		return (1);
	}
	else if (ft_strncmp(line, "C", 1) == 0)
	{
		trim_and_split_color(data, save, 2);
		free(save);
		return (1);
	}
	free(save);
	return (0);
}

int	check_if_filled(t_data *data, int hap)
{
	int	i;

	i = 0;
	while (data->wall[i])
		i++;
	if (data->floor[0] != -1 && data->sky[0] != -1 && i == 4)
		return (1);
	else if (hap == 0)
		return (-1);
	else
		return (0);
}

int	fill_to_struct(t_data *data, char *line)
{
	static int	status;
	int			happened;

	happened = 0;
	if (status == 0)
	{
		happened += check_for_direction(data, line);
		if (happened == 0)
			happened += check_for_color(data, line);
		status = check_if_filled(data, happened);
	}
	if (status == -1)
	{
		free(line);
		free_data(data, "Nonsense values / missing color or texture\n");
	}
	return (status);
}
