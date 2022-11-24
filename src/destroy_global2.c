/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_global2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/02 22:38:49 by hmoubal           #+#    #+#             */
/*   Updated: 2022/11/24 18:50:56 by hmoubal          ###   ########.fr       */
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
	free(all->textures);
	all->textures = NULL;
}