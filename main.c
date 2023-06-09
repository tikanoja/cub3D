#include "cub3D.h"

int	freeandexit(t_master *master)
{
	mlx_destroy_window(master->mlx.mlx_ptr, master->mlx.mlx_win);
	free(master->mlx.mlx_ptr);
	exit(0);
	return (0);
}

int	key_press(int keycode, t_master *master)
{
	if (keycode == 53 || keycode == 6)
	{
		freeandexit(master);
	}
	else if (keycode == 13 || keycode == 126) //anglen suuntaan
	{
		master->keylog.W = 1;
		master->keylog.UP = 1;
	}
	else if (keycode == 1 || keycode == 125) //anglen suuntaan
	{
		master->keylog.S = 1;
		master->keylog.DOWN = 1;
	}
	else if (keycode == 0)
		master->keylog.A = 1;
	else if (keycode == 2)
		master->keylog.D = 1;
	else if (keycode == 123)
		master->keylog.LEFT = 1;
	else if (keycode == 124)
		master->keylog.RIGHT = 1;
	return (0);
}
int	key_release(int keycode, t_master *master)
{
	if (keycode == 13 || keycode == 126) //anglen suuntaan
	{
		master->keylog.W = 0;
		master->keylog.UP = 0;
	}
	else if (keycode == 1 || keycode == 125) //anglen suuntaan
	{
		master->keylog.S = 0;
		master->keylog.DOWN = 0;
	}
	else if (keycode == 0)
		master->keylog.A = 0;
	else if (keycode == 2)
		master->keylog.D = 0;
	else if (keycode == 123)
		master->keylog.LEFT = 0;
	else if (keycode == 124)
		master->keylog.RIGHT = 0;
	return (0);
}

void	run_cub3d(t_master *master)
{
	static int flag;

	if (flag != 0)
		mlx_destroy_image(master->mlx.mlx_ptr, master->img.img);
	flag = 1;
	master->img.img = mlx_new_image(master->mlx.mlx_ptr, WIN_W, WIN_H);
	master->img.addr = mlx_get_data_addr(master->img.img, &master->img.bpp, &master->img.llen, &master->img.en);
	draw_background(master, &master->img);
	draw_minimap(master, &master->img);
	mlx_put_image_to_window(master->mlx.mlx_ptr, master->mlx.mlx_win, master->img.img, 0, 0);
}

int	update_game(t_master *master)
{
	int movement_speed;
	int updateflag;

	updateflag = 0;
	movement_speed = 4;
	if (master->keylog.W == 1 || master->keylog.UP == 1) //anglen suuntaan
	{
		master->player.y += movement_speed * sin(master->player.angle);
		master->player.x += movement_speed * cos(master->player.angle);
		updateflag = 1;
		printf("W / Arrow Up\n");

	}
	if (master->keylog.S == 1 || master->keylog.DOWN == 1) //anglen suuntaan
	{
		master->player.y += -movement_speed * sin(master->player.angle);
		master->player.x += -movement_speed * cos(master->player.angle);
		printf("S / Arrow Down\n");
		updateflag = 1;

	}
	if (master->keylog.A == 1)
	{
		master->player.x -= 2;
		updateflag = 1;
		printf("A\n");

	}
	if (master->keylog.D == 1)
	{
		master->player.x += 2;
		updateflag = 1;
		printf("D\n");

	}
	if (master->keylog.LEFT == 1)
	{
		master->player.angle -= 0.05;
		if (master->player.angle <= 0)
			master->player.angle = 2 * M_PI;
		updateflag = 1;
		printf("Arrow Left\n");

	}
	if (master->keylog.RIGHT == 1)
	{
		master->player.angle += 0.05;
		if (master->player.angle >= 2 * M_PI)
			master->player.angle = 0;
		updateflag = 1;
		printf("Arrow Right\n");
	}
	if(updateflag == 1)
		run_cub3d(master);
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



void	init_cub3d(t_master master)
{
	master.img.img = mlx_new_image(master.mlx.mlx_ptr, WIN_W, WIN_H);
	master.img.addr = mlx_get_data_addr(master.img.img, &master.img.bpp, &master.img.llen, &master.img.en);
	draw_background(&master, &master.img);
	draw_minimap(&master, &master.img);
	mlx_put_image_to_window(master.mlx.mlx_ptr, master.mlx.mlx_win, master.img.img, 0, 0);

	mlx_hook(master.mlx.mlx_win, 2, 0, key_press, &master);
	mlx_hook(master.mlx.mlx_win, 3, 0, key_release, &master);
	mlx_loop_hook(master.mlx.mlx_ptr, update_game, &master); //taa ois mlx loop hook
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
    map_validator(&master.data);
	//printmap(master.data);
	init_mlx(&master);
	init_cub3d(master);
    return (0);
}