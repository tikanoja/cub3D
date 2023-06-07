#include "cub3D.h"

int	freeandexit(t_mlxinfo *mlx)
{
	mlx_destroy_window(mlx->mlx_ptr, mlx->mlx_win);
	free(mlx->mlx_ptr);
	exit(0);
	return (0);
}

int	key_hook(int keycode, t_mlxinfo *mlx)
{
	// t_img	img;

	printf("keycode: %d\n", keycode);
	if (keycode == 53 || keycode == 6)
	{
		freeandexit(mlx);
	}
	else if (keycode == 13 || keycode == 126)
		printf("W / Arrow Up\n");
	else if (keycode == 1 || keycode == 125)
		printf("S / Arrow Down\n");
	else if (keycode == 0 || keycode == 123)
		printf("A / Arrow Left\n");
	else if (keycode == 2 || keycode == 124)
		printf("D / Arrow Right\n");
	// if ((keycode >= 123 && keycode <= 126) || keycode == 69 || keycode == 78)
	// {
	// 	img.img = mlx_new_image(mlx->mlx_ptr, WIN_W, WIN_H);
	// 	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.llen, &img.en);
	// 	modhandler(keycode, mlx);
	// 	drawgrid(*mlx->map, &img, mlx->coords, mlx);
	// 	mlx_destroy_image(mlx->mlx_ptr, mlx->currentimg);
	// 	mlx_put_image_to_window(mlx->mlx_ptr, mlx->mlx_win, img.img, 0, 0);
	// 	mlx->currentimg = img.img;
	// }
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

// void	draw_minimap(t_master *master, t_img *img)
// {
// 	int x;
// 	int y;
// 	int block;

// 	x = WIN_W / master->data.mapsize[0] / 2;
// 	y = WIN_H / master->data.mapsize[1] / 2;
// 	if (x <= y)
// 		block = x;
// 	else
// 		block = y;
// 	x = 0;
// 	y = 0;
// 	while(y < block * master->data.mapsize[1])
// 	{
// 		while (x < block * master->data.mapsize[0])
// 		{
// 			my_mlx_pixel_put(img, x, y, 0x808080);
// 			x++;
// 		}
// 		x = 0;
// 		y++;
// 	}
// }

void	draw_background(t_master *master, t_img *img)
{
	int x;
	int y;

	x = 0;
	y = 0;
	while(y < WIN_H)
	{
		while (x < WIN_W)
		{
			if (y < WIN_H / 2)
				my_mlx_pixel_put(img, x, y, master->data.s_int);
			else
				my_mlx_pixel_put(img, x, y, master->data.f_int);
			x++;
		}
		x = 0;
		y++;
	}
}

void	run_cub3d(t_master master)
{
	master.img.img = mlx_new_image(master.mlx.mlx_ptr, WIN_W, WIN_H);
	master.img.addr = mlx_get_data_addr(master.img.img, &master.img.bpp, &master.img.llen, &master.img.en);
	draw_background(&master, &master.img);
	// draw_minimap(&master, &master.img);
	mlx_put_image_to_window(master.mlx.mlx_ptr, master.mlx.mlx_win, master.img.img, 0, 0);
	mlx_key_hook(master.mlx.mlx_win, key_hook, &master.mlx);
	mlx_hook(master.mlx.mlx_win, 17, 0, freeandexit, &master.mlx);
	mlx_loop(master.mlx.mlx_ptr);
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
}

int main(int ac, char **av)
{
	t_master	master;

    arg_checker(ac, av);
    master.data.fd = get_fd(av[1]);
    map_parser(&master.data);
	get_map_size(&master.data);
    map_validator(&master.data);
	//printmap(master.data);
	init_mlx(&master);
	run_cub3d(master);
    return (0);
}