/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 19:05:39 by hmoubal           #+#    #+#             */
/*   Updated: 2022/08/09 17:58:45 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

void	*ft_calloc(size_t	a, size_t	i)
{
	char	*hub;
	int		k;
	int		j;

	hub = NULL;
	k = 0;
	j = 0;
	if (a == 0 || i == 0)
	{
		i = 1;
		a = 1;
	}
	k = a * i;
	hub = malloc(k);
	if (hub == NULL)
		return (NULL);
	while (k != 0)
	{
		hub[j] = '\0';
		j++;
		k--;
	}
	return (hub);
}
