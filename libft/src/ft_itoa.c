/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/03 17:34:31 by hmoubal           #+#    #+#             */
/*   Updated: 2022/08/09 17:58:45 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

static int	calc_size(long int n)
{
	int	i;

	i = 0;
	while (n > 0)
	{
		n = n / 10;
		i++;
	}
	return (i);
}

static char	*sep_num(char *str,	int n,	int size)
{
	int	i;
	int	a;

	i = 0;
	a = n;
	if (n < 0)
		n = n * -1;
	str[size] = '\0';
	while (size-- != 0)
	{
		str[size] = n % 10 + 48;
		if (a < 0)
			str[i] = '-';
		n = n / 10;
	}
	return (str);
}

char	*ft_itoa(int n)
{
	int		i;
	char	*tab;

	i = 0;
	tab = NULL;
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	else if (n == 0)
		return (ft_strdup("0"));
	if (n > 0)
	{
		i = calc_size(n);
		tab = (char *)malloc(i + 1);
	}
	else if (n < 0)
	{
		i = calc_size(n * -1);
		tab = (char *)malloc(i + 2);
		i = i + 1;
	}
	if (tab == NULL)
		return (NULL);
	tab = sep_num(tab, n, i);
	return (tab);
}
