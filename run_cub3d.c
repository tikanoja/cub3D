#include "cub3D.h"

int is_wall(float x, float y, t_master *master, float buffer_distance)
{
    int map_x = x / master->minimap.block;
    int map_y = y / master->minimap.block;

    if (map_x >= 0 && map_x < master->data.mapsize[0] && map_y >= 0 && map_y < master->data.mapsize[1] && master->data.map[map_y][map_x] == '1')
    {
        float dist_x = fmod(x, master->minimap.block);
        float dist_y = fmod(y, master->minimap.block);

        if (dist_x <= buffer_distance || dist_x >= master->minimap.block - buffer_distance || dist_y <= buffer_distance || dist_y >= master->minimap.block - buffer_distance)
        {
            return 1; // Collision with wall considering the buffer distance
        }
    }

    return 0;
}
//add collision distance to other directions?

int update_game(t_master *master)
{
	float movement_speed = 1.5;
	int updateflag = 0;
	float new_x, new_y;
	int sign_x = 0;
    int sign_y = 0;

	if (master->keylog.W == 1 || master->keylog.UP == 1) // Move forward
	{
		new_x = master->player.x + movement_speed * cos(master->player.angle);
		new_y = master->player.y + movement_speed * sin(master->player.angle);

		sign_y = WALLDIST;
		sign_x = WALLDIST;
		if (cos(master->player.angle) >= 0)
			sign_x = -WALLDIST;
		if (sin(master->player.angle) >= 0)
			sign_y = -WALLDIST;
		if (!is_wall(new_x - sign_x, new_y - sign_y, master, master->minimap.block) || GOD_MODE == 0)
		{
			master->player.x = new_x;
			master->player.y = new_y;
			updateflag = 1;
		}
	}

	if (master->keylog.S == 1 || master->keylog.DOWN == 1) // Move backward
	{
		new_x = master->player.x - movement_speed * cos(master->player.angle);
		new_y = master->player.y - movement_speed * sin(master->player.angle);

		sign_x = -WALLDIST;
		sign_y = -WALLDIST;
		if (cos(master->player.angle) >= 0)
			sign_x = WALLDIST;
		if (sin(master->player.angle) >= 0)
			sign_y = WALLDIST;
		if (!is_wall(new_x - sign_x, new_y - sign_y, master, master->minimap.block) || GOD_MODE == 0)
		{
			master->player.x = new_x;
			master->player.y = new_y;
			updateflag = 1;
		}
	}

	if (master->keylog.A == 1) // Move left
	{
		new_x = master->player.x + movement_speed * sin(master->player.angle);
		new_y = master->player.y - movement_speed * cos(master->player.angle);
		sign_x = WALLDIST;
		sign_y = WALLDIST;
		if (cos(master->player.angle) >= 0)
			sign_x = -WALLDIST;
		if (sin(master->player.angle) >= 0)
			sign_y = -WALLDIST;
		if (!is_wall(new_x - sign_x, new_y - sign_y, master, master->minimap.block) || GOD_MODE == 0)
		{
			master->player.x = new_x;
			master->player.y = new_y;
			updateflag = 1;
		}
	}

	if (master->keylog.D == 1) // Move right
	{
		new_x = master->player.x - movement_speed * sin(master->player.angle);
		new_y = master->player.y + movement_speed * cos(master->player.angle);
		sign_x = -WALLDIST;
		sign_y = -WALLDIST;
		if (cos(master->player.angle) >= 0)
			sign_x = WALLDIST;
		if (sin(master->player.angle) >= 0)
			sign_y = WALLDIST;
		if (!is_wall(new_x - sign_x, new_y - sign_y, master, master->minimap.block) || GOD_MODE == 0)
		{
			master->player.x = new_x;
			master->player.y = new_y;
			updateflag = 1;
		}
	}


	if (master->keylog.LEFT == 1) // Rotate left
	{
		master->player.angle -= 0.03;
		if (master->player.angle < 0)
			master->player.angle = 2 * M_PI + master->player.angle;
		updateflag = 1;
	}

	if (master->keylog.RIGHT == 1) // Rotate right
	{
		master->player.angle += 0.03;
		if (master->player.angle > 2 * M_PI)
			master->player.angle = master->player.angle - 2 * M_PI;
		updateflag = 1;
	}

	if (updateflag == 1)
		run_cub3d(master);

	return 0;
	}


void	run_cub3d(t_master *master)
{
	// static int flag;

	// if (flag != 0)
		mlx_destroy_image(master->mlx.mlx_ptr, master->img.img);
	// flag = 1;
	master->img.img = mlx_new_image(master->mlx.mlx_ptr, WIN_W, WIN_H);
	master->img.addr = mlx_get_data_addr(master->img.img, &master->img.bpp, &master->img.llen, &master->img.en);
	draw_background(master, &master->img);
	txt_raycaster(master, &master->img);

	draw_minimap(master, &master->img);
	mlx_put_image_to_window(master->mlx.mlx_ptr, master->mlx.mlx_win, master->img.img, 0, 0);
}

void	init_cub3d(t_master master)
{
	master.img.img = mlx_new_image(master.mlx.mlx_ptr, WIN_W, WIN_H);
	master.img.addr = mlx_get_data_addr(master.img.img, &master.img.bpp, &master.img.llen, &master.img.en);
	draw_background(&master, &master.img);
	draw_minimap(&master, &master.img);
	txt_raycaster(&master, &master.img);
	mlx_put_image_to_window(master.mlx.mlx_ptr, master.mlx.mlx_win, master.img.img, 0, 0);
	mlx_hook(master.mlx.mlx_win, 17, 0, exit_gracefully, &master);
	mlx_hook(master.mlx.mlx_win, 2, 0, key_press, &master);
	mlx_hook(master.mlx.mlx_win, 3, 0, key_release, &master);
	mlx_loop_hook(master.mlx.mlx_ptr, update_game, &master); //taa ois mlx loop hook
	mlx_loop(master.mlx.mlx_ptr);
}