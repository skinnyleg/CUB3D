/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:52:57 by med-doba          #+#    #+#             */
/*   Updated: 2022/11/06 11:19:34 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"



void	ft_move_left(t_global *all, int i, int j)
{
	i = 0;
	j = 0;
	// if (all->map->map[i][j - 1] == '0')
	// {
	// 	// all->map->map[i][j] = '0';
	// 	// all->map->map[i][j - 1] = 'N';
	// }
	// ft_render_(all);
	int tmp = all->pos_x;
	double	movesteps_x;
	all->mini->turndirection -= 1;
	movesteps_x = all->mini->walkdirection * all->mini->movespeed;
	all->pos_x -= movesteps_x;
	// ft_render_(all);
	// ft_render_move(all);
	ft_replace(all, 'x');
	all->pos_x = tmp;
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
				ft_move_left(all, i, j);
				return ;
			}
			j++;
		}
		i++;
	}
}

void	ft_move_rigth(t_global *all, int i, int j)
{
	// if (all->map->map[i][j + 1] == '0')
	// {
	// 	// all->map->map[i][j] = '0';
	// 	// all->map->map[i][j + 1] = 'N';
	// }
	// ft_render_(all);
	i = 0;
	j = 0;
	all->mini->turndirection += 1;
	int tmp = all->pos_x;
	double	movesteps_x;
	movesteps_x = all->mini->walkdirection * all->mini->movespeed;
	all->pos_x += movesteps_x;
	printf("r = %d\n", all->mini->turndirection);
	// ft_render_(all);
	// ft_render_move(all);
	ft_replace(all, 'x');
	all->pos_x = tmp;
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
				ft_move_rigth(all, i, j);
				return ;
			}
			j++;
		}
		i++;
	}
}
void	ft_move_up(t_global *all, int i, int j)
{
	// if (all->map->map[i - 1][j] == '0')
	// {
	// 	// all->map->map[i][j] = '0';
	// 	// all->map->map[i - 1][j] = 'N';
	// }
	// ft_render_(all);
	i = 0;
	j = 0;
	int tmp = all->pos_y;
	double movesteps_y;
	all->mini->walkdirection += 1;
	movesteps_y = all->mini->walkdirection * all->mini->movespeed;
	all->pos_y += movesteps_y;
	printf("up = %d\n", all->pos_y);
	// ft_render_move(all);
	// ft_render_(all);
	ft_replace(all, 'y');
	all->pos_y = tmp;
	return ;
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
				ft_move_up(all, i, j);
				return ;
			}
			j++;
		}
		i++;
	}
}

void	ft_move_down(t_global *all, int i, int j)
{
	// if (all->map->map[i + 1][j] == '0')
	// {
	// 	// all->map->map[i][j] = '0';
	// 	// all->map->map[i + 1][j] = 'N';
	// }
	// ft_render_(all);
	i = 0;
	j = 0;
	int tmp = all->pos_y;
	double movesteps_y;
	all->mini->walkdirection -= 1;
	movesteps_y = all->mini->walkdirection * all->mini->movespeed;
	all->pos_y -= movesteps_y;
	printf("down = %d\n", all->pos_y);
	// ft_render_(all);
	// ft_render_move(all);
	ft_replace(all, 'y');
	all->pos_y = tmp;
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
				ft_move_down(all, i, j);
				return ;
			}
			j++;
		}
		i++;
	}
}
