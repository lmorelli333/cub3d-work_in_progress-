/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fcarlucc <fcarlucc@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/26 10:32:20 by fcarlucc          #+#    #+#             */
/*   Updated: 2024/02/28 03:21:54 by fcarlucc         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub.h"

int	err(char *s)
{
	//write(2, "Error : ", 7)
    while (*s)
        write(2, s++, 1);
    return (0);
}

char	*ft_strjoin(char *s1, char *s2)
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

size_t	len_number(int n)
{
	long int	nbr;
	int			len;

	nbr = n;
	len = 1;
	if (nbr < 0)
	{
		len++;
		nbr = -nbr;
	}
	while (nbr >= 10)
	{
		nbr = nbr / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*str;
	long int	nbr;
	long int	len;

	len = len_number(n);
	nbr = n;
	str = (char *)malloc(len + 1);
	if (!str)
		return (NULL);
	if (nbr < 0)
	{
		nbr = -nbr;
		*str = '-';
	}
	str[len] = '\0';
	len--;
	while (nbr >= 10)
	{
		str[len] = 48 + (nbr % 10);
		nbr /= 10;
		len--;
	}
	if (nbr >= 0 && nbr < 10)
		str[len] = 48 + (nbr % 10);
	return (str);
}

int	ft_atoi(const char *str)
{
	int	i;
	int	s;
	int	res;

	i = 0;
	s = 1;
	res = 0;
	while (str[i] == 32 || (str[i] >= 9 && str[i] <= 13))
		i++;
	if (str[i] == '-' || str[i] == '+')
	{
		if (str[i] == '-')
			s = -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		res = (res * 10) + (str[i] - '0');
		i++;
	}
	return (res * s);
}
