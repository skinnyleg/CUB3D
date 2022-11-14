/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_background.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 16:53:46 by hmoubal           #+#    #+#             */
/*   Updated: 2022/11/14 01:38:44 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

// char	*get_hex()
// {

// }

// void	convert_color(t_global *all, char *key, char *content)
// {
// 	char	*hex_color;

// 	hex_color = get_hex(content);
// 	if (ft_strcmp(key, "C") == 0)
// 		all->color_ceiling = get_int(hex_color);
// 	else
// 		all->color_floor = get_int(hex_color);
// }

// void	get_color(t_global *all)
// {
// 	t_paraup	*up;

// 	up = all->up;
// 	while (up != NULL)
// 	{
// 		if (ft_strcmp(up->dir, "F") == 0 || ft_strcmp(up->dir, "C") == 0)
// 			convert_color(all, up->dir, up->value);
// 		up = up->next;
// 	}
// }

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
			pixel_put(all->mlx, i, j, 16711680);
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
			pixel_put(all->mlx, i, j, 65280);
			j++;
		}
		i++;
	}
}

void	background_render(t_global *all)
{
	// get_color(all);
	render_ceiling(all);
	render_floor(all);
}
