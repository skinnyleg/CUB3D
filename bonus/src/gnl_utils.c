/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 18:26:25 by hmoubal           #+#    #+#             */
/*   Updated: 2022/12/03 22:44:21 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

char	*ft_strjoin_free(char *s1,	char *s2)
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
		return (free(s1), NULL);
	i = 0;
	j = 0;
	while (s1[i] != '\0')
	{
		tab[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
		tab[i++] = s2[j++];
	tab[k] = '\0';
	free(s1);
	return (tab);
}
