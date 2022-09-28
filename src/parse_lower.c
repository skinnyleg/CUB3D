#include "../includes/CUB3D.h"

int	parse_wall(t_global *all)
{
	if (vertical_wall(all->map) == 1)
		return (printf("error wall\n"), free_map(all->map), 1);
	if (horizantal_wall(all->map) == 1)
		return (printf("error wall\n"), free_map(all->map), 1);
	if (check_contents(all->map) == 1)
		return (printf("error contents\n"), free_map(all->map), 1);
	printf("outside haha\n");
	return (0);
}

int	fill(char **av, t_global *all)
{
	all->map = (t_map *)malloc(sizeof(t_map) * 1);
	if (all->map == NULL)
		return (printf("malloc error\n"), close(all->fd), 1);
	init_height(all->fd, all);
	if (all->map->height == 1)
		return (printf("map not found\n"), free(all->map), 1);
	all->map->map = (char **) malloc(sizeof(char *) * (all->map->height + 1));
	if (all->map->map == NULL)
		return (printf("malloc error\n"), free(all->map), 1);
	if (fill_map(all, av) == 1)
		return (free(all->map), 1);
	return (0);
}

int	parse_lower(char **av, t_global *all)
{
	if (fill(av, all) == 1)
		return (1);
	if (parse_wall(all) == 1)
		return (1);
	return (0);
}
