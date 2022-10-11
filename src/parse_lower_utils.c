/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lower_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:23:47 by hmoubal           #+#    #+#             */
/*   Updated: 2022/10/11 12:23:48 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

void	free_map(t_map *map)
{
	free_2d(map->map, map->height);
	free(map);
}

void	free_2d(char **map, int size)
{
	while (size != 0)
	{
		size--;
		free(map[size]);
	}
	free(map);
}

int	change_line(t_global *all, char **line)
{
	if (all->map->width > (int)ft_strlen(*line))
	{
		all->a = all->map->width - ft_strlen(*line);
		while (all->a != 0)
		{
			*line = ft_strjoin_free(*line, " ");
			all->a--;
		}
	}
	return (0);
}

int	check_cas(char c)
{
	if (c != '1' && c != '0' && c != ' '
		&& c != 'N' && c != 'S' && c != 'E' && c != 'W')
		return (1);
	return (0);
}

void	player_count(char c, int *count)
{
	if (c == 'N' || c == 'S' || c == 'E' || c == 'W')
		(*count)++;
}
