/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:03:14 by hmoubal           #+#    #+#             */
/*   Updated: 2022/11/28 18:41:08 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

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
	int			height;
	int			width;
	t_player	*p;

	p = all->player;
	height = p->tile_height * all->scale;
	width = p->tile_width * all->scale;
	x = i * width;
	while (x < ((i * width) + width))
	{
		y = j * height;
		while (y < ((j * height) + height))
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

	dx = (ray.xnext - x) * all->scale;
	dy = (ray.ynext - y) * all->scale;
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