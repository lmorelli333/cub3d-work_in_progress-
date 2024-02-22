/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:56:05 by lmorelli          #+#    #+#             */
/*   Updated: 2024/02/22 16:12:44 by lmorelli         ###   ########.fr       */
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

static int check_around(t_all *all, size_t i , size_t j)
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
	// while (all->map.mapm[i][j] == ' ' || all->map.mapm[i][j] == '\t'
	// || all->map.mapm[i][j] == '\v' || all->map.mapm[i][j] == '\r' 
	// || all->map.mapm[i][j] == '\f')
	// 	j++;
	while (all->map.mapm[i][j])
	{
		if (all->map.mapm[i][j] != '1' && all->map.mapm[i][j] != ' ' && all->map.mapm[i][j] != '\0')
			return (1);
		j++;
	}
	return (0);
}

int check_map(t_all *all)
{
    size_t i;
    size_t j;
    size_t height;

    i = 0;
    height = map_height(all) - 1;
    while (all->map.mapm[i])
    {
        j  = 0;
        if (i == 0 || i == height)
        {
            if (check_up_bottom(all, i, j))
                return (1);
        }
        else
        {

            while (j < ft_strlen(all->map.mapm[i]))
            {
                if (!check_around(all, i, j))
                    return (1);
                j++;
            }
        }
        i++;
    }
    return (0);
}