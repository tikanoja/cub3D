#include "cub3D.h"

void    fill_to_struct(t_data *data, char *line, int status)
{
    // static int filling_stage;

    // if (status != 0)
    //     filling_stage = status;
    // while(is_it)
    if (status == 0)
        //check_for_ilmasnuunta
    else if (status == 1)
        //ceck_for_colors
    else if (status == 2)
        //fill map
}


void    map_parser(t_data *data)
{
    char *line;
    int status;

    line = NULL;
    status = 0;
    data->wall = malloc(sizeof(char *) * 5);
    if (data->wall == NULL)
        free_data(data, "Malloc failed!\n");
    data->wall[4] = NULL;
    line = get_next_line(data->fd);
    if (line == NULL)
        free_data(data, "Malloc failed!\n");
    while (line != NULL)
    {
        printf("%s\n", line);
        status = check_status(data);
        fill_to_struct(data, line, status);
        free(line);
        line = get_next_line(data->fd);
        if (line == NULL)
            free_data(data, "Malloc failed!\n");
    }
    close(data->fd);
}
