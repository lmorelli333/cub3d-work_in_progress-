/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:45:20 by fcarlucc          #+#    #+#             */
/*   Updated: 2024/03/06 04:20:51 by fcarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

size_t	ft_strlen(char *s)
{
	int	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	return (i);
}

int	ft_cleanbuff(char *buff)
{
	int	i;
	int	j;
	int	newline;

	i = 0;
	j = 0;
	newline = 0;
	while (buff[i])
	{
		if (newline)
			buff[j++] = buff[i];
		if (buff[i] == '\n')
			newline = 1;
		buff[i++] = '\0';
	}
	return (newline);
}

char	*ft_strjoin_next(char *s1, char *s2)
{
	int		i;
	char	*s3;

	i = 0;
	s3 = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (!s3)
		return (NULL);
	while (s1 && s1[i])
	{	
		s3[i] = s1[i];
		i++;
	}
	free(s1);
	while (*s2)
	{
		s3[i++] = *s2;
		if (*s2++ == '\n')
			break ;
	}
	s3[i] = '\0';
	return (s3);
}

char	*get_next_line(int fd)
{
	static char	buff[BUFFER_SIZE + 1];
	char		*readline;
	int			i;

	i = 0;
	if (BUFFER_SIZE < 1 || read(fd, buff, 0) < 0)
	{
		while (buff[i])
			buff[i++] = 0;
		return (NULL);
	}
	readline = NULL;
	while (*buff || read(fd, buff, BUFFER_SIZE) > 0)
	{
		readline = ft_strjoin_next(readline, buff);
		if (ft_cleanbuff(buff))
			break ;
	}
	return (readline);
}
