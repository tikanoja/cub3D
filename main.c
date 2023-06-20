/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ttikanoj <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 10:04:02 by ttikanoj          #+#    #+#             */
/*   Updated: 2023/06/20 10:04:06 by ttikanoj         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

int	freeandexit(t_master *master)
{
	mlx_destroy_window(master->mlx.mlx_ptr, master->mlx.mlx_win);
	free(master->mlx.mlx_ptr);
	exit(0);
	return (0);
}

void printmap(t_data data)
{
	int i;
	int j;

	i = 0;
	j = 0;
	printf("north: %s\nsouth: %s\neast: %s\nwest: %s\n\n", data.wall[0], data.wall[2], data.wall[1], data.wall[3]);
	printf("floor R: %d, G: %d, B: %d\n", data.floor[0], data.floor[1], data.floor[2]);
	printf("sky R: %d, G: %d, B: %d\n\n", data.sky[0], data.sky[1], data.sky[2]);
	while(data.map[j])
	{
		while(data.map[j][i])
		{
			printf("%c, ", data.map[j][i]);
			i++;
		}
		printf("\n");
		i = 0;
		j++;
	}
}


void	get_map_size(t_data *data)
{
	int maxwidth;
	int i;
	int j;

	maxwidth = 0;
	i = 0;
	j = 0;
	while(data->map[j])
	{
		while(data->map[j][i])
			i++;
		if (i > maxwidth)
			maxwidth = i;
		i = 0;
		j++;
	}
	data->mapsize[0] = maxwidth;
	data->mapsize[1] = j;
}

void	init_mlx(t_master *master)
{
	master->mlx.mlx_ptr = mlx_init();
	master->mlx.mlx_win = mlx_new_window(master->mlx.mlx_ptr, WIN_W, WIN_H, "cub3D");
	master->keylog.W = 0;
	master->keylog.A = 0;
	master->keylog.S = 0;
	master->keylog.D = 0;
	master->keylog.UP = 0;
	master->keylog.LEFT = 0;
	master->keylog.DOWN = 0;
	master->keylog.RIGHT = 0;
}
int main(int ac, char **av)
{
	t_master	master;

    arg_checker(ac, av);
    master.data.fd = get_fd(av[1]);
    map_parser(&master.data);
	get_map_size(&master.data);
	// printmap(master.data);
    map_validator(&master.data);
	process_textures(&master);
	init_mlx(&master);
	init_cub3d(master);
    return (0);
}
