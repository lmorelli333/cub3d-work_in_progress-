/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/28 04:00:22 by fcarlucc          #+#    #+#             */
/*   Updated: 2024/03/08 21:47:01 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

// void    printmatrix(t_map *map)
// {
//  for (int i = 0; i <= map->rows; i++) {
// 		for (int j = 0; j < map->cols; j++) {
// 			printf("%c", map->map[i][j]);
// 		}
// }
// }

int	is_playable(t_map *map)
{
	int	i;
	int	j;

	i = -1;
	flood_fill(map, map->y, map->x);
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

int	ft_close(void)
{
	//free_game()
	exit(0);
}

int	ft_move(int keycode, t_map *map)
{
	printf("Tasto premuto: %d\n", keycode);
	if (keycode == 65307)
		ft_close();
	else if (keycode == 119)
	{
		printf("X = %d Y = %d\n", map->x, map->y);
		map->map[map->y][map->x] = '0';
		map->map[map->y - 1][map->x] = 'N';
		//printmatrix(map);
	}
	else if (keycode == 115)
	{
		printf("X = %d Y = %d\n", map->x, map->y);
		map->map[map->y][map->x] = '0';
		map->map[map->y + 1][map->x] = 'S';
		//printmatrix(map);
	}
	else if (keycode == 100)
	{
		printf("X = %d Y = %d\n", map->x, map->y);
		map->map[map->y][map->x] = '0';
		map->map[map->y][map->x + 1] = 'E';
		//printmatrix(map);
	}
	else if (keycode == 97)
	{
		printf("X = %d Y = %d\n", map->x, map->y);
		map->map[map->y][map->x] = '0';
		map->map[map->y][map->x - 1] = 'W';
		//printmatrix(map);
	}
	return (1);
}

void	play(t_map *map)
{
	t_game	*game;

	printf("X GIUSTO = %d Y GIUSTO = %d\n", map->x, map->y);
	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return ;
	game->mlx = mlx_init();
	game->window = mlx_new_window(game->mlx, map->cols * 64, map->rows * 64, "CUB3D");
	game->image = mlx_new_image(game->mlx, map->cols * 64, map->rows * 64);
	game->address = mlx_get_data_addr(game->image, &game->bpp, &game->line_len, &game->endian);
	//mlx_loop_hook(game->mlx, raycasting, 0);
	mlx_put_image_to_window(game->mlx, game->window, game->image, 0, 0);
	mlx_key_hook(game->window, ft_move, game);
	mlx_hook(game->window, 17, 1L << 2, ft_close, game);
	mlx_loop(game->mlx);
}
