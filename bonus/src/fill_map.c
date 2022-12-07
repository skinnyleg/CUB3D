/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:23:19 by hmoubal           #+#    #+#             */
/*   Updated: 2022/12/07 20:18:24 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

int	array_fill(t_global *all)
{
	char	*line;
	int		i;
	int		ret;

	i = 0;
	line = get_next_line(all->fd);
	while (line != NULL)
	{
		ret = line_valid(line);
		if (ret == 0)
		{
			if (change_line(all, &line) == -1)
				return (1);
			all->map->map[i] = ft_strdup(line);
			if (all->map->map[i++] == NULL)
				return (free(line), 1);
		}
		else if ((i != 0 && i != all->map->height) || ret == -1)
			return (free(line), 1);
		free(line);
		line = get_next_line(all->fd);
	}
	if (map_size(all->map->map) < all->map->height)
		return (1);
	return (0);
}

int	skip_line(int fd)
{
	char	*line;
	int		count;

	count = 0;
	line = get_next_line(fd);
	while (line != NULL && count != 5)
	{
		line = ft_strtrim_free(line, " \t");
		if (line == NULL)
			return (-1);
		if (*line != '\0')
			count++;
		free(line);
		line = get_next_line(fd);
	}
	free(line);
	line = get_next_line(fd);
	free(line);
	return (0);
}

int	fill_map(t_global *all, char **av)
{
	all->fd = open(av[1], O_RDWR);
	if (all->fd < 0)
		return (1);
	if (skip_line(all->fd) == -1)
		return (close(all->fd), 1);
	if (array_fill(all) == 1)
		return (close(all->fd), 1);
	return (close(all->fd), 0);
}

void	init_height(int fd, t_global *all)
{
	char	*line;

	all->map->height = all->l;
	all->map->width = all->a;
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_strchr(line, '0') != NULL || ft_strchr(line, '1') != NULL)
		{
			if (all->map->width < (int)ft_strlen(line))
					all->map->width = ft_strlen(line);
			all->map->height++;
		}
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
}

int	line_valid(char *line)
{
	char	*buffer;
	char	*rep;

	rep = ft_strdup(line);
	if (rep == NULL)
		return (-1);
	buffer = ft_strtrim_free(rep, " \t");
	if (buffer == NULL)
		return (-1);
	if (*buffer == '\0')
		return (free(buffer), 1);
	return (free(buffer), 0);
}
