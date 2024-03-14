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
	update_movement(ray, map);
	return (0);
}

void	ray_init(t_ray *ray, t_map *map)
{
	ray->mapX = 0;
	ray->mapY = 0;
	ray->posx = (double)map->x;
	ray->posy = (double)map->y;
	define_view(ray, map);
	ray->planeX = 0;
	ray->planeY = 0.66;
	ray->cameraX = 0;
	ray->rayDirX = 0;
	ray->rayDirY = 0;
	ray->sideDistX = 0;
	ray->sideDistY = 0;
	ray->deltaDistX = 0;
	ray->deltaDistY = 0;
	ray->perpWallDist = 0;
	ray->stepX = 0;
	ray->stepY = 0;
	ray->hit = 1;
	ray->side = 0;
	ray->lineHeight = 0;
	ray->drawStart = 0;
	ray->drawEnd = 0;
	ray->diry = 0;
	ray->dirx = 0;
	ray->time = 0;
	ray->old_time = 0;
	//ray->map->map = map->map;
	//printmatrix2(map, ray->map->map);
}

void	calculate_ray_position_and_direction(t_ray *ray, int i)
{
	ray->cameraX = 2 * i / (double)screenWidth - 1;
	ray->rayDirX = ray->dirx + ray->planeX * ray->cameraX;
	ray->rayDirY = ray->diry + ray->planeY * ray->cameraX;
	ray->mapX = ray->posx;
	ray->mapY = ray->posy;
	if (ray->rayDirX == 0)
		ray->deltaDistX = 1e30;
	else
		ray->deltaDistX = fabs(1 / ray->rayDirX);
	if (ray->rayDirY == 0)
		ray->deltaDistY = 1e30;
	else
		ray->deltaDistY = fabs(1 / ray->rayDirY);
}

void	calculate_step_and_side_distances(t_ray *ray)
{
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (ray->posx - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - ray->posx) * ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (ray->posy - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - ray->posy) * ray->deltaDistY;
	}
}

void	perform_dda(t_ray *ray)
{
	while (ray->hit == 0)
	{
		if (ray->sideDistX < ray->sideDistY)
		{
			ray->sideDistX += ray->deltaDistX;
			ray->mapX += ray->stepX;
			ray->side = 0;
		}
		else
		{
			ray->sideDistY += ray->deltaDistY;
			ray->mapY += ray->stepY;
			ray->side = 1;
		}
		if (ray->map->map[ray->mapX][ray->mapY] > 0)
			ray->hit = 1;
	}
}

void	calculate_distance_projected_on_camera(t_ray *ray)
{
	if (ray->side == 0)
		ray->perpWallDist = ray->sideDistX - ray->deltaDistX;
	else
		ray->perpWallDist = ray->sideDistY - ray->deltaDistY;
}

void calculate_pixels(t_ray *ray)
{
	ray->lineHeight = (int)(screenHeight / ray->perpWallDist);
	ray->drawStart = -ray->lineHeight / 2 + screenHeight / 2;
	if (ray->drawStart < 0)
		ray->drawStart = 0;
	ray->drawEnd = ray->lineHeight / 2 + screenHeight / 2;
	if (ray->drawEnd >= screenHeight)
		ray->drawEnd = screenHeight - 1;
}

void define_view(t_ray *ray, t_map *map)
{
	if (map->view == 'N')
	{
		ray->diry = -1;
		ray->dirx = 0;
	}
	if (map->view == 'S')
	{
		ray->diry = 1;
		ray->dirx = 0;
	}
	if (map->view == 'W')
	{
		ray->diry = 0;
		ray->dirx = -1;
	}
	if (map->view == 'E')
	{
		ray->diry = 0;
		ray->dirx = 1;
	}
}

// void set_ray_color(t_ray *ray, t_map *map)         NON SO SE SERVE
// {
// 	int mapValue;
// 	mapValue = map->map[ray->mapX][ray->mapY];

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
