/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:52:57 by med-doba          #+#    #+#             */
/*   Updated: 2022/11/13 20:03:26 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

void	ft_move_left(t_global *all)
{
	all->mini->turndirection = 1;
	all->mini->movesteps = all->mini->turndirection * all->mini->movespeed;
	// printf("left angle  x = %f\n", all->mini->rotateangle);
	all->pos_x -=  cos(all->mini->rotateangle) * all->mini->movesteps;
	// printf("left x = %f\n", all->pos_x);
	all->pos_y +=  sin(all->mini->rotateangle) * all->mini->movesteps;
	// printf("left y = %f\n", all->pos_y);
	// all->pos_x += all->mini->movesteps_x;
	ft_replace(all);
	return ;
}

void	ft_left(t_global *all)
{
	int	i;
	int	j;

	i = 0;
	while (all->map->map[i] != NULL)
	{
		j = 0;
		while (all->map->map[i][j] != '\0')
		{
			if (ft_derection(all->map->map[i][j]))
			{
				ft_move_left(all);
				return ;
			}
			j++;
		}
		i++;
	}
}

void	ft_move_rigth(t_global *all)
{
	all->mini->turndirection = 1;
	all->mini->movesteps = all->mini->turndirection * all->mini->movespeed;
	// printf("rigth angle  x = %f\n", all->mini->rotateangle);
	all->pos_x +=  cos(all->mini->rotateangle) * all->mini->movesteps;
	// printf("rigth x = %f\n", all->pos_x);
	all->pos_y -=  sin(all->mini->rotateangle) * all->mini->movesteps;
	// printf("rigth y = %f\n", all->pos_y);
	// all->pos_x += all->mini->movesteps_x;
	ft_replace(all);
	return ;
}

void	ft_rigth(t_global *all)
{
	int	i;
	int	j;

	i = 0;
	while (all->map->map[i] != NULL)
	{
		j = 0;
		while (all->map->map[i][j] != '\0')
		{
			if (ft_derection(all->map->map[i][j]))
			{
				ft_move_rigth(all);
				return ;
			}
			j++;
		}
		i++;
	}
}
void	ft_move_up(t_global *all)
{
	all->mini->walkdirection = 1;
	all->mini->movesteps = all->mini->walkdirection * all->mini->movespeed;
	all->pos_y +=  sin(all->mini->rotateangle) * all->mini->movesteps;
	// printf("sin = %f\n", sin(all->mini->rotateangle) * all->mini->movesteps);
	all->pos_x +=  cos(all->mini->rotateangle) * all->mini->movesteps;
	// printf("cos = %f\n", cos(all->mini->rotateangle) * all->mini->movesteps);
	// all->pos_y += all->mini->movesteps_y;
	ft_replace(all);
}

void	ft_up(t_global *all)
{
	int	i;
	int	j;

	i = 0;
	while (all->map->map[i] != NULL)
	{
		j = 0;
		while (all->map->map[i][j] != '\0')
		{
			if (ft_derection(all->map->map[i][j]))
			{
				ft_move_up(all);
				return ;
			}
			j++;
		}
		i++;
	}
}

void	ft_move_down(t_global *all)
{
	all->mini->walkdirection = -1;
	all->mini->movesteps = all->mini->walkdirection * all->mini->movespeed;
	all->pos_y +=  sin(all->mini->rotateangle) * all->mini->movesteps;
	// printf("y-> = %f\n", all->pos_y);
	all->pos_x +=  cos(all->mini->rotateangle) * all->mini->movesteps;
	// printf("x-> = %f\n", all->pos_x);
	// all->pos_y += all->mini->movesteps_y;
	ft_replace(all);
	return ;
}

void	ft_down(t_global *all)
{
	int	i;
	int	j;

	i = 0;
	while (all->map->map[i] != NULL)
	{
		j = 0;
		while (all->map->map[i][j] != '\0')
		{
			if (ft_derection(all->map->map[i][j]))
			{
				ft_move_down(all);
				return ;
			}
			j++;
		}
		i++;
	}
}

