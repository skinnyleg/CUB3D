/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/24 16:29:14 by hmoubal           #+#    #+#             */
/*   Updated: 2022/11/24 22:02:57 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

int	set_textures(t_global *all)
{
	t_player	*p;
	int			sl;
	int			bpp;
	int			end;

	p = all->player;
	all->scale = 1;
	p->tile_height = TILE_SIZE;
	p->tile_width = TILE_SIZE;
	all->textures = (t_textures *)malloc(sizeof(t_textures) * 1);
	if (all->textures == NULL)
		return (destroy_all(all), -1);
	all->textures->teximg = mlx_xpm_file_to_image(all->mlx->mlx_ptr, "./textures/wall.xpm", &sl, &bpp);
	if (all->textures->teximg == NULL)
		return (destroy_all(all), -1);
	all->textures->texture = (int *)mlx_get_data_addr(all->textures->teximg, &sl , &bpp , &end);
	if (all->textures->texture == NULL)
		return (destroy_all(all), -1);
	return (0);
}