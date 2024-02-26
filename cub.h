/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/21 17:47:15 by fcarlucc          #+#    #+#             */
/*   Updated: 2024/02/26 17:21:28 by fcarlucc         ###   ########.fr       */
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

typedef struct s_map
{
	char	**map;
	char	*no;
	char	*so;
	char	*we;
	char	*ea;
	char	*f;
	char	*c;
	int		ok;
	//da freeare stringhe e struct
}		t_map;

char	*get_next_line(int fd);
char	**ft_split(char const *s, char c);

int		err(char *s);
char	*fix_map(char *s);
void	init_map(t_map	*map);
int		take_params(char *path);
int		check_extension(char *path);
char	*take_map(char *s1, char *s2);
void	split_coordinates(t_map *map, char *s);
int		purify_map(t_map *map, int fd, char *s);
#endif

//salvare mappa in matrice e riempire con 0 gli spazi
//convertire i colori
//verificare che non ci sia piu di un player
//verificare la mappa che sia valida
//check a split_coordinates funzione
//check esistenza/doppi path punti cardinali t_map