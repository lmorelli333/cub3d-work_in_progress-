/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/17 17:52:02 by lmorelli          #+#    #+#             */
/*   Updated: 2024/02/20 14:07:47 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTURE_H
# define STRUCTURE_H

typedef struct s_boh
{
    void *mlx;
    void *win;
} t_boh;

typedef struct s_player
{
	char	dir;
	double	dir_x;
	double	dir_y;
	double	pos_x;
	double	pos_y;
	double	plane_x;
	double	plane_y;
	int		mv_x;
	int		mv_y;
	int		rotate;
}	t_player;

typedef struct s_all
{
    t_boh boh;
    t_player player;  
} t_all;

#endif