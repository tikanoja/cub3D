/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:26:54 by jaurasma          #+#    #+#             */
/*   Updated: 2023/06/06 18:28:23 by jaurasma         ###   ########.fr       */
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
	if (ft_strncmp(line , "NO", 2) == 0 && !dupcheck(data->wall[0], line, data) \
	&& change_happened(&happened))
		data->wall[0] = ft_strdup(trim_direction(save));
	else if (ft_strncmp(line , "EA", 2) == 0 && !dupcheck(data->wall[1], line, data) \
	&& change_happened(&happened))
		data->wall[1] = ft_strdup(trim_direction(save));
	else if (ft_strncmp(line , "SO", 2) == 0 && !dupcheck(data->wall[2], line, data) \
	&& change_happened(&happened))
		data->wall[2] = ft_strdup(trim_direction(save));
	else if (ft_strncmp(line , "WE", 2) == 0 && !dupcheck(data->wall[3], line, data) \
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
void free_color_args(char **temp, t_data *data)
{
	free_char_arr(temp);
	// if (color)
	// 	free(color);
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
	if (temp[2])
		temp[2][ft_strlen(temp[2]) - 1] = '\0'; 
	check_for_color_argument(temp, data);
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
	if (ft_strncmp(line , "F", 1) == 0)
	{
		trim_and_split_color(data, save, 1);
		free(save);
		return (1);
	}
	else if (ft_strncmp(line , "C", 1) == 0)
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
		free_data(data, "Garbage values\n");
	}
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
void init_parsing(t_data *data)
{
	data->wall[0] = NULL;
	data->wall[1] = NULL;
	data->wall[2] = NULL;
	data->wall[3] = NULL;
	data->wall[4] = NULL;
	data->floor[0] = -1;
	data->floor[1] = -1;
	data->floor[2] = -1;
	data->sky[0] = -1;
	data->sky[1] = -1;
	data->sky[2] = -1;
}
int rgb_to_int(int rgb[3]) 
{
    int combinedValue;
    
	combinedValue = rgb[0] * 65536 + rgb[1] * 256 + rgb[2];
	return (combinedValue);
}

void	map_parser(t_data *data)
{
	char	*line;
	char	*map;
	int		filled;

	filled = 0;
	line = NULL;
	map = NULL;
	data->map = NULL;
	data->wall = malloc(sizeof(char *) * 5);
	if (data->wall == NULL)
		free_data(data, "Malloc failed!\n");
	line = get_next_line(data->fd);
	if (line == NULL)
		free_data(data, "Malloc failed!\n");
	init_parsing(data);
	while (line != NULL)
	{
		if (check_empty_line(line) != 1 && filled == 0)
			filled = fill_to_struct(data, line);
		else if (check_empty_line(line) != 1 && filled == 1)
			map = ft_strjoin_map(map, line);
		free(line);
		line = get_next_line(data->fd);
	}
	close(data->fd);
	data->map = ft_split(map, '\n');
	free(map);
	if (data->map == NULL)
		free_data(data, "Malloc failed!\n");
	data->f_int = rgb_to_int(data->floor);
	data->s_int = rgb_to_int(data->sky);	
}
