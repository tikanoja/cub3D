/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 14:49:26 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/06/20 14:49:38 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

void	split_colors(char **temp, int *data)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		data[i] = ft_atoi(temp[i]);
		free(temp[i]);
		i++;
	}
}

void	free_color_args(char **temp, t_data *data)
{
	free_char_arr(temp);
	ft_putstr_fd("Error\n", 2);
	free_data(data, "Wrong color argument!\n");
}

int	check_for_num(char c)
{
	if (c < 48 || c > 57)
		return (1);
	return (0);
}

int	check_for_correct_number(char *num)
{
	int	i;

	i = 0;
	if (ft_strlen(num) > 3)
		return (1);
	while (num[i])
	{
		if (num[i] == '\0')
			break ;
		if (check_for_num(num[i]) == 1)
			return (1);
		i++;
	}
	if (ft_atoi(num) < 0 || ft_atoi(num) > 255)
		return (1);
	return (0);
}

void	check_for_color_argument(char **temp, t_data *data)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		if (i > 3)
			free_color_args(temp, data);
		else if (check_for_correct_number(temp[i]) == 1)
			free_color_args(temp, data);
		i++;
	}
}
