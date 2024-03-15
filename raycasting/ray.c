/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:29:11 by fcarlucc          #+#    #+#             */
/*   Updated: 2024/03/09 20:17:28 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	calculate_fps(t_ray *ray)
{
	//char	*number;

	ray->old_time = ray->time;
	ray->time = get_time();
	ray->frame_time = (ray->time - ray->old_time) / 1000.0;
	ray->fps = (int)(1.0 / ray->frame_time);
	if (ray->fps > 60)
	{
		ft_wait(((1.0 / 60) - ray->frame_time) * 1000);
		ray->time = get_time();
		ray->frame_time = (ray->time - ray->old_time) / 1000.0;
		ray->fps = (int)(1.0 / ray->frame_time);
	}
	// number = ft_itoa(game->fps);
	// mlx_string_put(game->mlx, cube->mlx_win,
	// 	SCREENWIDTH - 50, 20, -1, number);
	// free(number);
}

void    printmatrix2(t_map *m, char **mtx)
{
 for (int i = 0; i <= m->rows; i++) {
		for (int j = 0; j < m->cols; j++) {
			printf("%c", mtx[i][j]);
		}
		printf("\n");
}
}

int	raycasting(t_map *map)
{
	int		i;
	t_ray	*ray;

	ray = (t_ray *)malloc(sizeof(t_ray));
	if (!ray)
		return (0);
	ray_init(ray, map);
	i = -1;
	while (++i < screenWidth)    //vedere se sostituire i con widtheight
	{
		calculate_ray_position_and_direction(ray, i);
		calculate_step_and_side_distances(ray);
		perform_dda(ray);
		calculate_distance_projected_on_camera(ray);
		calculate_pixels(ray);
	}
	calculate_fps(ray);
	which_movement(ray, map);
	return (0);
}

void	ray_init(t_ray *ray, t_map *map)
{
	ray->map_x = 0;
	ray->map_y = 0;
	ray->pos_x = (double)map->x;
	ray->pos_y = (double)map->y;
	define_view(ray, map);
	ray->plane_x = 0;
	ray->plane_y = 0.66;
	ray->camera_x = 0;
	ray->raydir_x = 0;
	ray->raydir_y = 0;
	ray->sidedist_x = 0;
	ray->sidedist_y = 0;
	ray->delta_dist_x = 0;
	ray->delta_dist_y = 0;
	ray->perp_wall_dist = 0;
	ray->step_x = 0;
	ray->step_y = 0;
	ray->hit = 1;
	ray->side = 0;
	ray->line_height = 0;
	ray->draw_start = 0;
	ray->draw_end = 0;
	ray->dir_y = 0;
	ray->dir_x = 0;
	ray->time = 0;
	ray->old_time = 0;
	//ray->map->map = map->map;
	//printmatrix2(map, ray->map->map);
}

void	calculate_ray_position_and_direction(t_ray *ray, int i)
{
	ray->camera_x = 2 * i / (double)screenWidth - 1;
	ray->raydir_x = ray->dir_x + ray->plane_x * ray->camera_x;
	ray->raydir_y = ray->dir_y + ray->plane_y * ray->camera_x;
	ray->map_x = ray->pos_x;
	ray->map_y = ray->pos_y;
	if (ray->raydir_x == 0)
		ray->delta_dist_x = 1e30;
	else
		ray->delta_dist_x = fabs(1 / ray->raydir_x);
	if (ray->raydir_y == 0)
		ray->delta_dist_y = 1e30;
	else
		ray->delta_dist_y = fabs(1 / ray->raydir_y);
}

void	calculate_step_and_side_distances(t_ray *ray)
{
	if (ray->raydir_x < 0)
	{
		ray->step_x = -1;
		ray->sidedist_x = (ray->pos_x - ray->map_x) * ray->delta_dist_x;
	}
	else
	{
		ray->step_x = 1;
		ray->sidedist_x = (ray->map_x + 1.0 - ray->pos_x) * ray->delta_dist_x;
	}
	if (ray->raydir_y < 0)
	{
		ray->step_y = -1;
		ray->sidedist_y = (ray->pos_y - ray->map_y) * ray->delta_dist_y;
	}
	else
	{
		ray->step_y = 1;
		ray->sidedist_y = (ray->map_y + 1.0 - ray->pos_y) * ray->delta_dist_y;
	}
}

void	perform_dda(t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->sidedist_x < ray->sidedist_y)
		{
			ray->sidedist_x += ray->delta_dist_x;
			ray->map_x += ray->step_x;
			ray->side = 0;
		}
		else
		{
			ray->sidedist_y += ray->delta_dist_y;
			ray->map_y += ray->step_y;
			ray->side = 1;
		}
		if (ray->map->map[ray->map_x][ray->map_y] > 0)
			ray->hit = 1;
	}
}

void	calculate_distance_projected_on_camera(t_ray *ray)
{
	if (ray->side == 0)
		ray->perp_wall_dist = ray->sidedist_x - ray->delta_dist_x;
	else
		ray->perp_wall_dist = ray->sidedist_y - ray->delta_dist_y;
}

void calculate_pixels(t_ray *ray)
{
	ray->line_height = (int)(screenHeight / ray->perp_wall_dist);
	ray->draw_start = -ray->line_height / 2 + screenHeight / 2;
	if (ray->draw_start < 0)
		ray->draw_start = 0;
	ray->draw_end = ray->line_height / 2 + screenHeight / 2;
	if (ray->draw_end >= screenHeight)
		ray->draw_end = screenHeight - 1;
}

void define_view(t_ray *ray, t_map *map)
{
	if (map->view == 'N')
	{
		ray->dir_y = -1;
		ray->dir_x = 0;
	}
	if (map->view == 'S')
	{
		ray->dir_y = 1;
		ray->dir_x = 0;
	}
	if (map->view == 'W')
	{
		ray->dir_y = 0;
		ray->dir_x = -1;
	}
	if (map->view == 'E')
	{
		ray->dir_y = 0;
		ray->dir_x = 1;
	}
}

// void set_ray_color(t_ray *ray, t_map *map)         NON SO SE SERVE
// {
// 	int mapValue;
// 	mapValue = map->map[ray->map_x][ray->map_y];

// 	if (mapValue == 1)
// 		ray->color = 0xFF0000;
// 	else if (mapValue == 2)
// 		ray->color = 0x00FF00;
// 	else if (mapValue == 3)
// 		ray->color = 0x0000FF;
// 	else
// 		ray->color = 0xFFFF00;
// 	if (ray->side == 1)
// 		ray->color = ray->color / 2;
// }

// void draw_lines(t_game *game, int x, int y1, int y2, int color)
// {
// 	int y;

// 	y = y1;
// 	while (y <= y2)
// 	{
// 		mlx_pixel_put(game->mlx, game->window, x, y, color);
// 		y++;
// 	}
// }
