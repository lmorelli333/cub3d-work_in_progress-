/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:56:05 by lmorelli          #+#    #+#             */
/*   Updated: 2024/02/21 21:37:48 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

int	check_av(char *av)
{
	size_t	len;

	len = ft_strlen(av);
	if ((av[len - 1] != 'b' || av[len - 2] != 'u'
			|| av[len - 3] != 'c'
			|| av[len - 4] != '.'))
		return (1);
	return (0);
}

static int  map_height(t_all *all)
{
    int height;

    height = 0;
    while (all->map.mapm[height])
        height++;
    return (height);
}

static int	check_wall_upbot(t_all *all, int i, int j)
{
	if (!all->map.mapm || !all->map.mapm[i] || !all->map.mapm[i][j])
		return (1);
	while (all->map.mapm[i][j] == ' ' || all->map.mapm[i][j] == '\t'
	|| all->map.mapm[i][j] == '\v' || all->map.mapm[i][j] == '\r' 
	|| all->map.mapm[i][j] == '\f')
		j++;
	while (all->map.mapm[i][j])
	{
		if (all->map.mapm[i][j] != '1' || (all->map.mapm[i][j] == '\0' && all->map.mapm[i-1][j] != '1'))
			return (1);
		j++;
	}
	return (0);
}

int	check_wall(t_all *all)
{
	int	i;
	int	j;
    int height;
    int k;
    int x = 1;

	if (check_wall_upbot(all, 0, 0))
		return (1);
	i = 1;
    height = map_height(all);
	while (i < height)
	{
		j = ft_strlen(all->map.mapm[i]) - 1;
		if (all->map.mapm[i][j] != '1' || all->map.mapm[i][0] != '1')
			return (1);
        while (x < height - 1)
        {
            k = 1;
            while (all->map.mapm[x][k])
            {
                if (all->map.mapm[x - 1][k] == '\0' || all->map.mapm[height - 1][k] == '\0')
                    return (1);
                k++;
            }
            x++;
        }
		i++;
	}
    i--;
	if (check_wall_upbot(all, i, 0))
		return (1);
	return (0);
}


// void	check_wall(t_all *all)
// {
// 	int	i;
// 	int	len;

// 	i = 0;
// 	len = ft_strlen((const char *)all->map.mapm[0]) - 1;
// 	while (all->map.mapm[i])
// 	{
// 		if (all->map.mapm[i][0] != '1' || all->map.mapm[i][len] != '1')
// 		{	
// 			ft_printf("Error\n");
// 			exit (1);
// 		}
// 		i++;
// 	}
// 	i = 0;
// 	while (all->map.mapm[i])
// 	{
// 		if (all->map.mapm[i][0] != '1' ||
// 		all->map.mapm[i][ft_strlen((const char *)all->map.mapm[i]) - 1] != '1')
// 		{	
// 			ft_printf("Error\n");
// 			exit (1);
// 		}
// 		i++;
// 	}
// }