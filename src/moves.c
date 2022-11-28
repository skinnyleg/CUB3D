/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:52:57 by med-doba          #+#    #+#             */
/*   Updated: 2022/11/28 15:10:39 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

int	ft_checkwall(t_global *all, double x, double y)
{
	int	tmp_x = floor(x / TILE_SIZE);
	int	tmp_y = floor(y / TILE_SIZE);
	if (tmp_y < all->map->height && all->map->map[tmp_y][tmp_x] == '1')
		return (0);
	return (1);
}

void	ft_move_left(t_global *all)
{
	double	tmp_x;
	double	tmp_y;

	all->mini->movesteps = all->mini->turndirection * all->mini->movespeed;
	tmp_x = all->pos_x - sin(all->mini->rotateangle) * all->mini->movesteps;
	tmp_y = all->pos_y + cos(all->mini->rotateangle) * all->mini->movesteps;
	if (ft_checkwall(all, tmp_x, tmp_y))
	{
		all->pos_x = tmp_x;
		all->pos_y = tmp_y;
	}
}


void	ft_move_up(t_global *all)
{
	double	tmp_x;
	double	tmp_y;

	all->mini->movesteps = all->mini->walkdirection * all->mini->movespeed;
	tmp_x = all->pos_x + cos(all->mini->rotateangle) * all->mini->movesteps;
	tmp_y = all->pos_y + sin(all->mini->rotateangle) * all->mini->movesteps;
	if (ft_checkwall(all, tmp_x, tmp_y))
	{
		all->pos_x = tmp_x;
		all->pos_y = tmp_y;
	}
}

// double	ft_normilaze(double angle)
// {
// 	angle = angle % (2 * M_PI);
// 	if (angle < 0)
// 		angle += (2 * M_PI);
// 	return (angle);
// }

