#ifndef CUB3D_H
# define CUB3D_H
# include <unistd.h> //close, read, write
# include <stdlib.h> //malloc, free, exit
# include <stdio.h> //printf, perror
# include <string.h> //strerror
# include <math.h> //you already know
# include <mlx.h> //unfortunately you already know
# include <fcntl.h> //open
# include "./libft/libft.h"
# define WIN_W 1920
# define WIN_H 1080


//arg_checker.c
int    get_fd(char *map);
int	is_it_whitespace(char c);
int are_there_any_whitespaces(char *str);
void    arg_checker(int ac, char **av);
void    validity_checker(int ac, char **av);

//main.c
int	main(int ac, char **av);

#endif