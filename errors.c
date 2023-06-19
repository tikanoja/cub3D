#include "cub3D.h"

void exitmsg(char *msg)
{
    ft_putstr_fd(msg, 2);
    exit(1);
}

void free_char_arr(char **arr)
{
    int i;

    i = 0;
    while(arr[i])
    {
        free(arr[i]);
        i++;
    }
    free(arr);
}

void free_data(t_data *data, char *msg)
{
    ft_putstr_fd("Error\n", 2);
    close(data->fd);
    if (data && data->map)
        free_char_arr(data->map);
    if (data && data->wall)
        free_char_arr(data->wall);
    exitmsg(msg);
}

void free_data_closed_fd(t_data *data, char *msg)
{
    ft_putstr_fd("Error\n", 2);
    if (data && data->map)
        free_char_arr(data->map);
    if (data && data->wall)
        free_char_arr(data->wall);
    exitmsg(msg);
}

int    exit_gracefully(t_master *master)
{
    free_char_arr(master->data.map);
    free_char_arr(master->data.wall);
    free_textures(master, 4);
    mlx_destroy_image(master->mlx.mlx_ptr, master->img.img);
    mlx_destroy_window(master->mlx.mlx_ptr, master->mlx.mlx_win);
    free(master->mlx.mlx_ptr);
    ft_putstr_fd("Thanks for playing :)\n", 1);
    exit (0);
    return (0);
}