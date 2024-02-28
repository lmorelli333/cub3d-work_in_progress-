/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/27 22:31:12 by fcarlucc          #+#    #+#             */
/*   Updated: 2024/02/28 04:43:01 by fcarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	check_extension(char *path)
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	if (path[i - 1] != 'b' || path[i - 2] != 'u' || path[i - 3] != 'c')
		return (err("Error: your extension must be '.cub' .\n\n"));
	return (1);
}

void	split_coordinates(t_map *map, char *s)
{
	if (*s == 32 || (*s >= 9 && *s <= 13))
		while (*s == 32 || (*s >= 9 && *s <= 13))
			s++;
	if (s[0] == 'N' && s[1] == 'O' && (s[2] == 32 || (s[2] >= 9 && s[2] <= 13)))
	{
		if (map->no)
            map->ok = -1;
		map->no = s;
	}
	else if (s[0] == 'S' && s[1] == 'O' && (s[2] == 32 || (s[2] >= 9 && s[2] <= 13)))
	{
		if (map->so)
            map->ok = -1;
		map->so = s;
	}
	else if (s[0] == 'W' && s[1] == 'E' && (s[2] == 32 || (s[2] >= 9 && s[2] <= 13)))
	{
		if (map->we)
            map->ok = -1;
		map->we = s;
	}
	else if (s[0] == 'E' && s[1] == 'A' && (s[2] == 32 || (s[2] >= 9 && s[2] <= 13)))
	{
		if (map->ea)
            map->ok = -1;
		map->ea = s;
	}
	else if (s[0] == 'F' && (s[1] == 32 || (s[1] >= 9 && s[1] <= 13)))
	{
		if (map->f_rgb)
            map->ok = -1;
		++s;
		map->f_rgb = ++s;
	}
	else if (s[0] == 'C' && (s[1] == 32 || (s[1] >= 9 && s[1] <= 13))) //sembra non funzionare solo con C provare su linux
	{
		if (map->c_rgb)
            map->ok = -1;
		++s;
		map->c_rgb = ++s;
	}
	if (map->no && map->so && map->we && map->ea && map->f_rgb && map->c_rgb)
		map->ok = 1;
	return ;
}

int	check_player(char *s)
{
	int i;
	int count;

	i = -1;
	count = 0;
	while (s[++i])
	{
		if (s[i] == 'N' || s[i] == 'S' || s[i] == 'W' || s[i] == 'E')
			count++;
		if (s[i] != 'N' && s[i] != 'S' && s[i] != 'W' && s[i] != 'E' && s[i] != '0' && s[i] != '1' && s[i] != '\n')
			return (0);
	}
	printf("%d\n", count);
	return (count);
		
}

void	find_len_and_lines(t_map *map, char *s)
{
	int i;
	int j;
	
	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] == '\t')
			j += 4;
		else if (s[i] != '\n')
			j++;
		else
		{
			j++;
			if (j > map->max)
				map->max = j;
			map->lines++;
			j = 0;
		}
		i++;
	}
	return ;
}

