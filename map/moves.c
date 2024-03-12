#include "../cub.h"

int	ft_move(int keycode, t_map *map, t_game *game)
{
	game = game;
	if (!game->mlx)
		printf("\n\n\n_______coglione_____\n");
	if (!game->window)
		printf("\n\n\n_______coglione_____\n");
	if (!map->map)
		printf("\n\n\n_______coglione_____\n");
	check_player_position(map);
	printf("Tasto premuto: %d\n", keycode);
	if (keycode == 65307)
		ft_close();
	else if (keycode == 119)
	{
		printf("\n----ciao-----\n");
		mlx_clear_window(game->mlx, game->window);
		if (map->map[map->y - 1][map->x] == '0')
		{
			map->map[map->y][map->x] = '0';
			map->map[map->y - 1][map->x] = 'N';
		}
		printmatrix(map);
		put_img01(game, map);
	}
	else if (keycode == 115)
	{
		mlx_clear_window(game->mlx, game->window);
		if (map->map[map->y + 1][map->x] == '0')
		{
			map->map[map->y][map->x] = '0';
			map->map[map->y + 1][map->x] = 'S';
		}
		printmatrix(map);
		put_img01(game, map);
	}
	else if (keycode == 100)
	{
		mlx_clear_window(game->mlx, game->window);
		if (map->map[map->y][map->x + 1] == '0')
		{
			map->map[map->y][map->x] = '0';
			map->map[map->y][map->x + 1] = 'E';
		}
		printmatrix(map);
		put_img01(game, map);
	}
	else if (keycode == 97)
	{
		printf("\n=====CIAO\n");
		mlx_clear_window(game->mlx, game->window);
		if (map->map[map->y][map->x - 1] == '0')
		{
			map->map[map->y][map->x] = '0';
			map->map[map->y][map->x - 1] = 'W';
		}
		printmatrix(map);
		put_img01(game, map);
	}
	return (1);
}

