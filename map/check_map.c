/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 04:00:22 by fcarlucc          #+#    #+#             */
/*   Updated: 2024/03/06 18:18:01 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"



static size_t  ft_strlen(char *s)
{
    int i;

    i = 0;
    while (s[i])
        i++;
    return (i);
}

static int  map_height(t_map *map)
{
    int height;

    height = 0;
    while (map->map[height])
        height++;
    return (height);
}

static int check_around(t_map *map, size_t i , size_t j)
{
    	while (map->map[i][j] == ' ' || map->map[i][j] == '\t'
	|| map->map[i][j] == '\v' || map->map[i][j] == '\r' 
	|| map->map[i][j] == '\f')
        j++;
    if (map->map[i][j] == '1')
        return (1);
    else if (map->map[i][j] != '1' && map->map[i][j] != '\n' && map->map[i][j] != '\0')
    {
        if (map->map[i][j + 1] != '0' && map->map[i][j + 1] != '1' && map->map[i][j + 1] != 'N' && map->map[i][j + 1] != 'S' && map->map[i][j + 1] != 'W' && map->map[i][j + 1] != 'E')
            return (0);
        else if (map->map[i][j - 1] != '0' && map->map[i][j - 1] != '1' && map->map[i][j - 1] != 'N' && map->map[i][j - 1] != 'S' && map->map[i][j - 1] != 'W' && map->map[i][j - 1] != 'E')
            return (0);
        else if (map->map[i + 1][j] != '0' && map->map[i + 1][j] != '1' && map->map[i + 1][j] != 'N' && map->map[i + 1][j] != 'S' && map->map[i + 1][j] != 'W' && map->map[i + 1][j] != 'E')
            return (0);
        else if (map->map[i - 1][j] != '0' && map->map[i - 1][j] != '1' && map->map[i - 1][j] != 'N' && map->map[i - 1][j] != 'S' && map->map[i - 1][j] != 'W' && map->map[i - 1][j] != 'E')
            return (0);
    }
     return (1);
}

int check_up_bottom(t_map *map, size_t i, size_t j)
{
	while (map->map[i][j])
	{
		if (map->map[i][j] != '1' && map->map[i][j] != ' ' && map->map[i][j] != '\0')
			return (1);
		j++;
	}
	return (0);
}

int check_map(t_map *map)
{
    size_t i;
    size_t j;
    size_t height;

    i = 0;
    height = map_height(map) - 1;
    while (map->map[i])
    {
        j  = 0;
        if (i == 0 || i == height)
        {
            if (check_up_bottom(map, i, j))
                return (1);
        }
        else
        {

            while (j < ft_strlen(map->map[i]))
            {
                if (!check_around(map, i, j))
                    return (1);
                j++;
            }
        }
        i++;
    }
    return (0);
}

int is_playable(t_map *map)
{
	int i;
	int j;

	i = -1;
    flood_fill(map, map->y, map->x);
    if (map->flag == 42)
        return (err("Error: the map is open.\n"));
    while (map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
			if (map->map[i][j] == 'X')
				map->map[i][j] = '0';
	}
	// printf("\n\n");
	// for (int i = 0; i <= map->rows; i++) {
    //     for (int j = 0; j < map->cols; j++) {
    //         printf("%c", map->map[i][j]);
    //     }
    //     printf("\n");
    // }
    return (1);
}
void flood_fill(t_map *map, int y, int x)
{
    if (x < 0 || x > map->cols || y < 0 || y > map->rows || map->flag == 42)
	{
		map->flag = 42;
        return ;
    }
    if (map->map[y][x] == '1' || map->map[y][x] == 'X')
        return ;
    map->map[y][x] = 'X';
    flood_fill(map, y + 1, x);
    flood_fill(map, y - 1, x);
    flood_fill(map, y, x + 1);
    flood_fill(map, y, x - 1);
	flood_fill(map, y + 1, x + 1);
    flood_fill(map, y + 1, x - 1);
	flood_fill(map, y - 1, x + 1);
    flood_fill(map, y - 1, x - 1);
}

int ft_close(void)
{
	//free_game()
	exit(0);
}

void play(t_map *map)
{
	t_game *game;
	
	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return ;
	game->mlx = mlx_init();
	game->window = mlx_new_window(game->mlx, map->cols * 64, map->rows * 64, "CUB3D");
	mlx_hook(game->window, 17, 1L << 2, ft_close, game);
	mlx_loop(game->mlx);
}
