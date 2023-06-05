#include "cub3D.h"

void    map_parser(t_data *data)
{
    char *line;

    line = NULL;
    line = get_next_line(data->fd);
    //write(1, "HERE\n", 5);
    while (line != NULL)
    {
        printf("%s\n", line);
        line = get_next_line(data->fd);
    }
    //remember to close fd :)
}