/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   destroy_global.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:28:11 by hmoubal           #+#    #+#             */
/*   Updated: 2022/10/31 17:56:03 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

void	destroy_map(t_global *all)
{
	free_map(all->map);
	all->map = NULL;
}

void	destroy_up(t_global *all)
{
	ft_free_lst_paraup(&(all->up));
	all->up = NULL;
}

void	destroy_mlx(t_global *all)
{
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
	if (all->mlx != NULL)
		destroy_mlx(all);
	if (all->player != NULL)
		destroy_player(all);
	if (all->map != NULL)
		destroy_map(all);
	if (all->up != NULL)
		destroy_up(all);
}
