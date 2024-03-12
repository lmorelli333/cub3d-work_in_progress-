#include "../cub.h"

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
