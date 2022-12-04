/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall3D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:00:46 by hmoubal           #+#    #+#             */
/*   Updated: 2022/12/03 21:40:25 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

void	calc_offset(t_global *all, int i, double *y, double *end)
{
	double		tmpy;
	t_textures	*tex;

	tex = all->textures;
	tmpy = ((double)WIN_HEIGHT / 2) - (all->wallheight / 2);
	*end = tmpy + all->wallheight;
	if (tmpy < 0)
		*y = 0;
	else
		*y = tmpy;
	if (*end > WIN_HEIGHT)
		*end = WIN_HEIGHT;
	if (all->rays[i].verthit == true)
		tex->offsetx = (int)all->rays[i].ynext % all->player->tile_height;
	else
		tex->offsetx = (int)all->rays[i].xnext % all->player->tile_height;
}

void	render_wall(t_global *all, int i, int index)
{
	double		x;
	double		y;
	double		tmpx;
	double		tmpy;
	double		end;

	x = i * STRIP_WIDTH;
	tmpx = i * STRIP_WIDTH;
	tmpy = ((double)WIN_HEIGHT / 2) - (all->wallheight / 2);
	calc_offset(all, i, &y, &end);
	while (x < tmpx + STRIP_WIDTH)
	{
		while (y < end)
		{
			all->textures->offsety = (y - tmpy) * \
				(all->player->tile_height / all->wallheight);
			all->textures->texelcolor = all->textures->texture[index][(\
				all->player->tile_width * all->textures->offsety) \
				+ all->textures->offsetx];
			pixel_put(all->mlx, x, y, all->textures->texelcolor);
			y++;
		}
		x++;
	}
}

void	render3dwalls(t_global *all)
{
	double	dist_proj;
	double	correctwall;
	int		i;
	int		index;

	i = 0;
	index = -1;
	dist_proj = (WIN_WIDTH / 2) / (tan(FOV * (M_PI / 180) / 2));
	while (i < all->num_rays)
	{
		index = index_textures(all, i);
		correctwall = all->rays[i].dist_const \
			* cos(all->rays[i].rad - all->player->rotateangle);
		all->wallheight = dist_proj \
			* ((double)all->player->tile_height / correctwall);
		render_wall(all, i, index);
		i++;
	}
}
