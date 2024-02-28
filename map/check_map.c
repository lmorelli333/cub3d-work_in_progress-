/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 04:00:22 by fcarlucc          #+#    #+#             */
/*   Updated: 2024/02/28 05:16:36 by fcarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void find_player(t_map *map)
{
    t_player *player;

    player = (t_player *)malloc(sizeof(t_player));
    if (!player)
        return;

    player->y = 0;
    player->x = 0;

    while (player->y < map->lines)
	{
        while (player->x < map->max)
		{
            if (map->map[player->y][player->x] == 'N' || map->map[player->y][player->x] == 'S' || map->map[player->y][player->x] == 'W' || map->map[player->y][player->x] == 'E')
			{
                printf("\n\n%c\n\n\n", map->map[player->y][player->x]);
                printf("\n\n%d\n%d\n\n", player->y, player->x);
                return ;
            }
			player->x++;
        }
		player->y++;
		player->x = 0;
    }
	return ;
}

