/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:52:02 by lmorelli          #+#    #+#             */
/*   Updated: 2024/02/22 17:15:27 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef struct s_map
{
    char *mapv;
    char **mapm;
    int height;
    int width;
} t_map;

typedef struct s_boh
{
    void *mlx;
    void *win;

    void	*img;
	char	*addr;
    int		bits_per_pixel;
	int		line_length;
	int		endian;
} t_boh;

typedef struct s_player
{
    int up;
    int down;
    int left;
    int right;
    int rr_left;
    int rr_right;
}	t_player;

typedef struct s_all
{
    t_boh boh;
    t_player player;
    t_map map;
} t_all;

#endif