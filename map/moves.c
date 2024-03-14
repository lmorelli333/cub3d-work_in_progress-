#include "../cub.h"

void	move_forward(t_ray *ray, double speed_move, t_map *map)
{
	if (map->map[(int)ray->posy]
		[(int)(ray->posx + ray->dirx * speed_move)] == '0')
		ray->posx += ray->dirx * speed_move;
	if (map->map[(int)(ray->posy + ray->diry
			* speed_move)]
		[(int)(ray->posx)] == '0')
		ray->posy += ray->diry
			* speed_move;
}

void	move_backward(t_ray *ray, double speed_move, t_map *map)
{
	if (map->map[(int)ray->posy]
		[(int)(ray->posx - ray->dirx * speed_move)] == '0')
		ray->posx -= ray->dirx * speed_move;
	if (map->map[(int)(ray->posy - ray->diry
			* speed_move)]
		[(int)ray->posx] == '0')
		ray->posy -= ray->diry * speed_move;
}

void	move_left(t_ray *ray, double speed_move, t_map *map)
{
	if (map->map[(int)ray->posy]
		[(int)(ray->posx - ray->diry * speed_move)] == '0')
		ray->posx -= ray->diry * speed_move;
	if (map->map[(int)(ray->posy
			+ ray->dirx * speed_move)]
		[(int)(ray->posx)] == '0')
		ray->posy += (ray->dirx) * speed_move;
}

void	move_right(t_ray *ray, double speed_move, t_map *map)
{
	if (map->map[(int)ray->posy]
		[(int)(ray->posx + ray->diry * speed_move)] == '0')
		ray->posx += ray->diry * speed_move;
	if (map->map[(int)(ray->posy
			- ray->dirx * speed_move)][(int)ray->posx] == '0')
		ray->posy -= (ray->dirx) * speed_move;
}

void	update_movement(t_ray *ray, t_map *map)
{
	double	speed_move;

	speed_move = ray->frame_time * 5.0;
	if (ray->diry == 1)
		move_forward(ray, speed_move, map);
	if (ray->diry == -1)
		move_backward(ray, speed_move, map);
	if (ray->dirx == -1)
		move_left(ray, speed_move, map);
	if (ray->dirx == 1)
		move_right(ray, speed_move, map);
}

// void	rotate_camera(float angle, t_game *game)
// {
// 	double	new_dir_x;
// 	double	new_dir_y;
// 	double	new_plane_x;
// 	double	new_plane_y;

// 	angle = angle * M_PI / 180.0f;
// 	new_dir_x = ray->dirx * cos(angle)
// 		- ray->diry * sin(angle);
// 	new_dir_y = ray->dirx * sin(angle)
// 		+ ray->diry * cos(angle);
// 	new_plane_x = ray->planex * cos(angle)
// 		- ray->planey * sin(angle);
// 	new_plane_y = ray->planex * sin(angle)
// 		+ ray->planey * cos(angle);
// 	ray->dirx = new_dir_x;
// 	ray->diry = new_dir_y;
// 	ray->planex = new_plane_x;
// 	ray->planey = new_plane_y;
// }


// int	key_hook_release(int keycode, t_game *game, t_ray *ray)
// {
// 	if (key == 'w' || key == 's')
// 		ray->diry = 0;
// 	else if (key == 'a' || key == 'd')
// 		ray->dirx = 0;
// 	else if (key == 65363 || key == 65361)
// 		ray->cam_dir = 0;
// 	return (0);
// }

// int	handle_mouse(int x, int y, void	*game)
// {
// 	double	normalized_x;
// 	double	max_rotation_angle;
// 	double	rotation_angle;
// 	double	new_rotation_angle;

// 	(void)y;
// 	mlx_mouse_hide(((t_game *)game)->mlx, ((t_game *)game)->mlx_win);
// 	normalized_x = (2.0f * x) / SCREENWIDTH - 1.0f;
// 	max_rotation_angle = 180.0f;
// 	rotation_angle = max_rotation_angle * normalized_x;
// 	new_rotation_angle = rotation_angle;
// 	if (((t_game *)game)->player->rot_angle != 360)
// 		new_rotation_angle = ((t_game *)game)->player->rot_angle
// 			- rotation_angle;
// 	((t_game *)game)->player->rot_angle = rotation_angle;
// 	rotate_camera(new_rotation_angle, (t_game *)game);
// 	return (0);
// }

int	ft_move(int keycode, t_ray *ray)
{
	if (keycode == 97)
		ray->dirx = -1;
	else if (keycode == 115)
		ray->diry = -1;
	else if (keycode == 100)
		ray->dirx = 1;
	else if (keycode == 119)
		ray->diry = 1;
	else if (keycode == 65307)
		ft_close();
	// else if (keycode == 65361)
	// 	ray->cam_dir = -1;
	// else if (keycode == 65363)
	// 	ray->cam_dir = 1;
	return (0);
}

// int	ft_move(int keycode, t_map *map, t_game *game)
// {
// 	check_player_position(map);
// 	printf("Tasto premuto: %d\n", keycode);
// 	if (keycode == 65307)
// 		ft_close();
// 	else if (keycode == 119)
// 	{
// 		printf("\n----ciao-----\n");
// 		mlx_clear_window(game->mlx, game->window);
// 		if (map->map[map->y - 1][map->x] == '0')
// 		{
// 			map->map[map->y][map->x] = '0';
// 			map->map[map->y - 1][map->x] = 'N';
// 		}
// 		printmatrix(map);
// 		put_img01(game, map);
// 	}
// 	else if (keycode == 115)
// 	{
// 		mlx_clear_window(game->mlx, game->window);
// 		if (map->map[map->y + 1][map->x] == '0')
// 		{
// 			map->map[map->y][map->x] = '0';
// 			map->map[map->y + 1][map->x] = 'S';
// 		}
// 		printmatrix(map);
// 		put_img01(game, map);
// 	}
// 	else if (keycode == 100)
// 	{
// 		mlx_clear_window(game->mlx, game->window);
// 		if (map->map[map->y][map->x + 1] == '0')
// 		{
// 			map->map[map->y][map->x] = '0';
// 			map->map[map->y][map->x + 1] = 'E';
// 		}
// 		printmatrix(map);
// 		put_img01(game, map);
// 	}
// 	else if (keycode == 97)
// 	{
// 		printf("\n=====CIAO\n");
// 		mlx_clear_window(game->mlx, game->window);
// 		if (map->map[map->y][map->x - 1] == '0')
// 		{
// 			map->map[map->y][map->x] = '0';
// 			map->map[map->y][map->x - 1] = 'W';
// 		}
// 		printmatrix(map);
// 		put_img01(game, map);
// 	}
// 	return (1);
// }

