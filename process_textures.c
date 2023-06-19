#include "cub3D.h"

t_texture    load_image(t_master *master, char *path, t_img *img)
{
    int y;
    int x;
    t_texture texture;


    y = 0;
    x = 0;
    
    img->img = mlx_xpm_file_to_image(master->mlx.mlx_ptr, path, &img->img_width, &img->img_height);
    img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->llen, &img->en);
    texture.array = malloc(sizeof(int *) * (img->img_height * img->img_width));
    while (y < img->img_height)
    {
        x = 0;
        while (x < img->img_width)
        {
            texture.array[img->img_width * y + x] = img->data[img->img_width * y + x];
            x++;
        }
        y++;
    }
    texture.width = img->img_width;
    texture.height = img->img_height;
    mlx_destroy_image(master->mlx.mlx_ptr, img->img);
    return (texture);
}

void    texture_extension_check(t_master *master)
{
    int str_end;
    int i;

    i = 0;
    while (i < 4)
    {
        str_end = ft_strlen(master->data.wall[i]);
        str_end = str_end - 4;
        if (ft_strncmp(&master->data.wall[i][str_end], ".xpm", 4))
            free_data_closed_fd(&master->data, "Please provide textures in .xpm\n");
        i++;
    }
}

void    free_textures(t_master *master, int flag)
{
    if (flag == 1)
        free(master->data.north.array);
    else if (flag == 2)
    {
        free(master->data.north.array);
        free(master->data.east.array);
    }
    else if (flag == 3)
    {
        free(master->data.north.array);
        free(master->data.east.array);
        free(master->data.west.array);
    }
    else if (flag == 4)
    {
        free(master->data.north.array);
        free(master->data.south.array);
        free(master->data.east.array);
        free(master->data.west.array);
    }
    if (flag != 4)
        free_data_closed_fd(&master->data, "Malloc failed!\n");
}

void    process_textures(t_master *master)
{
    t_img   img;
    
    texture_extension_check(master);
    master->data.north = load_image(master, master->data.wall[0], &img);
    if (master->data.north.array == NULL)
        free_data_closed_fd(&master->data, "Malloc failed!\n");
    master->data.east = load_image(master, master->data.wall[1], &img);
    if (master->data.east.array == NULL)
        free_textures(master, 1);
    master->data.south = load_image(master, master->data.wall[2], &img);
    if (master->data.south.array == NULL)
        free_textures(master, 2);
    master->data.west = load_image(master, master->data.wall[3], &img);
    if (master->data.west.array == NULL)
        free_textures(master, 3);
}