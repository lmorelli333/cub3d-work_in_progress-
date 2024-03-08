/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:26:48 by fcarlucc          #+#    #+#             */
/*   Updated: 2024/03/08 20:07:45 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	main(int ac, char **av)
{
	if (ac == 2)
	{
		if (check_map(av[1]))
		{
			printf("ccciaooo");
		}
		return (1);
	}
	return (err("Error: usage: ./cub3d and 'your_map.cub' .\n"));
}
