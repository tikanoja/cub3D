#include "cub3D.h"

int main(int ac, char **av)
{
    int fd;

    arg_checker(ac, av);
    fd = get_fd(av[1]);
    //map parsing && close fd
    //map validity check
    printf("thanks that is indeed a valid map with fd: %d\n", fd);
    return (0);
}