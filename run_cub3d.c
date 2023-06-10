#include "cub3D.h"

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