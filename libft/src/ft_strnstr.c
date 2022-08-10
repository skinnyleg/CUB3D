/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 15:09:28 by hmoubal           #+#    #+#             */
/*   Updated: 2022/08/09 17:58:45 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strnstr(const char *str,	const char *tab,	size_t a)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	if (*tab == '\0')
		return ((char *)str);
	while (*str && *tab && i < a)
	{
		if (str[i] == tab[0])
		{
			j = 0;
			while (str[i + j] == tab[j] && i + j < a)
			{
				if (tab[j++ + 1] == '\0')
					return ((char *)&str[i]);
			}
		}
		i++;
	}
	return (NULL);
}
