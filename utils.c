/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:32:20 by fcarlucc          #+#    #+#             */
/*   Updated: 2024/02/26 17:27:33 by fcarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub.h"

int	err(char *s)
{
    while (*s)
        write(2, s++, 1);
    return 0;
}

char	*take_map(char *s1, char *s2) //strjoin
{
	char	*res;
	size_t	i;
	size_t	len1;
	size_t	len2;

	if (!s1)
		len1 = 0;
	else
		len1 = strlen(s1);
	if (!s2)
		len2 = 0;
	else
		len2 = strlen(s2);
	res = malloc(len1 + len2 + 1);
	i = -1;
	res[len1 + len2] = 0;
	while (++i < len1)
		res[i] = s1[i];
	i = -1;
	while (++i < len2)
		res[len1 + i] = s2[i];
	free(s2);
	return (res);
}

void	init_map(t_map	*map)
{
	map->map = NULL;
	map->no = NULL;
	map->so = NULL;
	map->we = NULL;
	map->ea = NULL;
	map->f = NULL;
	map->c = NULL;
	map->ok = 0;
	return ;
}

int	check_extension(char *path)
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	if (path[i - 1] != 'b' || path[i - 2] != 'u' || path[i - 3] != 'c')
		return (err("Error: your extension must be '.cub' .\n"));
	return (1);
}

void	split_coordinates(t_map *map, char *s)      //controlla se possono esserci spazi vuoti all' ínizio
{
	if (s[0] == 'N' && s[1] == 'O' && s[2] == ' ')
		map->no = s;
	else if (s[0] == 'S' && s[1] == 'O' && s[2] == ' ')
		map->so = s;
	else if (s[0] == 'W' && s[1] == 'E' && s[2] == ' ')
		map->we = s;
	else if (s[0] == 'E' && s[1] == 'A' && s[2] == ' ')
		map->ea = s;
	else if (s[0] == 'F' && s[1] == ' ')
		map->f = s;
	else if (s[0] == 'C' && s[1] == ' ')
		map->c = s;
	if (map->no && map->so && map->we && map->ea && map->f && map->c)
		map->ok = 1;
	return ;
}

int	take_params(char *path)
{
	int		fd;
	char	*s;
	t_map	*map;
	
	map = (t_map *)malloc(sizeof(t_map));
	if (!map)
		return (0);
	init_map(map);
	if (check_extension(path))
	{
		fd = open(path, O_RDONLY);
		s = get_next_line(fd);
		while (!map->ok)
		{
			split_coordinates(map, s);
			s = get_next_line(fd);
		}
		printf("%s\n%s\n%s\n%s\n%s\n%s\n", map->no ,map->so ,map->we ,map->ea ,map->f ,map->c);
		if (!map->ok)
			return (err("Error: your map haven't all instructions for start.\n"));
		purify_map(map, fd, s);
		close(fd);
		return (1);
	}
	return 0;
}

int	purify_map(t_map *map, int fd, char *s)
{
	char	*res;

	s = get_next_line(fd);
	res = take_map("", s);
	while (s)
	{
		s = get_next_line(fd);
		if (s)
			res = take_map(res, s);
	}
	printf("%s\n", res);
	res = fix_map(res);
	map->map = ft_split(res, '\n');
	free(res);
	if (!map->map)
		return (err("Error: problems in reading the map\n"));
	return (1);
}

void	dddddd(t_map *map)
{

}

char	*fix_map(char *s) //contolla se da gestire /r/f/v
{
	int		i;
	int		j;
	int		max;
	char	*res;

	i = -1;
	max = 0;
	while (s[++i])
		if (s[i] == '\t')
			max += 4;
	res = malloc((i + max) * sizeof(char *));
	i = -1;
	j = -1;
	while (s[i])
	{
		if (s[++i] == ' ')
			res[++j] = '0';
		else if (s[++i] == '\t')
		{
			s[++j] = '0';
			s[++j] = '0';
			s[++j] = '0';
			s[++j] = '0';
		}
		res[++j] = s[++i];
	}
	free(s);
	return (res);
}
