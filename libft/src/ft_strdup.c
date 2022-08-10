/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 18:54:22 by hmoubal           #+#    #+#             */
/*   Updated: 2022/08/09 17:58:45 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strdup(const char *src)
{
	char	*hub;
	int		i;
	int		len;

	hub = NULL;
	i = 0;
	len = 0;
	while (src[len] != '\0')
		len++;
	hub = malloc(len + 1);
	if (hub == NULL)
		return (NULL);
	while (src[i] != '\0')
	{
		hub[i] = src[i];
		i++;
	}
	hub[i] = '\0';
	return (hub);
}
