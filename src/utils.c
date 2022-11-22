/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:03:14 by hmoubal           #+#    #+#             */
/*   Updated: 2022/11/21 22:01:24 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

void	aspect_ratio(t_global *all)
{
	double	resizewidth;
	double	resizeheight;
	double	aspect;

	resizewidth = all->map->width;
	resizeheight = all->map->height;
	aspect = resizewidth / resizeheight;
	if (resizewidth > MINI_WIDTH)
	{
		resizewidth = MINI_WIDTH;
		resizeheight = resizewidth / aspect;
	}
	if (resizeheight > MINI_HEIGHT)
	{
		aspect = resizewidth / resizeheight;
		resizeheight = MINI_HEIGHT;
		resizewidth = resizeheight * aspect;
	}
	all->player->tile_width = (resizewidth / all->player->x) + 4;
	all->player->tile_height = (resizeheight / all->player->y) + 4;
}

void	render_block(t_global *all, int i, int j, int color)
{
	int			x;
	int			y;
	t_player	*p;

	aspect_ratio(all);
	p = all->player;
	p->tile_height = WIN_HEIGHT / all->map->height;
	p->tile_width = WIN_WIDTH / all->map->width;
	p->tile_height = 32;
	p->tile_width = 32;
	x = i * p->tile_width;
	while (x < ((i * p->tile_width) + p->tile_width))
	{
		y = j * p->tile_height;
		while (y < ((j * p->tile_height) + p->tile_height))
		{
			pixel_put(all->mlx, x, y, color);
			y++;
		}
		x++;
	}
}

void	render_rays(t_global *all, t_rays ray, double x, double y)
{
	int		dx;
	int		dy;
	double	ddx;
	double	ddy;
	double	x_inc;
	double	y_inc;
	int		step;

	dx = (ray.xnext - x);
	dy = (ray.ynext - y);
	if (abs(dx) > abs(dy))
		step = abs(dx);
	else
		step = abs(dy);
	x_inc = ((double)dx / (double)step);
	y_inc = ((double)dy / (double)step);
	dx = round(x);
	dy = round(y);
	ddx = x;
	ddy = y;
	while (step != 0)
	{
		pixel_put(all->mlx, dx, dy, 16711680);
		ddx += x_inc;
		ddy += y_inc;
		dx = round(ddx);
		dy = round(ddy);
		step--;
	}
}
