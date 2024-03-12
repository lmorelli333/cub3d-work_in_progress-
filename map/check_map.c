/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 04:00:22 by fcarlucc          #+#    #+#             */
/*   Updated: 2024/03/11 17:49:30 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	check_map(char *path)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (0);
	init_map(map);
	if (take_params(map, path))
	{
		raycasting(map);
		return (1);
	}
	return (0);
}

int	is_playable(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	//flood_fill(map, map->y, map->x);
	if (map->flag == 42)
		return (err("Error: the map is open.\n"));
	for (int i = 0; i <= map->rows; i++) {
		for (int j = 0; j < map->cols; j++) {
			printf("%c", map->map[i][j]);
		}
		printf("\n");
	}
	while (map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
			if (map->map[i][j] == 'X')
				map->map[i][j] = '0';
	}
	printf("\n\n");
	for (int i = 0; i <= map->rows; i++) {
		for (int j = 0; j < map->cols; j++) {
			printf("%c", map->map[i][j]);
		}
		printf("\n");
	}
	return (1);
}

void	flood_fill(t_map *map, int y, int x)
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

void	check_player_position(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
		{
			if (map->map[i][j] == 'N' || map->map[i][j] == 'S' || map->map[i][j] == 'W' || map->map[i][j] == 'E')
			{
				map->y = i;
				map->x = j;
				map->flag++;
				map->view = map->map[i][j];
			}
			if (map->map[i][j] != 'N' && map->map[i][j] != 'S' && map->map[i][j] != 'W' && map->map[i][j] != 'E' && map->map[i][j] != '0' && map->map[i][j] != '1' && map->map[i][j] != '\n')
				return ;
		}
	}
}
