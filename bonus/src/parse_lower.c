/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lower.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:23:33 by hmoubal           #+#    #+#             */
/*   Updated: 2022/12/07 20:13:25 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

int	parse_wall(t_global *all)
{
	if (vertical_wall(all->map) == 1)
		return (ft_putendl_fd("Error", 2), 1);
	if (horizantal_wall(all->map) == 1)
		return (ft_putendl_fd("Error", 2), 1);
	if (check_contents(all->map) == 1)
		return (ft_putendl_fd("Error", 2), 1);
	return (0);
}

void	set_null(t_global *all)
{
	int	i;

	i = 0;
	while (i < all->map->height + 1)
	{
		all->map->map[i] = NULL;
		i++;
	}
}

int	fill(char **av, t_global *all)
{
	all->map = (t_map *)malloc(sizeof(t_map) * 1);
	if (all->map == NULL)
		return (ft_putendl_fd("Error", 2), close(all->fd), 1);
	init_height(all->fd, all);
	all->map->map = (char **) malloc(sizeof(char *) * (all->map->height + 1));
	if (all->map->map == NULL)
		return (ft_putendl_fd("Error", 2), 1);
	set_null(all);
	if (fill_map(all, av) == 1)
		return (ft_putendl_fd("Error", 2), 1);
	return (0);
}

int	parse_lower(char **av, t_global *all)
{
	if (all->l == 0)
		return (ft_putendl_fd("Error", 2), 1);
	if (fill(av, all) == 1)
		return (destroy_all(all), 1);
	if (parse_wall(all) == 1)
		return (destroy_all(all), 1);
	return (0);
}
