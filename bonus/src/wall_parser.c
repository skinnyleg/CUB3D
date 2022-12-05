/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall_parser.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:22:51 by hmoubal           #+#    #+#             */
/*   Updated: 2022/12/03 23:11:43 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

int	vertical_wall2(t_map *map, int i, int j)
{
	if (i == 0 && map->map[i][j] != ' ')
	{
		if (map->map[i][j] != '1')
			return (1);
	}
	else if (i == map->height - 1)
	{
		if (map->map[i][j] != ' ')
			if (map->map[i][j] != '1')
				return (1);
	}
	else if (i != 0 && map->map[i][j] != ' ')
	{
		if (map->map[i - 1][j] == ' ' || map->map[i + 1][j] == ' ')
			if (map->map[i][j] != '1')
				return (1);
	}
	return (0);
}

int	vertical_wall(t_map *map)
{
	int	i;
	int	j;

	j = 0;
	while (j < map->width)
	{
		i = 0;
		while (i < map->height)
		{
			if (vertical_wall2(map, i, j) == 1)
				return (1);
			i++;
		}
		j++;
	}
	return (0);
}

int	horizantal_wall2(t_map *map, int i, int j)
{
	if (j == 0 && map->map[i][j] != ' ')
	{
		if (map->map[i][j] != '1')
			return (1);
	}
	else if (j == map->width - 1)
	{
		if (map->map[i][j] != ' ')
			if (map->map[i][j] != '1')
				return (1);
	}
	else if (j != 0 && map->map[i][j] != ' ')
	{
		if (map->map[i][j - 1] == ' ' || map->map[i][j + 1] == ' ')
			if (map->map[i][j] != '1')
				return (1);
	}
	return (0);
}

int	horizantal_wall(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (horizantal_wall2(map, i, j) == 1)
				return (1);
			j++;
		}
		i++;
	}
	return (0);
}

int	check_contents(t_map *map)
{
	int	i;
	int	j;
	int	count;

	count = 0;
	i = 0;
	while (map->map[i] != NULL && i < map->height)
	{
		j = 0;
		while (j < map->width)
		{
			if (check_cas(map->map[i][j]) == 1)
				return (1);
			player_count(map->map[i][j], &count);
			j++;
		}
		i++;
	}
	if (count != 1)
		return (1);
	return (0);
}
