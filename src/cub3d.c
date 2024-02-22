/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:41:48 by lmorelli          #+#    #+#             */
/*   Updated: 2024/02/22 18:11:13 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void    printmatrix(t_all *all)
{
    int i = 0;

    while (all->map.mapm[i])
    {
        ft_printf("%s\n", all->map.mapm[i]);
        i++;
    }
}

void    read_map(t_all *all, char *av)
{
	int		fd;
	char	*str;
    int     i;

	fd = open(av, O_RDONLY);
	if (fd == -1)
		return ;
	all->map.mapv = malloc(1);
	all->map.mapv[0] = '\0';
	while (1)
	{  
        i = 0;
		str = get_next_line(fd);
		if (!str)
			break ;
        if (str[0] != 'N' && str[0] != 'S' && str[0] != 'W' && str[0] != 'E')
 
		    all->map.mapv = ft_strjoin(all->map.mapv, str);
		free(str);
	}
	all->map.mapm = ft_split(all->map.mapv, '\n');
    printmatrix(all);
	close(fd);
}

int key_press(int keycode, t_all *all)
{
	if (keycode == 13 || keycode == 126) //avanti
		all->player.up = 1;
	else if (keycode == 1|| keycode == 125) //indietro
		all->player.down = 1;
	if (keycode == 0) //left
		all->player.left = 1;
	else if (keycode == 2) //right
		all->player.right = 1;
	if (keycode == 14|| keycode == 124) // rotazione oraria
		all->player.rr_left = 1;
	else if (keycode == 12 || keycode == 123) // rotazione antioraria
		all->player.rr_right = 1;
	return (0);
}


void    init_img(t_all *all)
{
	all->boh.img = mlx_new_image(all->boh.mlx, 640, 480);
	all->boh.addr = mlx_get_data_addr(all->boh.img, &all->boh.bits_per_pixel,
			&all->boh.line_length, &all->boh.endian);
            
    mlx_hook(all->boh.win, 2, 0, key_press, all);
}

void    init(t_all *all)
{
    // all->boh.win = NULL; NON RICORDO SE VA FATTA STA COSA
    // all->boh.mlx = NULL;
    all->boh.mlx = mlx_init();
	if (!all->boh.mlx)
        //exit free msgERROR
    all->boh.win = mlx_new_window(all->boh.mlx, 640, 480, "Cub3D");
	if (! all->boh.win)
	     //exit free msgERROR
    all->player.up = 0;
    all->player.down = 0;
    all->player.left = 0;
    all->player.right = 0;
    all->player.rr_left = 0;
    all->player.rr_right = 0;
    return ;  
}

int main(int ac, char **av)
{
    (void)av;
    t_all all;

    if (ac != 2)
    {
        ft_printf("e sei ncojone\n");
        exit (1);
    }
    init(&all);
    read_map(&all, av[1]);
    if (check_map(&all))
        ft_printf("Error\n");
    if (check_av(av[1]))
        ft_printf("Error\n");
    
    //cub3d(&all);
    //free(&all);
    return (0);
}