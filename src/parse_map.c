#include "../includes/CUB3D.h"

void	init_height(int fd, t_global *all)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
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
	while (line != NULL && count != 6)
	{
		if (*line != '\0')
			count++;
		printf("line == %s\n", line);
		free(line);
		line = get_next_line(fd);
	}
}

int	fill_map2(t_global *all, char **av)
{
	all->fd = open(av[1], O_RDONLY);
	if (all->fd < 0)
		return (printf("can't open file\n"), 1);
	skip_line(all->fd);
	return (0);
}

int	fill_map(char **av, t_global *all)
{
	all->map = (t_map *)malloc(sizeof(t_map) * 1);
	if (all->map == NULL)
		return (printf("malloc error\n"), close(all->fd), 1);
	init_height(all->fd, all);
	printf("height == %d\n", all->map->height);
	all->map->map = (char **) malloc(sizeof(char *) * all->map->height);
	if (all->map->map == NULL)
		return (printf("malloc error\n"), 1);
	if (fill_map2(all, av) == 1)
		return (1);
	return (0);	
}

int	parse_map_walls(char **av, t_global *all)
{
	fill_map(av, all);
	return (0);
}
