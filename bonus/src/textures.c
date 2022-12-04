/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/28 14:39:16 by hmoubal           #+#    #+#             */
/*   Updated: 2022/12/02 22:07:40 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

int	index_textures(t_global *all, int i)
{
	if (all->rays[i].verthit == false && all->rays[i].up == true)
		return (0);
	else if (all->rays[i].verthit == false && all->rays[i].up == false)
		return (1);
	else if (all->rays[i].verthit == true && all->rays[i].right == false)
		return (2);
	else if (all->rays[i].verthit == true && all->rays[i].right == true)
		return (3);
	return (0);
}

int	set_dir_text(t_global *all, char *path, int index)
{
	t_textures	*t;
	int			sl;
	int			bpp;
	int			end;

	t = all->textures;
	if (index == -1)
		return (2);
	t->teximg = mlx_xpm_file_to_image(all->mlx->mlx_ptr, path, &sl, &bpp);
	if (t->teximg == NULL)
		return (-1);
	t->texture[index] = (int *)mlx_get_data_addr(t->teximg, &sl, &bpp, &end);
	if (t->texture == NULL)
		return (-1);
	return (0);
}

int	fill_textures(t_global *all)
{
	t_paraup	*up;
	int			index;

	up = all->up;
	all->textures->texture = (int **)malloc(sizeof(int *) * 4);
	if (all->textures->texture == NULL)
		return (-1);
	while (up != NULL)
	{
		index = -1;
		if (ft_strcmp("NO", up->dir) == 0)
			index = 0;
		if (ft_strcmp("SO", up->dir) == 0)
			index = 1;
		if (ft_strcmp("WE", up->dir) == 0)
			index = 2;
		if (ft_strcmp("EA", up->dir) == 0)
			index = 3;
		if (set_dir_text(all, up->value, index) == -1)
			return (-1);
		up = up->next;
	}
	return (0);
}

int	set_textures(t_global *all)
{
	t_player	*p;

	p = all->player;
	all->scale = 0.2;
	p->tile_height = TILE_SIZE;
	p->tile_width = TILE_SIZE;
	all->textures = (t_textures *)malloc(sizeof(t_textures) * 4);
	if (all->textures == NULL)
		return (destroy_all(all), -1);
	if (fill_textures(all) == -1)
		return (destroy_all(all), -1);
	return (0);
}
