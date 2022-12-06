/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 22:32:11 by hmoubal           #+#    #+#             */
/*   Updated: 2022/12/06 01:17:33 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

void	ft_backround(t_global *all, int color)
{
	int	x;
	int	y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (sqrt((170 - y) * (170 - y) + (170 - x) * (170 - x)) <= 150)
				pixel_put(all->mlx, x, y, color);
			x++;
		}
		y++;
	}
}

void	ft_block(t_global *all, int color, int j, int i)
{
	int	x;
	int	y;

	y = (i * TILE_SIZE + 170);
	while ((y < (i * TILE_SIZE + TILE_SIZE + 170)))
	{
		x = (j * TILE_SIZE + 170);
		while (x < (j * TILE_SIZE + TILE_SIZE + 170))
		{
			if (sqrt((170 - y) * (170 - y) + (170 - x) * (170 - x)) <= 150)
				pixel_put(all->mlx, x, y, color);
			x++;
		}
		y++;
	}
}

int	ft_direction(char c)
{
	if (c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

void	ft_putcircle(t_global *all, int x, int y, int r)
{
	double	i;
	double	angle;
	double	x1;
	double	y1;

	i = 0;
	while (i < 360)
	{
		angle = i;
		x1 = r * cos(angle * M_PI / 180);
		y1 = r * sin(angle * M_PI / 180);
		pixel_put(all->mlx, x + x1, y + y1, 16777215);
		i += 0.1;
	}
}

void	render_minimap(t_global *all)
{
	int	i;
	int	j;
	int	x;
	int	y;

	ft_backround(all, 16777215);
	i = floor(all->player->pos_tiley / all->player->tile_height);
	j = floor(all->player->pos_tilex / all->player->tile_width);
	y = i;
	x = j;
	i -= 5;
	while (i < 0)
		i++;
	while (all->map->map[i])
	{
		j = 0;
		while (all->map->map[i][j])
		{
			if (all->map->map[i][j] == '1')
				ft_block(all, 16711680, j - x, i - y);
			else if (all->map->map[i][j] == '0')
				ft_block(all, 255, j - x, i - y);
			else if (all->map->map[i][j] != ' ')
				ft_block(all, 255, j - x, i - y);
			j++;
		}
		i++;
	}
	// ft_block(all, 65280, 0, 0);
	pixel_put(all->mlx, 170 + (TILE_SIZE / 2), 170 + (TILE_SIZE / 2), 0);
	render_direct(all, 60, 170 + (TILE_SIZE / 2), 170 + (TILE_SIZE / 2));
	ft_putcircle(all, 170, 170, 150);
}
