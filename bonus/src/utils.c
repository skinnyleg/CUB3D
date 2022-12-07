/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:03:14 by hmoubal           #+#    #+#             */
/*   Updated: 2022/12/07 20:08:18 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

int	map_size(char **map)
{
	int	i;

	i = 0;
	while (map[i] != NULL)
		i++;
	return (i);
}

void	free_maparr(t_global *all)
{
	int	i;

	i = 0;
	while (all->map->map[i] != NULL)
	{
		free(all->map->map[i]);
		i++;
	}
	free(all->map->map);
}

int	iswall_ray(t_global *all, double x, double y)
{
	int	gridx;
	int	gridy;

	if (x < 0 || x > all->map->width * all->player->tile_width \
		|| y < 0 || y > all->map->height * all->player->tile_height)
		return (1);
	gridx = floor((x / all->player->tile_width));
	gridy = floor((y / all->player->tile_height));
	if (gridy <= all->map->height && all->map->map[gridy] != NULL \
		&& all->map->map[gridy][gridx] == '1')
		return (1);
	return (0);
}

void	ft_direction_player(t_global *all, char p)
{
	if (p == 'N')
		all->player->rotateangle = (3 * M_PI) / 2;
	else if (p == 'S')
		all->player->rotateangle = (M_PI) / 2;
	else if (p == 'E')
		all->player->rotateangle = 0;
	else if (p == 'W')
		all->player->rotateangle = (M_PI);
}

int	iswall(t_global *all, double x, double y)
{
	int	gridx;
	int	gridy;

	if (x < 0 || x > all->map->width * all->player->tile_width \
		|| y < 0 || y > all->map->height * all->player->tile_height)
		return (1);
	gridx = floor((all->player->pos_tilex / (double)all->player->tile_width));
	gridy = floor((y / (double)all->player->tile_height));
	if (gridy <= all->map->height && all->map->map[gridy] != NULL \
		&& all->map->map[gridy][gridx] == '1')
		return (1);
	gridx = floor((x / (double)all->player->tile_width));
	gridy = floor((all->player->pos_tiley / (double)all->player->tile_height));
	if (gridy <= all->map->height && all->map->map[gridy] != NULL \
		&& all->map->map[gridy][gridx] == '1')
		return (1);
	return (0);
}
