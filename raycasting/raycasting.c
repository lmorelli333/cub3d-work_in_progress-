/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/07 02:26:13 by fcarlucc          #+#    #+#             */
/*   Updated: 2024/03/07 04:26:05 by fcarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void ray_init(t_ray *ray)
{
    ray->dirY = 42;
    ray->dirX = 42;
    ray->planeY = 0.66;
    ray->planeX = 0;
    ray->cameraX = 0;
    ray->screenX = 0;
    ray->rayDirY = 0;
    ray->rayDirX = 0;
    ray->posX = 0;
    ray->posY = 0;
    ray->mapX = 0;
    ray->mapY = 0;
    ray->sideDistX = 0;
    ray->sideDistY = 0;
    ray->deltaDistX = 0;
    ray->deltaDistY = 0;
    ray->stepX = 0;
    ray->stepY = 0;
    ray->side = 0;
    ray->hit = 0;
    ray->perpWallDist = 0;
    ray->lineHeight = 0;
    ray->drawStart = 0;
    ray->drawEnd = 0;
	ray->color = 0;
}

void raycast(t_map *map)
{
    int     i;
    t_ray   *ray;

    i = -1;
    ray = (t_ray *)malloc(sizeof(t_ray));
	if (!ray)
		return ; // return (0);
    ray_init(ray);
    define_view(ray, map);
    while  (++i < screenWidth)
    {
        calculate_ray_directions(ray, i);
        ray->mapX = (int)ray->posX;
        ray->mapY = (int)ray->posY;
        ray->deltaDistX = fabs(1 / ray->rayDirX);
        ray->deltaDistY = fabs(1 / ray->rayDirY);
        initialize_step_and_side_distances(ray);
        ray->hit = 0;
        perform_dda(ray, map);
        calculate_perpendicular_wall_distance(ray);
        calculate_draw_height(ray);
        set_ray_color(ray, map);
        draw_lines(ray->game, i, ray->drawStart, ray->drawEnd, ray->color);
    }
}

void define_view(t_ray *ray, t_map *map)
{
	if (map->view == 'N')
	{
		ray->dirY = -1;
		ray->dirX = 0;
	}
	if (map->view == 'S')
	{
		ray->dirY = 1;
		ray->dirX = 0;
	}
	if (map->view == 'W')
	{
		ray->dirY = 0;
		ray->dirX = -1;
	}
	if (map->view == 'E')
	{
		ray->dirY = 0;
		ray->dirX = 1;
	}
}


// void raycast(t_ray *ray, t_map *map)
// {
// 	ray_init(ray);
// 	define_view(map, ray);
	
//     for (int x = 0; x < screenWidth; x++)
//     {
//         ray->cameraX = 2 * x / (double)screenWidth - 1;
//         ray->rayDirX = ray->dirX + ray->planeX * ray->cameraX;
//         ray->rayDirY = ray->dirY + ray->planeY * ray->cameraX;

//         ray->mapX = (int)ray->posX;
//         ray->mapY = (int)ray->posY;

//         ray->deltaDistX = fabs(1 / ray->rayDirX);
//         ray->deltaDistY = fabs(1 / ray->rayDirY);

//         if (ray->rayDirX < 0)
//         {
//             ray->stepX = -1;
//             ray->sideDistX = (ray->posX - ray->mapX) * ray->deltaDistX;
//         }
//         else
//         {
//             ray->stepX = 1;
//             ray->sideDistX = (ray->mapX + 1.0 - ray->posX) * ray->deltaDistX;
//         }
//         if (ray->rayDirY < 0)
//         {
//             ray->stepY = -1;
//             ray->sideDistY = (ray->posY - ray->mapY) * ray->deltaDistY;
//         }
//         else
//         {
//             ray->stepY = 1;
//             ray->sideDistY = (ray->mapY + 1.0 - ray->posY) * ray->deltaDistY;
//         }

//         ray->hit = 0;
        
//         while (ray->hit == 0)
//         {
//             if (ray->sideDistX < ray->sideDistY)
//             {
//                 ray->sideDistX += ray->deltaDistX;
//                 ray->mapX += ray->stepX;
//                 ray->side = 0;
//             }
//             else
//             {
//                 ray->sideDistY += ray->deltaDistY;
//                 ray->mapY += ray->stepY;
//                 ray->side = 1;
//             }
//             if (map->map[ray->mapX][ray->mapY] > 0)
//             {
//                 ray->hit = 1;
//             }
//         }

//         if (ray->side == 0)
//         {
//             ray->perpWallDist = (ray->mapX - ray->posX + (1 - ray->stepX) / 2) / ray->rayDirX;
//         }
//         else
//         {
//             ray->perpWallDist = (ray->mapY - ray->posY + (1 - ray->stepY) / 2) / ray->rayDirY;
//         }

//         ray->lineHeight = (int)(screenHeight / ray->perpWallDist);
//         ray->drawStart = -ray->lineHeight / 2 + screenHeight / 2;
//         if (ray->drawStart < 0)
//         {
//             ray->drawStart = 0;
//         }
//         ray->drawEnd = ray->lineHeight / 2 + screenHeight / 2;
//         if (ray->drawEnd >= screenHeight)
//         {
//             ray->drawEnd = screenHeight - 1;
//         }

// 		switch (map->map[ray->mapX][ray->mapY])
// 		{
// 			case 1:
// 				ray->color = 0xFF0000;
// 				break;
// 			case 2:
// 				ray->color = 0x00FF00;
// 				break;
// 			case 3:
// 				ray->color = 0x0000FF;
// 				break;
// 			default:
// 				ray->color = 0xFFFF00;
// 				break;
// 		}

//         if (ray->side == 1)
//         {
//             ray->color = ray->color / 2;
//         }

//         verLine(x, ray->drawStart, ray->drawEnd, ray->color);
//     }
// }

