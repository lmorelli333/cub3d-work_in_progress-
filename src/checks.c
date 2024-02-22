/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:56:05 by lmorelli          #+#    #+#             */
/*   Updated: 2024/02/22 14:17:39 by lmorelli         ###   ########.fr       */
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

// static int	check_wall_upbot(t_all *all, int i, int j)
// {
// 	if (!all->map.mapm || !all->map.mapm[i] || !all->map.mapm[i][j])
// 		return (1);
// 	while (all->map.mapm[i][j] == ' ' || all->map.mapm[i][j] == '\t'
// 	|| all->map.mapm[i][j] == '\v' || all->map.mapm[i][j] == '\r' 
// 	|| all->map.mapm[i][j] == '\f')
// 		j++;
// 	while (all->map.mapm[i][j])
// 	{
// 		if (all->map.mapm[i][j] != '1' || (all->map.mapm[i][j] == '\0' && all->map.mapm[i-1][j] != '1'))
// 			return (1);
// 		j++;
// 	}
// 	return (0);
// }

// int	check_wall(t_all *all)
// {
// 	int	i;
// 	int	j;
//     int height;
//     int k;
//     int x = 1;

// 	if (check_wall_upbot(all, 0, 0))
// 		return (1);
// 	i = 1;
//     height = map_height(all);
// 	while (i < height)
// 	{
// 		j = ft_strlen(all->map.mapm[i]) - 1;
// 		if (all->map.mapm[i][j] != '1' || all->map.mapm[i][0] != '1')
// 			return (1);
//         while (x < height - 1)
//         {
//             k = 1;
//             while (all->map.mapm[x][k])
//             {
//                 if (all->map.mapm[x - 1][k] == '\0' || all->map.mapm[height - 1][k] == '\0')
//                     return (1);
//                 k++;
//             }
//             x++;
//         }
// 		i++;
// 	}
//     i--;
// 	if (check_wall_upbot(all, i, 0))
// 		return (1);
// 	return (0);
// }

int check_around(t_all *all, size_t i , size_t j)
{
    if (all->map.mapm[i][j] == '1')
        return (1);
    else if (all->map.mapm[i][j] != '1' && all->map.mapm[i][j] != '\n' && all->map.mapm[i][j] != '\0')
    {
        if (all->map.mapm[i][j + 1] != '0' && all->map.mapm[i][j + 1] != '1' && all->map.mapm[i][j + 1] != 'N')
            return (0);
        else if (all->map.mapm[i][j - 1] != '0' && all->map.mapm[i][j - 1] != '1' && all->map.mapm[i][j - 1] != 'N')
            return (0);
        else if (all->map.mapm[i + 1][j] != '0' && all->map.mapm[i + 1][j] != '1' && all->map.mapm[i + 1][j] != 'N')
            return (0);
        else if (all->map.mapm[i - 1][j] != '0' && all->map.mapm[i - 1][j] != '1' && all->map.mapm[i - 1][j] != 'N')
            return (0);
    }
     return (1);
}

int check_up_bottom(t_all *all, size_t i, size_t j)
{
    // if (!all->map.mapm || !all->map.mapm[i] || !all->map.mapm[i][j])
	// 	return (1);
	// while (all->map.mapm[i][j] == ' ' || all->map.mapm[i][j] == '\t'
	// || all->map.mapm[i][j] == '\v' || all->map.mapm[i][j] == '\r' 
	// || all->map.mapm[i][j] == '\f')
	// 	j++;
  //  ft_printf("ciao\n");
	while (all->map.mapm[i][j])
	{ //ft_printf("codeddio\n");
		if (all->map.mapm[i][j] != '1' && all->map.mapm[i][j] != ' ' && all->map.mapm[i][j] != '\0' && all->map.mapm[i][j] != '\n') //|| (all->map.mapm[i][j] == '\0' && all->map.mapm[i-1][j] != '1'))
			return (1);
		j++;
	}
	return (0);
}

int flood_fill(t_all *all)
{
    size_t i = 0;
    size_t j;
    size_t height;

    height = map_height(all) - 1;
    while (all->map.mapm[i])
    {
        j  = 0;
        if (i == 0 || i == height)
        {
            if (check_up_bottom(all, i, j))
                return (1);
        }
        else// else if (i != 0 && i != height)
        {

            while (j < ft_strlen(all->map.mapm[i]))
            {
       // ft_printf("i = %d\nj = %d\n", i, j);
                if (!check_around(all, i, j))
                    return (1);
                j++;
            }
        }
        i++;
    }
    return (0);
}