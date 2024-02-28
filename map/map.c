/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 22:25:27 by fcarlucc          #+#    #+#             */
/*   Updated: 2024/02/28 06:08:31 by fcarlucc         ###   ########.fr       */
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
	map->ok = 0;
	map->max = 0;

	return ;
}

int	take_params(char *path)
{
	int		fd;
	char	*s;
	char	**t;
	t_map	*map;
	
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (0);
	init_map(map);
	if (check_extension(path))
	{
		fd = open(path, O_RDONLY);
		s = get_next_line(fd);
		while (map->ok == 0)
		{
			split_coordinates(map, s);
			if (map->ok == -1)
				return (err("Error: invalid map parameters.\n"));
			s = get_next_line(fd);
		}
		printf("%s\n%s\n%s\n%s\n%s\n%s\n", map->no ,map->so ,map->we ,map->ea ,map->f_rgb ,map->c_rgb);
		if (!map->ok || !purify_map(map, fd, s))
			return (err("Error: invalid map.\n"));
		t = ft_split(map->f_rgb, ',');
		map->f[0] = ft_atoi(t[0]);
		map->f[1] = ft_atoi(t[1]);
		map->f[2] = ft_atoi(t[2]);
		//free_matrix
		t = ft_split(map->c_rgb, ','); //capiren se fare funzione dove converto in esadecimale il colore 
		map->c[0] = ft_atoi(t[0]);
		map->c[1] = ft_atoi(t[1]);
		map->c[2] = ft_atoi(t[2]);
		//free_matrix
		printf("\n\ncolors:\n\n%d\n%d\n%d\n%d\n%d\n%d\n%s\n%s\n", map->f[0] ,map->f[1] ,map->f[2] ,map->c[0] ,map->c[1],map->c[2], map->f_rgb, map->c_rgb);
		close(fd);
		return (1);
	}
	return (0);
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
	find_len_and_lines(map, res);
	res = fix_map(map, res);
	printf("\n\n%s\n\n\n%d\n%d", res, map->max, map->lines);
	if (check_player(res) != 1)
		return (err("Error: the map must contain 1 player.\n\n"));
	map->map = ft_split(res, '\n');
	if (!map->map)
		return (err("Error: problems in reading the map.\n\n"));
	find_player(map, res);
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
	res = malloc(((map->max * map->lines) + 1) * sizeof(char *));
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
			while (k < map->max && s[i] != 0)
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
