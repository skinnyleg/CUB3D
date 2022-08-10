/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/02 16:24:21 by hmoubal           #+#    #+#             */
/*   Updated: 2022/08/09 17:58:45 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strtrim(char const *s1,	char const *set)
{
	size_t	j;
	char	*hub;

	j = 0;
	hub = NULL;
	if (!s1 || !set)
		return (NULL);
	while (*s1)
	{
		if (ft_strchr(set,*s1) == NULL)
			break ;
		s1++;
	}
	j = ft_strlen(s1);
	while (j != 0 && ft_strchr(set, s1[j - 1]) != NULL)
		j--;
	hub = (char *)malloc(j + 1);
	if (hub == NULL)
		return (NULL);
	ft_memcpy(hub, s1, j);
	hub[j] = '\0';
	return (hub);
}
