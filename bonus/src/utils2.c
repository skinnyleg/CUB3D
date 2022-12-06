/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 23:10:51 by hmoubal           #+#    #+#             */
/*   Updated: 2022/12/06 01:17:27 by hmoubal          ###   ########.fr       */
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
