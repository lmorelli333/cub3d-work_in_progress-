#include "../cub.h"

void	move_up(t_ray *ray, double speed_move, t_map *map)
{
	if (map->map[(int)ray->pos_y]
		[(int)(ray->pos_x + ray->dir_x * speed_move)] == '0')
		ray->pos_x += ray->dir_x * speed_move;
	if (map->map[(int)(ray->pos_y + ray->dir_y
			* speed_move)]
		[(int)(ray->pos_x)] == '0')
		ray->pos_y += ray->dir_y
			* speed_move;
}

void	move_down(t_ray *ray, double speed_move, t_map *map)
{
	if (map->map[(int)ray->pos_y]
		[(int)(ray->pos_x - ray->dir_x * speed_move)] == '0')
		ray->pos_x -= ray->dir_x * speed_move;
	if (map->map[(int)(ray->pos_y - ray->dir_y
			* speed_move)]
		[(int)ray->pos_x] == '0')
		ray->pos_y -= ray->dir_y * speed_move;
}

void	move_left(t_ray *ray, double speed_move, t_map *map)
{
	if (map->map[(int)ray->pos_y]
		[(int)(ray->pos_x - ray->dir_y * speed_move)] == '0')
		ray->pos_x -= ray->dir_y * speed_move;
	if (map->map[(int)(ray->pos_y
			+ ray->dir_x * speed_move)]
		[(int)(ray->pos_x)] == '0')
		ray->pos_y += (ray->dir_x) * speed_move;
}

void	move_right(t_ray *ray, double speed_move, t_map *map)
{
	if (map->map[(int)ray->pos_y]
		[(int)(ray->pos_x + ray->dir_y * speed_move)] == '0')
		ray->pos_x += ray->dir_y * speed_move;
	if (map->map[(int)(ray->pos_y
			- ray->dir_x * speed_move)][(int)ray->pos_x] == '0')
		ray->pos_y -= (ray->dir_x) * speed_move;
}

void	which_movement(t_ray *ray, t_map *map)
{
	double	speed_move;

	speed_move = ray->frame_time * 5.0;
	if (ray->dir_y == 1)
		move_up(ray, speed_move, map);
	if (ray->dir_y == -1)
		move_down(ray, speed_move, map);
	if (ray->dir_x == 1)
		move_right(ray, speed_move, map);
	if (ray->dir_x == -1)
		move_left(ray, speed_move, map);
}

// void	rotate_camera(float angle, t_game *game)
// {
// 	double	new_dir_x;
// 	double	new_dir_y;
// 	double	new_plane_x;
// 	double	new_plane_y;

// 	angle = angle * M_PI / 180.0f;
// 	new_dir_x = ray->dir_x * cos(angle)
// 		- ray->dir_y * sin(angle);
// 	new_dir_y = ray->dir_x * sin(angle)
// 		+ ray->dir_y * cos(angle);
// 	new_plane_x = ray->planex * cos(angle)
// 		- ray->planey * sin(angle);
// 	new_plane_y = ray->planex * sin(angle)
// 		+ ray->planey * cos(angle);
// 	ray->dir_x = new_dir_x;
// 	ray->dir_y = new_dir_y;
// 	ray->planex = new_plane_x;
// 	ray->planey = new_plane_y;
// }


// int	key_hook_release(int keycode, t_game *game, t_ray *ray)
// {
// 	if (key == 'w' || key == 's')
// 		ray->dir_y = 0;
// 	else if (key == 'a' || key == 'd')
// 		ray->dir_x = 0;
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
	printf("Tasto premuto: %d\n", keycode);
	if (keycode == 97)
		ray->dir_x = -1;
	else if (keycode == 115)
		ray->dir_y = -1;
	else if (keycode == 100)
		ray->dir_x = 1;
	else if (keycode == 119)
		ray->dir_y = 1;
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

