/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:52:57 by med-doba          #+#    #+#             */
/*   Updated: 2022/11/01 16:06:12 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

void	ft_move_left(t_global *all, int i, int j)
{
	if (all->map->map[i][j - 1] == '0')
	{
		all->map->map[i][j] = '0';
		all->map->map[i][j - 1] = 'P';
	}
	else if (all->map->map[i][j - 1] == 'C')
	{
		all->map->map[i][j] = '0';
		all->map->map[i][j - 1] = 'P';
	}
	else if (all->map->map[i][j - 1] == 'E')
	{
		// if (ft_check(all, 'C') == 0)
		// {
		// 	ft_printf("You Win\n");
		// 	// ft_close(all);
		// }
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
			if (all->map->map[i][j] == 'P')
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
		all->map->map[i][j + 1] = 'P';
	}
	else if (all->map->map[i][j + 1] == 'C')
	{
		all->map->map[i][j] = '0';
		all->map->map[i][j + 1] = 'P';
	}
	else if (all->map->map[i][j + 1] == 'E')
	{
		// if (ft_check(all, 'C') == 0)
		// {
		// 	ft_printf("You Win\n");
		// 	// ft_close(all);
		// }
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
			if (all->map->map[i][j] == 'P')
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
		all->map->map[i - 1][j] = 'P';
	}
	else if (all->map->map[i - 1][j] == 'C')
	{
		all->map->map[i][j] = '0';
		all->map->map[i - 1][j] = 'P';
	}
	else if (all->map->map[i - 1][j] == 'E')
	{
		// if (ft_check(all, 'C') == 0)
		// {
		// 	ft_printf("You Win\n");
		// 	// ft_close(all);
		// }
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
			if (all->map->map[i][j] == 'P')
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
		all->map->map[i + 1][j] = 'P';
	}
	else if (all->map->map[i + 1][j] == 'C')
	{
		all->map->map[i][j] = '0';
		all->map->map[i + 1][j] = 'P';
	}
	else if (all->map->map[i + 1][j] == 'E')
	{
		// if (ft_check(all, 'C') == 0)
		// {
		// 	printf("You Win\n");
		// 	// ft_close(all);
		// }
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
			if (all->map->map[i][j] == 'P')
			{
				ft_move_down(all, i, j);
				return ;
			}
			j++;
		}
		i++;
	}
}
