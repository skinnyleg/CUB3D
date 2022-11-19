/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:52:57 by med-doba          #+#    #+#             */
/*   Updated: 2022/11/18 21:50:32 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

void	ft_move_left(t_global *all)
{
	// all->mini->turndirection = 1;
	all->mini->movesteps = all->mini->turndirection * all->mini->movespeed;
	all->pos_x -=  cos(all->mini->rotateangle) * all->mini->movesteps;
	all->pos_y +=  sin(all->mini->rotateangle) * all->mini->movesteps;
	// ft_replace(all);
}

void	ft_left(t_global *all)
{
	all->mini->movesteps = all->mini->turndirection * all->mini->movespeed;
	all->pos_x -=  cos(all->mini->rotateangle) * all->mini->movesteps;
	all->pos_y +=  sin(all->mini->rotateangle) * all->mini->movesteps;
}

void	ft_move_rigth(t_global *all)
{
	// all->mini->turndirection = 1;
	all->mini->movesteps = all->mini->turndirection * all->mini->movespeed;
	all->pos_x +=  cos(all->mini->rotateangle) * all->mini->movesteps;
	all->pos_y -=  sin(all->mini->rotateangle) * all->mini->movesteps;
	// ft_replace(all);
}

void	ft_rigth(t_global *all)
{
	int	i;
	int	j;

	i = -1;
	while (all->map->map[++i] != NULL)
	{
		j = -1;
		while (all->map->map[i][++j] != '\0')
			if (ft_derection(all->map->map[i][j]))
				return (ft_move_rigth(all));
	}
}

void	ft_move_up(t_global *all)
{
	// all->mini->walkdirection = 1;
	all->mini->movesteps = all->mini->walkdirection * all->mini->movespeed;
	all->pos_y +=  sin(all->mini->rotateangle) * all->mini->movesteps;
	all->pos_x +=  cos(all->mini->rotateangle) * all->mini->movesteps;
	// ft_replace(all);
}

void	ft_up(t_global *all)
{
	puts("ddd");
	int	i;
	int	j;

	i = -1;
	while (all->map->map[++i] != NULL)
	{
		j = -1;
		while (all->map->map[i][++j] != '\0')
			if (ft_derection(all->map->map[i][j]))
				return (ft_move_up(all));
	}
}

void	ft_move_down(t_global *all)
{
	// all->mini->walkdirection = -1;
	all->mini->movesteps = all->mini->walkdirection * all->mini->movespeed;
	all->pos_y +=  sin(all->mini->rotateangle) * all->mini->movesteps;
	all->pos_x +=  cos(all->mini->rotateangle) * all->mini->movesteps;
	// ft_replace(all);
}

void	ft_down(t_global *all)
{
	int	i;
	int	j;

	i = -1;
	while (all->map->map[++i] != NULL)
	{
		j = -1;
		while (all->map->map[i][++j] != '\0')
			if (ft_derection(all->map->map[i][j]))
				return (ft_move_down(all));
	}
}

