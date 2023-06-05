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

	if (keycode == 53 || keycode == 6)
	{
		freeandexit(mlx);
	}
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


int main(int ac, char **av)
{
    t_mlxinfo	mlx;
	t_img		img;
	t_data		data;

    arg_checker(ac, av);
    data.fd = get_fd(av[1]);
    map_parser(&data);
    //map validity check

    mlx.mlx_ptr = mlx_init();
	mlx.mlx_win = mlx_new_window(mlx.mlx_ptr, WIN_W, WIN_H, "cub3D");
	img.img = mlx_new_image(mlx.mlx_ptr, WIN_W, WIN_H);
	img.addr = mlx_get_data_addr(img.img, &img.bpp, &img.llen, &img.en);
	mlx_put_image_to_window(mlx.mlx_ptr, mlx.mlx_win, img.img, 0, 0);
	mlx_key_hook(mlx.mlx_win, key_hook, &mlx);
	mlx_hook(mlx.mlx_win, 17, 0, freeandexit, &mlx);
	mlx_loop(mlx.mlx_ptr);
    
    return (0);
}