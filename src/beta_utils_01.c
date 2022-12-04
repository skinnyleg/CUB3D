/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beta_utils_01.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 11:27:39 by med-doba          #+#    #+#             */
/*   Updated: 2022/12/03 23:43:09 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

void	img_pix_put(t_global *all, int x, int y, int color)
{
	char	*pixel;

	if (x >= 0 && x < WIN_WIDTH && y >= 0 &&  y < WIN_HEIGHT)
	{
		// printf("x == %d and y == %d\n", x , y);
		pixel = all->mini->addr + (y * all->mini->size_line + x * (all->mini->bpp / 8));
		*(int *)pixel = color;
	}
}

int	key_hook(t_global *all)
{
	if (all->mini->turndirection == 0 && all->mini->directionangle == 0 && all->mini->walkdirection == 0)
		return (0);
	if (all->mini->walkdirection != 0)
		ft_move_up(all);
	if (all->mini->turndirection != 0)
		ft_move_left(all);
	if (all->mini->directionangle != 0)
	{
		all->mini->rotateangle += all->mini->directionangle * all->mini->rotatespeed;
		all->mini->rotateangle = ft_normilaze(all->mini->rotateangle);
	}
	mlx_destroy_image(all->mlx->mlx_ptr, all->mini->img);
	ft_replace(all);
	return (0);
}

int	ft_KeyPress(int keycode, t_global *all)
{
	if (keycode == 53)
		return (destroy_all(all), exit(0), 0);
	if (keycode == 13)
		all->mini->walkdirection = 1;
	if (keycode == 1)
		all->mini->walkdirection = -1;
	if (keycode == 0)
		all->mini->turndirection = -1;
	if (keycode == 2)
		all->mini->turndirection = 1;
	if (keycode == 124)
		all->mini->directionangle = 1;
	if (keycode == 123)
		all->mini->directionangle = -1;
	return (0);
}

int	ft_KeyRelease(int keycode, t_global *all)
{
	if (keycode == 13)
		all->mini->walkdirection = 0;
	if (keycode == 1)
		all->mini->walkdirection = 0;
	if (keycode == 0)
		all->mini->turndirection = 0;
	if (keycode == 2)
		all->mini->turndirection = 0;
	if (keycode == 124)
		all->mini->directionangle = 0;
	if (keycode == 123)
		all->mini->directionangle = 0;
	return (0);
}

int	ft_mouse_hook(int x, int y, t_global *all)
{
	(void)y;
	static int	axe_x;
	if (x > WIN_WIDTH || x < 0 || y < 0 || y > WIN_HEIGHT)
		return 0;
	// printf("ps x = %d\n", x);
	mlx_clear_window(all->mlx->mlx_ptr, all->mlx->mlx_win);
	mlx_destroy_image(all->mlx->mlx_ptr, all->mini->img);
	// all->pos_x -= sin(all->mini->rotateangle) * all->mini->movesteps;
	if (x > axe_x)
		all->mini->rotateangle += all->mini->directionangle * all->mini->rotatespeed + 0.023;
	if (x < axe_x)
		all->mini->rotateangle += all->mini->directionangle * all->mini->rotatespeed - 0.023;
	ft_replace(all);
	axe_x = x;
	return 0;
}

// void	ft_render_mini_map(t_global *all)
// {
// 	int	i;
// 	int	j;
// 	int x,y;

// 	mlx_clear_window(all->mlx->mlx_ptr, all->mlx->mlx_win);
// 	// ft_find_position(all, &j, &i);
// 	ft_backround(all, 16777215);
// 	y = i;
// 	x = j;
// 	i -= 10;
// 	while (i < 0)
// 		i++;
// 	while (all->map->map[i])
// 	{
// 		j = 0;
// 		while (all->map->map[i][j])
// 		{
// 			if (all->map->map[i][j] == '1')
// 				ft_block(all, 16711680, j-x, i-y);
// 			else if (all->map->map[i][j] == '0')
// 				ft_block(all, 255, j-x, i-y);
// 			else if(ft_derection(all->map->map[i][j]))
// 				ft_block(all, 16776960, j-x, i-y);
// 			j++;
// 		}
// 		i++;
// 	}
// 	ft_PutCircle(all, 170, 170, 150);
// }
