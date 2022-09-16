
#include "../includes/CUB3D.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int	line_valid(char *line)
{
	char	*rep;

	if (*line == '\0')
		return (1);
	rep = ft_strtrim(line, " ");
	printf("rep trim == %s\n", rep);
	return (0);
}

int	init_height(char **av, t_global *all)
{
	int		fd;
	char	*line;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (printf("can't open file\n"), 1);
	line = get_next_line(fd);
	while (line != NULL)
	{
		printf("line == %s\n", line);
		if (line_valid(line) == 0)
			all->map->height++;
		free(line);
		line = get_next_line(fd);
	}
	return (0);
}

int	fill_map(char **av, t_global *all)
{
	int	fd;

	fd = open(av[1], O_RDONLY);
	if (fd < 0)
		return (printf("can't open file\n"), 1);
	all->map = (t_map *)malloc(sizeof(t_map) * 1);
	if (all->map == NULL)
		return (printf("malloc error\n"), close(fd), 1);
	init_height(av, all);
	return (0);	
}

int	parse_map_walls(char **av, t_global *all)
{
	fill_map(av, all);
	return (0);
}
