/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 16:29:11 by fcarlucc          #+#    #+#             */
/*   Updated: 2024/03/08 17:17:56 by fcarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	raycasting()
{
	int		i;
	t_ray	*ray;

	ray = (t_ray *)malloc(sizeof(t_ray));
	if (!ray)
		return (0);
	ray_init(ray);
	i = -1;
	while (++i < screenWidth)    //vedere se sostituire i con widtheight
	{
		calculate_ray_position_and_direction(ray, i);
		calculate_step_and_side_distances(ray);
		perform_dda(ray);
		calculate_distance_projected_on_camera(ray);
		calculate_pixels(ray);
	}
	return (0);
}

void ray_init(t_ray *ray)
{
	ray->mapX = 0;
	ray->mapY = 0;
	ray->posX = ray->map->x;
	ray->posY = ray->map->y;
	define_view(ray);
	ray->planeX = 0;
	ray->planeY = 0.66;
	ray->time = 0;
	ray->oldTime = 0;
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
	ray->hit = 0;
	ray->side = 0;
	ray->lineHeight = 0;
	ray->drawStart = 0;
	ray->drawEnd = 0;
}

void calculate_ray_position_and_direction(t_ray *ray, int i)
{
	ray->cameraX = 2 * i / (double)screenWidth - 1;
	ray->rayDirX = ray->dirX + ray->planeX * ray->cameraX;
	ray->rayDirY = ray->dirY + ray->planeY * ray->cameraX;
	ray->mapX = ray->posX;
	ray->mapY = ray->posY;
	if (ray->rayDirX == 0)
		ray->deltaDistX = 1e30;
	else
		ray->deltaDistX = fabs(1 / ray->rayDirX);
	if (ray->rayDirY == 0)
		ray->deltaDistY = 1e30;
	else
		ray->deltaDistY = fabs(1 / ray->rayDirY);
}

void calculate_step_and_side_distances(t_ray *ray)
{
	if (ray->rayDirX < 0)
	{
		ray->stepX = -1;
		ray->sideDistX = (ray->posX - ray->mapX) * ray->deltaDistX;
	}
	else
	{
		ray->stepX = 1;
		ray->sideDistX = (ray->mapX + 1.0 - ray->posX) * ray->deltaDistX;
	}
	if (ray->rayDirY < 0)
	{
		ray->stepY = -1;
		ray->sideDistY = (ray->posY - ray->mapY) * ray->deltaDistY;
	}
	else
	{
		ray->stepY = 1;
		ray->sideDistY = (ray->mapY + 1.0 - ray->posY) * ray->deltaDistY;
	}
}

void perform_dda(t_ray *ray)
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

void calculate_distance_projected_on_camera(t_ray *ray)
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

void define_view(t_ray *ray)
{
	if (ray->map->view == 'N')
	{
		ray->dirY = -1;
		ray->dirX = 0;
	}
	if (ray->map->view == 'S')
	{
		ray->dirY = 1;
		ray->dirX = 0;
	}
	if (ray->map->view == 'W')
	{
		ray->dirY = 0;
		ray->dirX = -1;
	}
	if (ray->map->view == 'E')
	{
		ray->dirY = 0;
		ray->dirX = 1;
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
