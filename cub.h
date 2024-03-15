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
# include <sys/time.h>
# include <sys/wait.h>
# include <time.h>

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
	char	view;
	int		f[3];
	int		c[3];
	int		flag;
	int		cols;
	int		rows;
	int		y;
	int		x;
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
	t_map *map;
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
	double	camera_x;
	double	raydir_x;
	double	raydir_y;
	double	sidedist_x;
	double	sidedist_y;
	double	delta_dist_x;
	double	delta_dist_y;
	double	perp_wall_dist;
	double	frame_time;
	double	time;
	double	old_time;
	int		step_x;
	int		step_y;
	int		map_x;
	int		map_y;
	int		hit;
	int		side;
	int		line_height;
	int		draw_start;
	int		draw_end;
	int		fps;
}		t_ray;


//utils.c
int		err(char *s);
int		ft_atoi(const char *str);
size_t	len_number(int n);
char	*get_next_line(int fd);
char	**ft_split(char const *s, char c);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_itoa(int n);
void	ft_wait(u_int64_t time);
u_int64_t	get_time(void);

//map.c
void	init_map(t_map	*map);
void	take_colors(t_map *map);
void    printmatrix(t_map *map);
void	check_player_position(t_map *map);
int		take_params(t_map *map, char *path);
int		check_map(char *path);
int		purify_map(t_map *map, int fd, char *s);
int		ft_move(int keycode, t_ray *ray);
char	*fix_map(t_map *map, char *s);//contolla se da gestire /r/f/v
//map_utils.c
int		check_extension(char *path);
int		check_player(t_map *map, char *s);
void	textures_and_colors(t_map *map, char *s);
void	find_rows_and_cols(t_map *map, char *s);
//check_map.c
int		is_playable(t_map *map);
int		ft_close(void);
void	flood_fill(t_map *map, int y, int x);
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

void	which_movement(t_ray *ray, t_map *map);

//img
void	take_img(t_game *game);
void	put_img01(t_game *game, t_map *map);

#endif


//check a textures_and_colors funzione
//capire perche non legge bene se non ce ultima riga vuota nella mappa(riguarda gnl)
//togliere decremento a rows se fixi gnl
//freeare matrici varie


//new_tasks


//sostituire definizioni screenWidth e screenheight con variabile col e rows *64?
//capire come fare drawing
//key hooks (anche press e release)
