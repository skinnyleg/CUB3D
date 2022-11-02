/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lower.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/11 12:23:33 by hmoubal           #+#    #+#             */
/*   Updated: 2022/10/31 17:56:55 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

int	parse_wall(t_global *all)
{
	if (vertical_wall(all->map) == 1)
		return (printf("error wall\n"), 1);
	if (horizantal_wall(all->map) == 1)
		return (printf("error wall\n"), 1);
	if (check_contents(all->map) == 1)
		return (printf("error contents\n"), 1);
	return (0);
}

int	fill(char **av, t_global *all)
{
	all->map = (t_map *)malloc(sizeof(t_map) * 1);
	if (all->map == NULL)
		return (printf("malloc error\n"), close(all->fd), 1);
	init_height(all->fd, all);
	all->map->map = (char **) malloc(sizeof(char *) * (all->map->height + 1));
	if (all->map->map == NULL)
		return (printf("malloc error\n"), free(all->map), all->map = NULL, 1);
	if (fill_map(all, av) == 1)
		return (free(all->map), all->map = NULL, 1);
	return (0);
}

int	parse_lower(char **av, t_global *all)
{
	if (all->l == 0)
		return (printf("map not found\n"), 1);
	if (fill(av, all) == 1)
		return (/*destroy_all(all),*/ 1);
	if (parse_wall(all) == 1)
		return (/*destroy_all(all),*/ 1);
	return (0);
}
