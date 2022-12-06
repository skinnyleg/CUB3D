/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 23:10:51 by hmoubal           #+#    #+#             */
/*   Updated: 2022/12/06 01:41:57 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

void	render_direct(t_global *all, int size, double x, double y)
{
	double	dx;
	double	dy;
	double	x_inc;
	double	y_inc;
	int		step;

	dx = cos(all->player->rotateangle) * size;
	dy = sin(all->player->rotateangle) * size;
	if (abs((int)dx) > abs((int)dy))
		step = abs((int)dx);
	else
		step = abs((int)dy);
	x_inc = (dx / (double)step);
	y_inc = (dy / (double)step);
	dx = x;
	dy = y;
	while (step != 0)
	{
		pixel_put(all->mlx, round(dx), round(dy), 16711680);
		dx += x_inc;
		dy += y_inc;
		step--;
	}
}

void	ft_background(t_global *all, int color)
{
	int	x;
	int	y;
	int	tmpy;
	int	tmpx;

	y = 640 - 150;
	tmpy = y;
	while (y < tmpy + (150 * 2))
	{
		x = 1340 - 150;
		tmpx = x;
		while (x < tmpx + (150 * 2))
		{
			if (sqrt((640 - y) * (640 - y) + (1340 - x) * (1340 - x)) <= 150)
				pixel_put(all->mlx, x, y, color);
			x++;
		}
		y++;
	}
}

void	ft_block(t_mlx *mlx, int color, int j, int i)
{
	int	x;
	int	y;

	y = (i * TILE_SIZE + 640);
	while ((y < (i * TILE_SIZE + TILE_SIZE + 640)))
	{
		x = (j * TILE_SIZE + 1340);
		while (x < (j * TILE_SIZE + TILE_SIZE + 1340))
		{
			if (sqrt((640 - y) * (640 - y) + (1340 - x) * (1340 - x)) <= 150)
				pixel_put(mlx, x, y, color);
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
