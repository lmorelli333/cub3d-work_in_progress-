/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lmorelli <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/18 17:15:03 by lmorelli          #+#    #+#             */
/*   Updated: 2023/01/21 17:49:55 by lmorelli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*stringa1;
	unsigned char	*stringa2;

	stringa1 = (unsigned char *)s1;
	stringa2 = (unsigned char *)s2;
	i = -1;
	while (++i < n)
	{
		if (stringa1[i] != stringa2[i])
			return (stringa1[i] - stringa2[i]);
	}
	return (0);
}
