/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 14:40:55 by hmoubal           #+#    #+#             */
/*   Updated: 2022/08/09 17:58:45 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

int	ft_strncmp(const char *str,	const char *tab,	size_t a)
{
	size_t	i;

	i = 0;
	while (str[i] == tab[i] && a != 0 && str[i] != '\0' && tab[i] != '\0')
	{
		i++;
		a--;
	}
	if (a == 0)
		return (0);
	return ((unsigned char)str[i] - (unsigned char)tab[i]);
}
