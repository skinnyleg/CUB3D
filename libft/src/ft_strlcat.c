/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 19:46:15 by hmoubal           #+#    #+#             */
/*   Updated: 2022/08/09 17:58:45 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

size_t	ft_strlcat(char *dest,	const char *src,	size_t size)
{
	unsigned int	i;
	unsigned int	s_dest;
	unsigned int	s_src;

	s_dest = 0;
	s_src = 0;
	i = 0;
	while (dest[s_dest] != '\0')
		s_dest++;
	while (src[s_src] != '\0')
		s_src++;
	if (size <= s_dest)
		return (s_src + size);
	while (i < size - (s_dest + 1) && src[i] != '\0')
	{
		dest[s_dest + i] = src[i];
		i++;
	}
	dest[s_dest + i] = '\0';
	return (s_dest + s_src);
}
