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

void    printmatrix(t_map *map)
{
 for (int i = 0; i <= map->rows; i++) {
		for (int j = 0; j < map->cols; j++) {
			printf("%c", map->map[i][j]);
		}
		printf("\n");
}
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

int	ft_close(void)
{
	//free_game()
	exit(0);
}

void	put_img01(t_game *game, t_map *map)
{
	int	i;
	int	j;

	i = -1;
	while (map->map[++i])
	{
		j = -1;
		while (map->map[i][++j])
		{
			if (map->map[i][j] == '1')
				mlx_put_image_to_window(game->mlx, game->window,
					game->img->wall, j * 64, i * 64);
			else if (map->map[i][j] == '0')
				mlx_put_image_to_window(game->mlx, game->window,
					game->img->floor, j * 64, i * 64);
			else if (map->map[i][j] == 'N' || map->map[i][j] == 'E' || map->map[i][j] == 'W' || map->map[i][j] == 'S')
				mlx_put_image_to_window(game->mlx, game->window,
					game->img->player, j * 64, i * 64);
		}
	}
}

int	ft_move(int keycode, t_map *map, t_game *game)
{
	game = game;
	check_player_position(map);
	printf("Tasto premuto: %d\n", keycode);
	if (keycode == 65307)
		ft_close();
	else if (keycode == 119)
	{
		printf("\n----ciao-----\n");
		// mlx_clear_window(game->mlx, game->window);
		if (map->map[map->y - 1][map->x] == '0')
		{
			map->map[map->y][map->x] = '0';
			map->map[map->y - 1][map->x] = 'N';
		}
		printmatrix(map);
		// put_img01(game, map);
	}
	else if (keycode == 115)
	{
		// mlx_clear_window(game->mlx, game->window);
		if (map->map[map->y + 1][map->x] == '0')
		{
			map->map[map->y][map->x] = '0';
			map->map[map->y + 1][map->x] = 'S';
		}
		printmatrix(map);
		// put_img01(game, map);
	}
	else if (keycode == 100)
	{
		// mlx_clear_window(game->mlx, game->window);
		if (map->map[map->y][map->x + 1] == '0')
		{
			map->map[map->y][map->x] = '0';
			map->map[map->y][map->x + 1] = 'E';
		}
		printmatrix(map);
		// put_img01(game, map);
	}
	else if (keycode == 97)
	{
		// mlx_clear_window(game->mlx, game->window);
		if (map->map[map->y][map->x - 1] == '0')
		{
			map->map[map->y][map->x] = '0';
			map->map[map->y][map->x - 1] = 'W';
		}
		printmatrix(map);
		// put_img01(game, map);
	}
	return (1);
}


void	take_img(t_game *game)
{
	int	size_img;

	game->img = (t_img *)malloc(sizeof(t_img));
	if (!game->img)
		return ;
	size_img = 64;
	game->img->floor = mlx_xpm_file_to_image(game->mlx, "./back.xpm",
			&size_img, &size_img);
	game->img->wall = mlx_xpm_file_to_image(game->mlx, "./wall.xpm",
			&size_img, &size_img);
	game->img->player = mlx_xpm_file_to_image(game->mlx, "./playerR.xpm",
			&size_img, &size_img);
}

void	play(t_map *map)
{
	t_game	*game;

	printf("====> %c\n", map->map[map->y][map->x]);
	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return ;
	game->mlx = mlx_init();
	game->window = mlx_new_window(game->mlx, (map->cols - 1) * 64, (map->rows + 1) * 64, "CUB3D");
	game->image = mlx_new_image(game->mlx, map->cols * 64, map->rows * 64);
	game->address = mlx_get_data_addr(game->image, &game->bpp, &game->line_len, &game->endian);
	take_img(game);
	put_img01(game, map);
	mlx_loop_hook(game->mlx, raycasting, game);
	//mlx_put_image_to_window(game->mlx, game->window, game->image, 0, 0);
	mlx_hook(game->window, 2, 1L << 0, ft_move, map);
	mlx_hook(game->window, 17, 1L << 2, ft_close, game);
	mlx_loop(game->mlx);
}
