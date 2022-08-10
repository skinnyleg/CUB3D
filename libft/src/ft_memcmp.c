/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 16:59:12 by hmoubal           #+#    #+#             */
/*   Updated: 2022/08/09 17:58:45 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_memcmp(const void *p1,	const void *p2,	size_t size)
{
	unsigned char	*p;
	unsigned char	*t;
	size_t			i;

	p = (unsigned char *)p1;
	t = (unsigned char *)p2;
	i = 0;
	while (i < size)
	{
		if (p[i] != t[i])
			return (p[i] - t[i]);
		i++;
	}
	return (0);
}
