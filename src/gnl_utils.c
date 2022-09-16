/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:26:25 by hmoubal           #+#    #+#             */
/*   Updated: 2021/11/16 22:21:01 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

char	*ft_strjoin_free(char const *s1,	char const *s2)
{
	char	*tab;
	size_t	i;
	size_t	j;
	int		k;

	if (!s1 || !s2)
		return (NULL);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	k = i + j;
	tab = (char *)malloc(k + 1);
	if (tab == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		tab[i] = (char)s1[i];
		i++;
	}
	while (s2[j] != '\0')
		tab[i++] = (char)s2[j++];
	tab[k] = '\0';
	free((char *)s1);
	return (tab);
}
