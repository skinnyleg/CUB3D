/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_calculate.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:27:08 by hmoubal           #+#    #+#             */
/*   Updated: 2022/12/03 20:36:01 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

double	looptilhit_horz(t_rays *ray, t_global *all)
{
	while (ray->xnext >= 0 \
		&& ray->xnext <= all->map->width * all->player->tile_width \
		&& ray->ynext >= 0 \
		&& ray->ynext <= all->map->height * all->player->tile_height)
	{
		if (iswall_ray(all, ray->xnext, ray->ynext) == 1)
		{
			if (ray->up == true)
				ray->ynext++;
			ray->horzx = ray->xnext;
			ray->horzy = ray->ynext;
			return (distance_calcul(all, *ray));
		}
		ray->xnext += ray->xstep;
		ray->ynext += ray->ystep;
	}
	return (INT_MAX);
}

double	looptilhit_vert(t_rays *ray, t_global *all)
{
	while (ray->xnext >= 0 \
			&& ray->xnext <= all->map->width * all->player->tile_width \
			&& ray->ynext >= 0 \
			&& ray->ynext <= all->map->height * all->player->tile_height)
	{
		if (iswall_ray(all, ray->xnext, ray->ynext) == 1)
		{
			if (ray->right == false)
				ray->xnext++;
			ray->vertx = ray->xnext;
			ray->verty = ray->ynext;
			return (distance_calcul(all, *ray));
		}
		ray->xnext += ray->xstep;
		ray->ynext += ray->ystep;
	}
	return (INT_MAX);
}

void	horiz_intersect(t_global *all, t_rays *ray)
{
	ray->ynext = floor((all->player->pos_tiley \
		/ (double)all->player->tile_height)) \
		* (double)all->player->tile_height;
	if (!ray->up)
		ray->ynext += (double)all->player->tile_height;
	ray->xnext = all->player->pos_tilex - \
		((all->player->pos_tiley - ray->ynext) / tan(ray->rad));
	ray->ystep = (double)all->player->tile_height;
	if (ray->up == true)
		ray->ystep *= -1;
	ray->xstep = (double)all->player->tile_height / tan(ray->rad);
	if ((ray->right == true && ray->xstep < 0) \
		|| (ray->right == false && ray->xstep > 0))
		ray->xstep *= -1;
	if (ray->up == true)
		ray->ynext--;
	ray->distance_horiz = looptilhit_horz(ray, all);
}

void	vertic_intersect(t_global *all, t_rays *ray)
{
	ray->xnext = floor((all->player->pos_tilex \
		/ (double)all->player->tile_width)) \
		* (double)all->player->tile_width;
	if (ray->right == true)
		ray->xnext += (double)all->player->tile_width;
	ray->ynext = all->player->pos_tiley - \
		(tan(ray->rad) * (all->player->pos_tilex - ray->xnext));
	ray->xstep = (double)all->player->tile_width;
	if (ray->right == false)
		ray->xstep *= -1;
	ray->ystep = (double)all->player->tile_width * tan(ray->rad);
	if ((ray->up == true && ray->ystep > 0) \
		|| (ray->up == false && ray->ystep < 0))
		ray->ystep *= -1;
	if (ray->right == false)
		ray->xnext--;
	ray->distance_vertic = looptilhit_vert(ray, all);
}

void	cast_render(t_global *all, t_rays *ray)
{
	horiz_intersect(all, ray);
	vertic_intersect(all, ray);
	if (ray->distance_horiz < ray->distance_vertic)
	{
		ray->ynext = ray->horzy;
		ray->xnext = ray->horzx;
		ray->verthit = false;
		ray->dist_const = ray->distance_horiz;
	}
	else if (ray->distance_horiz >= ray->distance_vertic)
	{
		ray->xnext = ray->vertx;
		ray->ynext = ray->verty;
		ray->verthit = true;
		ray->dist_const = ray->distance_vertic;
	}
}
