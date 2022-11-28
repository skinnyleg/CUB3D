/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall3D.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:00:46 by hmoubal           #+#    #+#             */
/*   Updated: 2022/11/28 15:27:37 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

void	render_wall(t_global *all, int i, double wallheight, int index)
{
	double		x;
	double		y;
	double		tmpx;
	double		tmpy;
	double		end;
	t_textures	*tex;

	tex = all->textures;
	x = i * STRIP_WIDTH;
	tmpx = i * STRIP_WIDTH;
	tmpy = ((double)WIN_HEIGHT / 2) - (wallheight / 2);
	end = tmpy + wallheight;
	if (tmpy < 0)
		y = 0;
	else
		y = tmpy;
	if (end > WIN_HEIGHT)
		end = WIN_HEIGHT;
	if (all->rays[i].verthit == true)
		tex->offsetx = (int)all->rays[i].ynext % all->player->tile_height;
	else
		tex->offsetx = (int)all->rays[i].xnext % all->player->tile_height;
	while (x < tmpx + STRIP_WIDTH)
	{
		while (y < end)
		{
			tex->offsety = (y - tmpy) * (all->player->tile_height / wallheight);
			tex->texelcolor = tex->texture[index][(all->player->tile_width * tex->offsety) + tex->offsetx];
			pixel_put(all->mlx, x, y, tex->texelcolor);
			y++;
		}
		x++;
	}
}

void	render3dwalls(t_global *all)
{
	double	dist_proj;
	double	wall_height;
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
		wall_height = dist_proj \
			* ((double)all->player->tile_height / correctwall);
		render_wall(all, i, wall_height, index);
		i++;
	}
}
