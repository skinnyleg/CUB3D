#include "../includes/CUB3D.h"

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
			change_line(all, &line);
			all->map->map[i] = ft_strdup(line);
			if (all->map->map[i] == NULL)
				return (free(line), free_2d(all->map->map, i), 1);
			i++;
		}
		free(line);
		line = get_next_line(all->fd);
	}
	all->map->map[i] = NULL;
	return (0);
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
	free(line);
	line = get_next_line(fd);
	free(line);
}

int	fill_map(t_global *all, char **av)
{
	all->fd = open(av[1], O_RDONLY);
	if (all->fd < 0)
		return (printf("can't open file\n"), 1);
	skip_line(all->fd);
	if (array_fill(all) == 1)
		return (1);
	return (0);
}

void	init_height(int fd, t_global *all)
{
	char	*line;

	all->map->height = 1;
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
	buffer = ft_strtrim_free(rep, " \t");
	if (*buffer == '\0')
		return (free(buffer), 1);
	return (free(buffer), 0);
}

