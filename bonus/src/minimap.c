/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 22:32:11 by hmoubal           #+#    #+#             */
/*   Updated: 2022/12/06 00:03:47 by hmoubal          ###   ########.fr       */
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

	y = (i * 30 + 170);
	while ((y < (i * 30 + 30 + 170)))
	{
		x = (j * 30 + 170);
		while (x < (j * 30 + 30 + 170))
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

	// find_pos_p(all);
	ft_backround(all, 16777215);
	y = all->a;
	x = all->l;
	i = all->a;
	j = all->l;
	i -= 10;
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
			else if (ft_direction(all->map->map[i][j]))
			{
				pixel_put(all->mlx, all->player->pos_tilex, all->player->pos_tiley, 16776960);
				render_direct(all, 60, all->player->pos_tilex, all->player->pos_tiley);
				// ft_block(all, 16776960, j-x, i-y);
			}
			j++;
		}
		i++;
	}
	ft_putcircle(all, 170, 170, 150);
}
