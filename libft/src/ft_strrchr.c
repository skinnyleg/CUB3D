/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/01 12:41:38 by hmoubal           #+#    #+#             */
/*   Updated: 2022/08/09 17:58:45 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

char	*ft_strrchr(const char *str,	int a)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	while (i != 0 && str[i] != (unsigned char)a)
		i--;
	if (i == 0 && str[i] != (unsigned char)a)
		return (NULL);
	return ((char *)&str[i]);
}
