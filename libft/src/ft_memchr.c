/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 17:37:09 by hmoubal           #+#    #+#             */
/*   Updated: 2022/08/09 17:58:45 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_memchr(const void *tab,	int a,	size_t v)
{
	unsigned char	i;
	unsigned char	*p1;

	i = (unsigned char)a;
	p1 = (unsigned char *)tab;
	while (v > 0)
	{
		if (*p1 == i)
			return (p1);
		v--;
		p1++;
	}
	return (NULL);
}
