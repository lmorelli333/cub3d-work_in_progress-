/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 04:00:22 by fcarlucc          #+#    #+#             */
/*   Updated: 2024/02/28 06:44:01 by fcarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void find_player(t_map *map, char *s)
{
    t_player *player;

    player = (t_player *)malloc(sizeof(t_player));
    if (!player)
        return ;
    player->y = 0;
    player->x = 0;
	player->field = ft_split(s, '\n');
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
		// if (is_playable(player))
        play(map);
        // else
        //     err("Error : invalid map.");
    }
	return ;
}

int is_playable(t_player *player)
{
	int i;
	int j;

	i = player->y;
	j = player->x;
	return (1);
}

void play(t_map *map)
{
    t_game *game;
    
    game = (t_game *)malloc(sizeof(t_game));
    if (!game)
        return ;
    game->mlx = mlx_init();
    game->window = mlx_new_window(game->mlx, map->max * 64, map->lines * 64, "CUB3D");
}