/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 22:32:11 by hmoubal           #+#    #+#             */
/*   Updated: 2022/12/06 01:45:57 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

void	render_loop(t_global *all)
{
	int	i;
	int	j;
	int	x;
	int	y;

	i = floor(all->player->pos_tiley / all->player->tile_height);
	j = floor(all->player->pos_tilex / all->player->tile_width);
	y = i;
	x = j;
	i -= 5;
	if (i < 0)
		i = 0;
	while (all->map->map[i])
	{
		j = -1;
		while (all->map->map[i][++j])
		{
			if (all->map->map[i][j] == '1')
				ft_block(all->mlx, 16711680, j - x, i - y);
			else if (all->map->map[i][j] == '0' || all->map->map[i][j] != ' ')
				ft_block(all->mlx, 255, j - x, i - y);
		}
		i++;
	}
}

void	render_minimap(t_global *all)
{
	ft_background(all, all->color_floor);
	ft_putcircle(all, 1340, 640, 150);
	render_loop(all);
	pixel_put(all->mlx, 1340 + (TILE_SIZE / 2), 640 + (TILE_SIZE / 2), 0);
	render_direct(all, 60, 1340 + (TILE_SIZE / 2), 640 + (TILE_SIZE / 2));
}
