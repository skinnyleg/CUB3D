/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beta_utils_00.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 11:24:49 by med-doba          #+#    #+#             */
/*   Updated: 2022/11/13 19:55:08 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

int	ft_derection(char c)
{
	if(c == 'N' || c == 'S' || c == 'W' || c == 'E')
		return (1);
	return (0);
}

int	ft_find_position(t_global *all,double *x,double *y)
{
	*y = -1;
	while (all->map->map[(int)++(*y)])
	{
		*x = -1;
		while (all->map->map[(int)*y][(int)++(*x)])
			if(ft_derection(all->map->map[(int)*y][(int)*x]))
				return (0);
	}
	return (1);
}

void ft_PutCircle(t_global *all, int x, int y, int r)
{
	static const double PI = 3.1415926535;
	double i, angle, x1, y1;

	i = 0;
	while(i < 360)
	{
		angle = i;
		x1 = r * cos(angle * PI / 180);
		y1 = r * sin(angle * PI / 180);
		// x1 = 0;
		// y1 = 0;
		// r = 0;
		img_pix_put(all, x + x1, y + y1, 16777215);
		i += 0.1;
	}
}

void ft_center_player(t_global *all, int color)
{
	int	x;
	int y;

	y = 170 ;
	while ((y < (170 + 30)))
	{
		x = 170;
		while (x < (170 + 30))
		{
			if (sqrt((170 - y) * (170 - y) + (170 - x) * (170 - x)) <= 150)
				img_pix_put(all, x, y, color);
			x++;
		}
		y++;
	}
}

void	ft_backround(t_global *all, int color)
{
	int	x;
	int y;

	y = 0;
	while (y < WIN_HEIGHT)
	{
		x = 0;
		while (x < WIN_WIDTH)
		{
			if (sqrt((170 - y) * (170 - y) + (170 - x) * (170 - x)) <= 150)
				img_pix_put(all, x, y, color);
			x++;
		}
		y++;
	}
}
