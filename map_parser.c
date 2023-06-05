/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:26:54 by jaurasma          #+#    #+#             */
/*   Updated: 2023/06/05 18:51:36 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

char	*trim_direction(char *direction)
{
	direction = direction + 2;
	while(is_it_whitespace(*direction) == 1)
		direction++;
	return (direction);
}

int		dupcheck(char *wall, char *line, t_data *data)
{
	if (wall)
	{
		free(line);
		free_data(data, "Duplicate point of compass!\n");
	}
	return (0);
}

int	change_happened(int *happened)
{
	(*happened) = 1;
	return (1);
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
	while(is_it_whitespace(*save) == 1)
		save++;
	if (strncmp(line , "NO", 3) && !dupcheck(data->wall[0], line, data) \
	&& change_happened(&happened))
		data->wall[0] = ft_strdup(trim_direction(save));
	else if (strncmp(line , "EA", 3) && !dupcheck(data->wall[1], line, data) \
	&& change_happened(&happened))
		data->wall[1] = ft_strdup(trim_direction(save));
	else if (strncmp(line , "SO", 3) && !dupcheck(data->wall[2], line, data) \
	&& change_happened(&happened))
		data->wall[2] = ft_strdup(trim_direction(save));
	else if (strncmp(line , "WE", 3) && !dupcheck(data->wall[3], line, data) \
	&& change_happened(&happened))
		data->wall[3] = ft_strdup(trim_direction(save));
	free(save);
	return (happened);
}

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
void free_color_args(char **temp, t_data *data, char *color)
{
	free_char_arr(temp);
	free(color);
	free_data(data, "Wrong color argument!\n");
}

int check_for_num(char c)
{
	if (c < 48 || c > 57)
		return (1);
	return (0);
}

int check_for_correct_number(char *num)
{
	int	i;

	i = 0;
	if (ft_strlen(num) > 3)
		return (1);
	while(num[i])
	{
		if (check_for_num(num[i]) == 1)
			return (1);
		i++;
	}
	if (ft_atoi(num) < 0 || ft_atoi(num) > 255)
	 	return (1);
	return (0);
}

void	check_for_color_argument(char **temp, t_data *data, char *color)
{
	int	i;

	i = 0;
	while (temp[i])
	{
		if (i > 3)
			free_color_args(temp, data, color);
		else if (check_for_correct_number(temp[i]) == 1)
			free_color_args(temp, data, color);
		i++;
	}
}
void	trim_and_split_color(t_data *data, char *color, int flag)
{
	char	**temp;
	int		i;
	
	color = color + 1;
	i = 0;
	while(is_it_whitespace(*color) == 1)
		color++;
	temp = ft_split(color, ',');
	if (temp == NULL)
	{
		free(color);
		free_data(data, "Malloc failed!\n");
	}
	while(temp[i])
		i++;
	check_for_color_argument(temp, data, color);
	if (flag == 1)
		split_colors(temp, data->floor);
	else
		split_colors(temp, data->sky);
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
	if (strncmp(line , "F", 3))
	{
		trim_and_split_color(data, save, 1);
		free(save);
		return (1);
	}
	else if (strncmp(line , "C", 3))
	{
		trim_and_split_color(data, save, 2);
		free(save);
		return (1);
	}
	free(save);
	return (0);
}

int check_if_filled(t_data *data, int hap)
{
	int i;
	
	i = 0;
	while (data->wall[i])
		i++;
	if (data->floor[0] && data->sky[0] && i == 3)
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
		happened += check_for_color(data, line);
		status = check_if_filled(data, happened);
	}
	if (status == -1)
	{
		free(line);
		free_data(data, "Garbage values\n");
	}
	// else
	// 	fill_map(data, line);
	return (status);
}

int check_empty_line(char *line)
{
	int i;
	
	i = 0;
	while (line[i])
	{
		if (is_it_whitespace(line[i]) == 0)
			return (0);
		i++;
	}
	return (1);
}
char	*ft_strjoin_map(char *s1, char *s2)
{
	char	*ns;
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (s2 == NULL)
		return (s1);
	if (s1 == NULL)
		return (ft_strdup(s2));
	ns = ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!ns)
		return (NULL);
	while (s1[i])
		ns[j++] = s1[i++];
	i = 0;
	while (s2[i])
		ns[j++] = s2[i++];
	free(s1);
	ns[j] = '\0';
	return (ns);
}


void	map_parser(t_data *data)
{
	char	*line;
	char	*map;
	int		filled;

	filled = 0;
	line = NULL;
	map = NULL;
	data->wall = malloc(sizeof(char *) * 5);
	if (data->wall == NULL)
		free_data(data, "Malloc failed!\n");
	data->wall[4] = NULL;
	line = get_next_line(data->fd);
	if (line == NULL)
		free_data(data, "Malloc failed!\n");
	while (line != NULL)
	{
		if (check_empty_line(line) != 1 && filled == 0)
			filled = fill_to_struct(data, line);
		else if (check_empty_line(line) != 1 && filled == 1)
			map = ft_strjoin_map(map, line);
		printf("%s\n", line);
		free(line);
		line = get_next_line(data->fd);
	}
	close(data->fd);
	data->map = ft_split(map, '\n');
	free(map);
	if (data->map == NULL)
		free_data(data, "Malloc failed!\n");
}
