/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checks.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 15:56:05 by lmorelli          #+#    #+#             */
/*   Updated: 2024/02/21 15:56:24 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cub3d.h"

void	check_wall(t_all *all)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen((const char *)box->map.mapm[0]) - 1;
	while (box->map.mapm[i])
	{
		if (box->map.mapm[i][0] != '1' || box->map.mapm[i][len] != '1')
		{	
			ft_printf("Error\n");
			exit (1);
		}
		i++;
	}
	i = 0;
	while (box->map.mapm[i])
	{
		if (box->map.mapm[i][0] != '1' ||
		box->map.mapm[i][ft_strlen((const char *)box->map.mapm[i]) - 1] != '1')
		{	
			ft_printf("Error\n");
			exit (1);
		}
		i++;
	}
}