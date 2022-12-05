/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_global2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 22:38:49 by hmoubal           #+#    #+#             */
/*   Updated: 2022/12/03 20:41:40 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

void	destroy_rays(t_global *all)
{
	free(all->rays);
	all->rays = NULL;
}

void	destroy_textures(t_global *all)
{
	int	i;

	i = 0;
	while (i < 4)
	{
		if (all->textures->teximg[i] != NULL)
			mlx_destroy_image(all->mlx->mlx_ptr, all->textures->teximg[i]);
		i++;
	}
	free(all->textures->texture);
	free(all->textures);
	all->textures = NULL;
}
