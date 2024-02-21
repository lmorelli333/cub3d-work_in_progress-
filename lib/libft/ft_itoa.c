/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/21 20:58:54 by lmorelli          #+#    #+#             */
/*   Updated: 2023/01/23 15:22:30 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	lenght_string(int n)
{
	long int	number;
	int			len;

	number = n;
	len = 1;
	if (number < 0)
	{
		len++;
		number = -number;
	}
	while (number >= 10)
	{
		number = number / 10;
		len++;
	}
	return (len);
}

char	*ft_itoa(int n)
{
	char		*stringa;
	long int	number;
	long int	len;

	len = lenght_string(n);
	number = n;
	stringa = (char *)malloc(len + 1);
	if (!stringa)
		return (NULL);
	if (number < 0)
	{
		number = -number;
		*stringa = '-';
	}
	stringa[len] = '\0';
	len--;
	while (number >= 10)
	{
		stringa[len] = 48 + (number % 10);
		number /= 10;
		len--;
	}
	if (number >= 0 && number < 10)
		stringa[len] = 48 + (number % 10);
	return (stringa);
}
