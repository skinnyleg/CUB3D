/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/21 21:29:56 by hmoubal           #+#    #+#             */
/*   Updated: 2022/09/21 22:12:51 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"
#include <stdio.h>
#include <stdlib.h>

void	init_height(int fd, t_global *all)
{
	char	*line;

	all->map->height = 1;
	line = get_next_line(fd);
	while (line != NULL)
	{
		line = ft_strtrim_free(line, " \t");
		if (*line != '\0')
			all->map->height++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

void	skip_line(int fd)
{
	char	*line;
	int		count;

	count = 0;
	line = get_next_line(fd);
	while (line != NULL && count != 5)
	{
		line = ft_strtrim_free(line, " \t");
		if (*line != '\0')
			count++;
		free(line);
		line = get_next_line(fd);
	}
	line = get_next_line(fd);
	free(line);
}

int	line_valid(char *line)
{
	char	*buffer;
	char	*rep;

	rep = ft_strdup(line);
	buffer = ft_strtrim_free(rep, " \t");
	if (*buffer == '\0')
		return (free(buffer), 1);
	return (free(buffer), 0);
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

int	array_fill(t_global *all)
{
	char	*line;
	int		i;

	i = 0;
	line = get_next_line(all->fd);
	while (line != NULL)
	{
		if (line_valid(line) == 0)
		{
			all->map->map[i] = ft_strdup(line);
			if (all->map->map[i] == NULL)
				return (free_2d(all->map->map, i), 1);
			i++;
		}
		free(line);
		line = get_next_line(all->fd);
	}
	all->map->map[i] = NULL;
	return (0);
}

int	fill_map2(t_global *all, char **av)
{
	all->fd = open(av[1], O_RDONLY);
	if (all->fd < 0)
		return (printf("can't open file\n"), 1);
	skip_line(all->fd);
	if (array_fill(all) == 1)
		return (1);
	return (0);
}

int	fill_map(char **av, t_global *all)
{
	all->map = (t_map *)malloc(sizeof(t_map) * 1);
	if (all->map == NULL)
		return (printf("malloc error\n"), close(all->fd), 1);
	init_height(all->fd, all);
	all->map->map = (char **) malloc(sizeof(char *) * (all->map->height + 1));
	if (all->map->map == NULL)
		return (printf("malloc error\n"), 1);
	if (fill_map2(all, av) == 1)
		return (free(all->map), 1);
	return (0);
}

int	parse_map_walls(char **av, t_global *all)
{
	fill_map(av, all);
	return (0);
}
