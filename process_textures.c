#include "cub3D.h"

int    *load_image(t_master *master, char *path, t_img *img)
{
    int y;
    int x;
    int *texture;

    y = 0;
    x = 0;
    write(1, "HELLO\n", 6);
    img->img = mlx_xpm_file_to_image(master->mlx.mlx_ptr, path, &img->img_width, &img->img_height);
    img->data = (int *)mlx_get_data_addr(img->img, &img->bpp, &img->llen, &img->en);
    texture = malloc(sizeof(int *) * (img->img_height * img->img_width));
    while (y < img->img_height)
    {
        x = 0;
        while (x < img->img_width)
        {
            texture[img->img_width * y + x] = img->data[img->img_width * y + x];
            x++;
        }
        y++;
    }
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

void    process_textures(t_master *master)
{
    t_img   img;
    
    texture_extension_check(master);
    master->data.north = load_image(master, master->data.wall[0], &img);
    master->data.east = load_image(master, master->data.wall[1], &img);
    master->data.south = load_image(master, master->data.wall[2], &img);
    master->data.west = load_image(master, master->data.wall[2], &img);
}