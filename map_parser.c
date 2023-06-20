/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaurasma <jaurasma@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/05 16:26:54 by jaurasma          #+#    #+#             */
/*   Updated: 2023/06/20 11:20:57 by jaurasma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

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

void	parsing_loop(char *line, char **map, int flag, t_data *data)
{
	int	filled;

	filled = 0;
	while (line != NULL)
	{
		if (*map && ft_strchr(*map, '1'))
			flag = 1;
		if (*line == '\n' && flag == 1)
		{
			check_double_map(data, line);
			break ;
		}
		if (check_empty_line(line) != 1 && filled == 0)
			filled = fill_to_struct(data, line);
		else if (filled == 1)
		{
			*map = ft_strjoin_map(*map, line);
			if (*map == NULL)
				free_data(data, "Malloc failed!\n");
		}
		free(line);
		line = get_next_line(data->fd);
	}
}

void	map_parser(t_data *data)
{
	char	*line;
	char	*map;
	int		flag;

	init_map_parser(&flag, &line, &map);
	data->map = NULL;
	data->wall = malloc(sizeof(char *) * 5);
	if (data->wall == NULL)
		free_data(data, "Malloc failed!\n");
	line = get_next_line(data->fd);
	if (line == NULL)
		free_data(data, "Malloc failed!\n");
	init_parsing(data);
	parsing_loop(line, &map, flag, data);
	close(data->fd);
	data->map = ft_split(map, '\n');
	if (data->map == NULL)
		free_data_closed_fd(data, "Malloc failed!\n");
	free(map);
	data->f_int = rgb_to_int(data->floor);
	data->s_int = rgb_to_int(data->sky);
}
