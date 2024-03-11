/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:47:15 by fcarlucc          #+#    #+#             */
/*   Updated: 2024/03/11 17:19:03 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB_H
# define CUB_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include <string.h>
# include <stdlib.h>
# include <math.h>

# include "./minilibx/mlx.h"

# define screenWidth 640
# define screenHeight 480

typedef struct s_map
{
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f_rgb; 		//capire come passare a mlx se da int o stringa
	char	*c_rgb; 		//e poi implementare colors.c/read_rgb(){}
	int		f[3];
	int		c[3];
	int		flag;
	int		cols;
	int		rows;
	int		y;
	int		x;
	char	view;
	//da freeare stringhe e struct
}		t_map;

typedef struct s_img
{
	void	*wall;
	void	*floor;
	void	*player;
}	t_img;

typedef struct s_game
{
	t_img	*img;
	void	*mlx;
	void	*window;
	void	*image;
	char	*address;
	int		bpp;
	int		line_len;
	int		endian;
}		t_game;

typedef struct s_ray
{
	double	posX;
	double	posY;
	double	dirX;
	double	dirY;
	double	planeX;
	double	planeY;
	double	time;
	double	oldTime;
	double	cameraX;
	double	rayDirX;
	double	rayDirY;
	double	sideDistX;
	double	sideDistY;
	double	deltaDistX;
	double	deltaDistY;
	double	perpWallDist;
	int		stepX;
	int		stepY;
	int		mapX;
	int		mapY;
	int		hit;
	int		side;
	int		lineHeight;
	int		drawStart;
	int		drawEnd;
	t_map *map;
}		t_ray;

char	*get_next_line(int fd);
char	**ft_split(char const *s, char c);

//utils.c
int		err(char *s);
char	*ft_strjoin(char *s1, char *s2);
size_t	len_number(int n);
char	*ft_itoa(int n);
int		ft_atoi(const char *str);

//map.c
void	init_map(t_map	*map);
// int		take_params(char *path);
int		take_params(t_map *map, char *path);
int		check_map(char *path);
int		purify_map(t_map *map, int fd, char *s);
char	*fix_map(t_map *map, char *s);//contolla se da gestire /r/f/v

void	take_colors(t_map *map);
//map_utils.c
int		check_extension(char *path);
void	textures_and_colors(t_map *map, char *s);
int		check_player(t_map *map, char *s);
void	find_rows_and_cols(t_map *map, char *s);

//check_map.c
int		is_playable(t_map *map);
void	flood_fill(t_map *map, int y, int x);
int		ft_close(void);
// int		ft_move(t_map *map, int keycode);
void	play(t_map *map);

//ray.c
int		raycasting(t_map *map);
void	ray_init(t_ray *ray, t_map *map);
void	define_view(t_ray *ray, t_map *map);
void	calculate_ray_position_and_direction(t_ray *ray, int i);
void	calculate_step_and_side_distances(t_ray *ray);
void	perform_dda(t_ray *ray);//Digital Differential Analyzer (traccia i raggi)
void	calculate_distance_projected_on_camera(t_ray *ray);
void	calculate_pixels(t_ray *ray);
// void set_ray_color(t_ray *ray);
// void draw_lines(t_game *game, int x, int y1, int y2, int color);

#endif


//check a textures_and_colors funzione
//capire perche non legge bene se non ce ultima riga vuota nella mappa(riguarda gnl)
//togliere decremento a rows se fixi gnl
//freeare matrici varie


//new_tasks


//sostituire definizioni screenWidth e screenheight con variabile col e rows *64?
//capire come fare drawing
//key hooks (anche press e release)
