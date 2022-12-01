/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_up_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 20:40:54 by med-doba          #+#    #+#             */
/*   Updated: 2022/09/25 23:09:51 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

int	ft_check_ptr_0(char *ptr0)
{
	if (ft_strcmp(ptr0, "NO") == 0 || ft_strcmp(ptr0, "SO") == 0
		|| ft_strcmp(ptr0, "WE") == 0 || ft_strcmp(ptr0, "EA") == 0
		|| ft_strcmp(ptr0, "F") == 0 || ft_strcmp(ptr0, "C") == 0)
		return (0);
	return (-1);
}

int	check_double(t_paraup *up)
{
	t_paraup	*top;
	t_paraup	*tmp;
	int			i;

	top = up;
	tmp = up;
	while (top)
	{
		i = 0;
		while (tmp)
		{
			if (ft_strcmp(tmp->dir, top->dir) == 0)
			{
				i++;
				if (i > 1)
					return (1);
			}
			tmp = tmp->next;
		}
		tmp = up;
		top = top->next;
	}
	return (0);
}

char	*ft_strtrim_free(char const *s1, char const *set)
{
	int		j;
	int		i;
	char	*hub;

	if (!s1 || !set)
		return (NULL);
	j = 0;
	i = 0;
	while (ft_strchr(set, s1[i]) && s1[i] != '\0')
		i++;
	if (s1[i] == '\0')
	{
		hub = ft_strdup("");
		return (free((void *)s1), hub);
	}
	j = ft_strlen(s1);
	while (j != 0 && ft_strchr(set, s1[j - 1]))
		j--;
	hub = malloc(sizeof(char) * (j - i + 1));
	if (hub == NULL)
		return (NULL);
	ft_memcpy (hub, s1 + i, j - i + 1);
	hub[j - i] = '\0';
	free((void *)s1);
	return (hub);
}
