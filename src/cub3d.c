/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:41:48 by lmorelli          #+#    #+#             */
/*   Updated: 2024/02/21 20:44:17 by lmorelli         ###   ########.fr       */
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
    all->player.dir = '\0';
	all->player.dir_x = 0.0;
	all->player.dir_y = 0.0;
	all->player.pos_x = 0.0;
	all->player.pos_y = 0.0;
	all->player.plane_x = 0.0;
	all->player.plane_y = 0.0;
	all->player.mv_x = 0;
	all->player.mv_y = 0;
	all->player.rotate = 0;
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
    if (check_wall(&all))
        ft_printf("Error\n");
    if (check_av(av[1]))
        ft_printf("Error\n");
    //check_map(&all);
    //cub3d(&all);
    //free(&all);
    return (0);
}