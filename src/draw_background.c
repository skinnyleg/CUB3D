/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:53:46 by hmoubal           #+#    #+#             */
/*   Updated: 2022/11/15 15:56:41 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

int	get_int(char *content)
{
	char	**ptr;
	int		i;
	int		color;
	int		shift;

	shift = 16;
	i = 0;
	color = 0;
	ptr = ft_split(content, ',');
	while (ptr[i] != NULL)
	{
		color += ft_atoi(ptr[i]) << shift;
		shift = shift - 8;
		i++;
	}
	ft_free_2d(ptr);
	return (color);
}

void	get_color(t_global *all)
{
	t_paraup	*up;

	up = all->up;
	while (up != NULL)
	{
		if (ft_strcmp(up->dir, "C") == 0)
			all->color_ceiling = get_int(up->value);
		else if (ft_strcmp(up->dir, "F") == 0)
			all->color_floor = get_int(up->value);
		up = up->next;
	}
}

void	render_ceiling(t_global *all)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_WIDTH)
	{
		j = 0;
		while (j < WIN_HEIGHT / 2)
		{
			pixel_put(all->mlx, i, j, all->color_ceiling);
			j++;
		}
		i++;
	}
}

void	render_floor(t_global *all)
{
	int	i;
	int	j;

	i = 0;
	while (i < WIN_WIDTH)
	{
		j = WIN_HEIGHT / 2;
		while (j < WIN_HEIGHT)
		{
			pixel_put(all->mlx, i, j, all->color_floor);
			j++;
		}
		i++;
	}
}

void	background_render(t_global *all)
{
	get_color(all);
	render_ceiling(all);
	render_floor(all);
}
