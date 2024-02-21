/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:41:48 by lmorelli          #+#    #+#             */
/*   Updated: 2024/02/20 19:14:41 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

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
    //check_map(&all);
    //cub3d(&all);
    //free(&all);
    return (0);
}