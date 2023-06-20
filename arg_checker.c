/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_checker.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 10:03:28 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/06/20 11:08:13 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	get_fd(char *map)
{
	int	fd;

	fd = open(map, O_RDONLY);
	if (fd == -1)
	{
		ft_putstr_fd("Error\n", 2);
		printf("Please fix path/rights & thank you for your patience! :)\n");
		exit(1);
	}
	return (fd);
}

int	is_it_whitespace(char c)
{
	if (c == 9 || c == 10 || c == 11 || c == 12 || c == 13 || c == 32)
		return (1);
	else
		return (0);
}

int	are_there_any_whitespaces(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (is_it_whitespace(str[i]) == 1)
			return (1);
		i++;
	}
	return (0);
}

void	arg_checker(int ac, char **av)
{
	int	arglen;

	if (ac != 2)
	{
		ft_putstr_fd("Error\n", 2);
		exitmsg("Please give one (1) argument. (path to '.cub' file)\n");
	}
	arglen = ft_strlen(av[1]);
	if (arglen <= 4)
	{
		ft_putstr_fd("Error\n", 2);
		exitmsg("Please give a valid map. (ex. './maps/maze.cub')\n");
	}
	else if (are_there_any_whitespaces(av[1]) == 1)
	{
		ft_putstr_fd("Error\n", 2);
		exitmsg("What are you trying to do?\n");
	}
	else if (ft_strncmp(&av[1][arglen - 4], ".cub", 4) != 0)
	{
		ft_putstr_fd("Error\n", 2);
		exitmsg("Please give a valid map. (ex. './maps/maze.cub')\n");
	}
}
