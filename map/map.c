/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 22:25:27 by fcarlucc          #+#    #+#             */
/*   Updated: 2024/03/07 04:45:38 by fcarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

void	init_map(t_map	*map)
{
	map->map = NULL;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->f_rgb = NULL;
	map->c_rgb = NULL;
	map->f[0] = 0;
	map->f[1] = 0;
	map->f[2] = 0;
	map->c[0] = 0;
	map->c[1] = 0;
	map->c[2] = 0;
	map->flag = 0;
	map->cols = 0;
	map->y = 0;
	map->x = 0;
	map->view = '$';
	return ;
}

int	check_map(char *path)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (0);
	init_map(map);
	if (take_params(map, path))
	{
		raycast(map);
		return (1);
	}
	return (0);
}

int	take_params(t_map *map, char *path)
{
	int		fd;
	char	*s;
	
	if (check_extension(path))
	{
		fd = open(path, O_RDONLY);
		s = get_next_line(fd);
		while (map->flag == 0)
		{
			textures_and_colors(map, s);
			if (map->flag == -1)
				return (err("Error: invalid map parameters.\n"));
			s = get_next_line(fd);
		}
		printf("%s\n%s\n%s\n%s\n%s\n%s\n", map->no ,map->so ,map->we ,map->ea ,map->f_rgb ,map->c_rgb);
		if (!map->flag || !purify_map(map, fd, s))
			return (err("Error: invalid map.\n"));
		take_colors(map);
		printf("\n\ncolors:\n\n%d\n%d\n%d\n%d\n%d\n%d\n%s\n%s\n", map->f[0] ,map->f[1] ,map->f[2] ,map->c[0] ,map->c[1],map->c[2], map->f_rgb, map->c_rgb);
		close(fd);
		return (1);
	}
	return (0);
}

// int	take_params(char *path)
// {
// 	int		fd;
// 	char	*s;
// 	t_map	*map;
	
// 	map = (t_map *)malloc(sizeof(t_map));
// 	if (!map)
// 		return (0);
// 	init_map(map);
// 	if (check_extension(path))
// 	{
// 		fd = open(path, O_RDONLY);
// 		s = get_next_line(fd);
// 		while (map->flag == 0)
// 		{
// 			textures_and_colors(map, s);
// 			if (map->flag == -1)
// 				return (err("Error: invalid map parameters.\n"));
// 			s = get_next_line(fd);
// 		}
// 		printf("%s\n%s\n%s\n%s\n%s\n%s\n", map->no ,map->so ,map->we ,map->ea ,map->f_rgb ,map->c_rgb);
// 		if (!map->flag || !purify_map(map, fd, s))
// 			return (err("Error: invalid map.\n"));
// 		take_colors(map);
// 		raycast(map);
// 		printf("\n\ncolors:\n\n%d\n%d\n%d\n%d\n%d\n%d\n%s\n%s\n", map->f[0] ,map->f[1] ,map->f[2] ,map->c[0] ,map->c[1],map->c[2], map->f_rgb, map->c_rgb);
// 		close(fd);
// 		return (1);
// 	}
// 	return (0);
// }

void	take_colors(t_map *map)
{
	char **colors;

	colors = ft_split(map->f_rgb, ',');
	map->f[0] = ft_atoi(colors[0]);
	map->f[1] = ft_atoi(colors[1]);
	map->f[2] = ft_atoi(colors[2]);
	//free_matrix
	colors = ft_split(map->c_rgb, ','); //capiren se fare funzione dove converto in esadecimale il colore 
	map->c[0] = ft_atoi(colors[0]);
	map->c[1] = ft_atoi(colors[1]);
	map->c[2] = ft_atoi(colors[2]);
	//free_matrix
}

int	purify_map(t_map *map, int fd, char *s)
{
	char	*res;

	s = get_next_line(fd);
	res = ft_strjoin("", s);
	while (s)
	{
		s = get_next_line(fd);
		if (s)
			res = ft_strjoin(res, s);
	}
	printf("%s\n", res);
	find_rows_and_cols(map, res);
	res = fix_map(map, res);
	if (check_player(map, res) != 1)
		return (err("Error: the map must contain 1 player.\n\n"));
	printf("\n\n%s\n\n\ncol%d\nrow%d\n%d\n%d", res, map->cols, map->rows, map->y, map->x);
	if (is_playable(map))
        play(map);
	else
	{
		free(res);
	    return (0);
	}
	free(res);
	return (1);
}

char	*fix_map(t_map *map, char *s) 
{
	int		i;
	int		j;
	int		k;
	char	*res;

	i = 0;
	j = 0;
	k = 1;
	res = malloc(((map->cols * map->rows) + 1) * sizeof(char *));
	if (!res)
		return (NULL);
	while (s[i])
	{
		if (s[i] == ' ')
			res[j] = '0';
		else if (s[i] == '\t')
		{
			res[j++] = '0';
			res[j++] = '0';
			res[j++] = '0';
			res[j] = '0';
			k += 3;
		}
		else if (s[i] == '\n')
		{
			while (k < map->cols && s[i] != 0)
			{
				res[j++] = '0';
				k++;
			}
			res[j] = '\n';
			k = 0;
		}
		else
			res[j] = s[i];
		i++;
		j++;
		k++;
	}
	res[j] = 0;
	free(s);
	return (res);
}
