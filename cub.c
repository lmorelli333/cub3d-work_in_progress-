/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:26:48 by fcarlucc          #+#    #+#             */
/*   Updated: 2024/02/26 16:14:51 by fcarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int main(int ac, char **av)
{
	if (ac == 2)
	{
		if (take_params(av[1]))
		{
			printf("ccciaooo");
		}
		return (1);
	}
	return (err("Error: usage: ./cub3d and 'your_map.cub' .\n"));
}