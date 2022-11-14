/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall3D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:00:46 by hmoubal           #+#    #+#             */
/*   Updated: 2022/11/12 17:00:25 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

void	render_wall(t_global *all, int i, double wallheight)
{
	double	x;
	double	y;
	double	tmpx;
	double	tmpy;

	x = i * STRIP_WIDTH;
	tmpx = i * STRIP_WIDTH;
	tmpy = ((double)WIN_HEIGHT / 2) - (wallheight / 2);
	while (x < tmpx + STRIP_WIDTH)
	{
		y = tmpy;
		while (y < tmpy + wallheight)
		{
			pixel_put(all->mlx, x, y, 16777215);
			y++;
		}
		x++;
	}
}

void	render3dwalls(t_global *all)
{
	double	dist_proj;
	double	wall_height;
	int		i;

	i = 0;
	dist_proj = (WIN_WIDTH / 2) / (tan(FOV * (M_PI / 180) / 2));
	while (i < all->num_rays)
	{
		wall_height = dist_proj \
			* ((double)all->player->tile_height / all->rays[i].dist_const);
		render_wall(all, i, wall_height);
		i++;
	}
}
