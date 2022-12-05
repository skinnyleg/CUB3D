/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_global.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:28:11 by hmoubal           #+#    #+#             */
/*   Updated: 2022/12/03 20:39:59 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

void	destroy_map(t_global *all)
{
	if (all->map->map != NULL)
		free_maparr(all);
	free(all->map);
	all->map = NULL;
}

void	destroy_up(t_global *all)
{
	ft_free_lst_paraup(&(all->up));
	all->up = NULL;
}

void	destroy_mlx(t_global *all)
{
	if (all->mlx->image != NULL)
		mlx_destroy_image(all->mlx->mlx_ptr, all->mlx->image);
	if (all->mlx->mlx_win != NULL)
		mlx_clear_window(all->mlx->mlx_ptr, all->mlx->mlx_win);
	free(all->mlx);
	all->mlx = NULL;
}

void	destroy_player(t_global *all)
{
	free(all->player);
	all->player = NULL;
}

void	destroy_all(t_global *all)
{
	if (all->textures != NULL)
		destroy_textures(all);
	if (all->mlx != NULL)
		destroy_mlx(all);
	if (all->player != NULL)
		destroy_player(all);
	if (all->map != NULL)
		destroy_map(all);
	if (all->up != NULL)
		destroy_up(all);
	if (all->rays != NULL)
		destroy_rays(all);
}
