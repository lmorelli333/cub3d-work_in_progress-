/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 03:20:50 by fcarlucc          #+#    #+#             */
/*   Updated: 2024/03/07 04:23:46 by fcarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"


void calculate_ray_directions(t_ray *ray, int x)
{
    ray->cameraX = 2 * x / (double)screenWidth - 1;
    ray->rayDirX = ray->dirX + ray->planeX * ray->cameraX;
    ray->rayDirY = ray->dirY + ray->planeY * ray->cameraX;
}

void initialize_step_and_side_distances(t_ray *ray)
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

void perform_dda(t_ray *ray, t_map *map)
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
        if (map->map[ray->mapX][ray->mapY] > 0)
        {
            ray->hit = 1;
        }
    }
}

void calculate_perpendicular_wall_distance(t_ray *ray)
{
    if (ray->side == 0)
    {
        ray->perpWallDist = (ray->mapX - ray->posX + (1 - ray->stepX) / 2) / ray->rayDirX;
    }
    else
    {
        ray->perpWallDist = (ray->mapY - ray->posY + (1 - ray->stepY) / 2) / ray->rayDirY;
    }
}

void calculate_draw_height(t_ray *ray)
{
    ray->lineHeight = (int)(screenHeight / ray->perpWallDist);
    ray->drawStart = -ray->lineHeight / 2 + screenHeight / 2;
    if (ray->drawStart < 0)
    {
        ray->drawStart = 0;
    }
    ray->drawEnd = ray->lineHeight / 2 + screenHeight / 2;
    if (ray->drawEnd >= screenHeight)
    {
        ray->drawEnd = screenHeight - 1;
    }
}

void set_ray_color(t_ray *ray, t_map *map)
{
    int mapValue;
    mapValue = map->map[ray->mapX][ray->mapY];
    
    if (mapValue == 1)
        ray->color = 0xFF0000;
    else if (mapValue == 2)
        ray->color = 0x00FF00;
    else if (mapValue == 3)
        ray->color = 0x0000FF;
    else
        ray->color = 0xFFFF00;
    if (ray->side == 1)
        ray->color = ray->color / 2;
}

void draw_lines(t_game *game, int x, int y1, int y2, int color)
{
    int y;
    
    y = y1;
    while (y <= y2)
    {
        mlx_pixel_put(game->mlx, game->window, x, y, color);
        y++;
    }
}