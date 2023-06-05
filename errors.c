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
    close(data->fd);
    if (data && data->map)
        free_char_arr(data->map);
    if (data && data->wall)
        free_char_arr(data->wall);
    exitmsg(msg);
}