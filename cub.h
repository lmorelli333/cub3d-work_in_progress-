/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:47:15 by fcarlucc          #+#    #+#             */
/*   Updated: 2024/02/28 06:45:43 by fcarlucc         ###   ########.fr       */
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

# include "./minilibx/mlx.h"

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
	int		ok;
	int		max;
	int		lines;
	//da freeare stringhe e struct
}		t_map;

typedef struct s_player
{
	int		y;
	int		x;
	char	**field;
	t_map	*map;
}		t_player;

typedef struct s_game
{
	void		*mlx;
	void		*window;
}		t_game;

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
int		take_params(char *path);
int		purify_map(t_map *map, int fd, char *s);
char	*fix_map(t_map *map, char *s);//contolla se da gestire /r/f/v

//map_utils.c
int		check_extension(char *path);
void	split_coordinates(t_map *map, char *s);
int		check_player(char *s);
void	find_len_and_lines(t_map *map, char *s);

//check_map.c
void	find_player(t_map *map, char *s);
void	play(t_map *map);

#endif

//salvare mappa in matrice e riempire con 0 gli spazi
//verificare che non ci sia piu di un player
//check esistenza/doppi path punti cardinali t_map (capire se necessario da subject)
//convertire i colori


//verificare la mappa che sia valida
//check a split_coordinates funzione
//capire perche non legge bene se non ce ultima riga vuota nella mappa(riguarda gnl)
//freeare matrici varie