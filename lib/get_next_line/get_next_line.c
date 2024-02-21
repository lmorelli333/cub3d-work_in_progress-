/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <lmorelli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/02/06 19:53:07 by lmorelli          #+#    #+#             */
/*   Updated: 2024/02/20 19:27:25 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_read_res(int fd, char *res)
{
	char	*temp;
	int		bytes;

	temp = malloc(BUFFER_SIZE + 1);
	if (!temp)
		return (NULL);
	bytes = 1;
	while (!ft_strchr_gnl(res, '\n') && bytes != 0)
	{
		bytes = read(fd, temp, BUFFER_SIZE);
		if (bytes == -1)
		{
			free (temp);
			return (NULL);
		}
		temp[bytes] = '\0';
		res = ft_strjoin_gnl(res, temp);
	}
	free (temp);
	return (res);
}

char	*get_next_line(int fd)
{
	static char	*res;
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (0);
	res = ft_read_res(fd, res);
	if (!res)
		return (NULL);
	line = ft_write_line(res);
	res = ft_new_res(res);
	return (line);
}
