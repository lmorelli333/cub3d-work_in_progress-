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

void	play(t_map *map)
{
	t_game	*game;

	printf("====> %c\n", map->map[map->y][map->x]);
	game = (t_game *)malloc(sizeof(t_game));
	if (!game)
		return ;
	game->mlx = mlx_init();
	game->window = mlx_new_window(game->mlx, 1280, 960, "cub3d"); //oppure 64 *col o rows
	//game->image = mlx_new_image(game->mlx, map->cols * 64, map->rows * 64);
	//game->address = mlx_get_data_addr(game->image, &game->bpp, &game->line_len, &game->endian);
	take_img(game);
	put_img01(game, map);
	//mlx_put_image_to_window(game->mlx, game->window, game->image, 0, 0);
	mlx_hook(game->window, 17, 1L << 2, ft_close, game);
	mlx_hook(game->window, 2, 1L << 0, ft_move, map);
	// mlx_hook(cube->mlx_win, 3, 1L << 1, key_release, game);
	// mlx_hook(cube->mlx_win, 6, 1L << 6, mouse_mov, game);
	mlx_loop_hook(game->mlx, raycasting, game);
	mlx_loop(game->mlx);
}

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
