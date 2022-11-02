/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:52:57 by med-doba          #+#    #+#             */
/*   Updated: 2022/11/02 12:12:14 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

void	ft_move_left(t_global *all, int i, int j)
{
	if (all->map->map[i][j - 1] == '0')
	{
		all->map->map[i][j] = '0';
		all->map->map[i][j - 1] = 'N';
	}
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
			if (all->map->map[i][j] == 'N')
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
	if (all->map->map[i][j + 1] == '0')
	{
		all->map->map[i][j] = '0';
		all->map->map[i][j + 1] = 'N';
	}
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
			if (all->map->map[i][j] == 'N')
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
	if (all->map->map[i - 1][j] == '0')
	{
		all->map->map[i][j] = '0';
		all->map->map[i - 1][j] = 'N';
	}
	ft_replace(all);
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
			if (all->map->map[i][j] == 'N')
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
	if (all->map->map[i + 1][j] == '0')
	{
		all->map->map[i][j] = '0';
		all->map->map[i + 1][j] = 'N';
	}
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
			if (all->map->map[i][j] == 'N')
			{
				ft_move_down(all, i, j);
				return ;
			}
			j++;
		}
		i++;
	}
}
