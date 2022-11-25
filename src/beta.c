/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:14:07 by med-doba          #+#    #+#             */
/*   Updated: 2022/11/24 13:26:30 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

void	ft_block(t_global *all, int color, int j, int i)
{
	int	x;
	int y;

	y = (i * 30 + 170);
	while ((y < (i * 30 + 30 + 170)))
	{
		x = (j * 30+ 170);
		while (x < (j * 30 + 30 + 170))
		{
			if (sqrt((170 - y) * (170 - y) + (170 - x) * (170 - x)) <= 150)
				img_pix_put(all, x, y, color);
			x++;
		}
		y++;
	}
}

void	ft_block_1(t_global *all, int color, int j, int i)
{
	int	x;
	int y;

	y = (i * 30);
	while ((y < (i * 30 + 30)))
	{
		x = (j * 30);
		while (x < (j * 30 + 30))
				img_pix_put(all, x++, y, color);
		y++;
	}
}

void	ft_draw_line(t_global *all, double x1, double y1, double x2, double y2)
{
	double	delat_y;
	double	delat_x;
	double	x_inc;
	double	y_inc;
	double	steps;

	delat_y = y2 - y1;
	delat_x = x2 - x1;
	if (abs((int)delat_y) > abs((int)delat_x))
		steps = abs((int)delat_y);
	else
		steps = abs((int)delat_x);
	x_inc = delat_x / steps;
	y_inc = delat_y / steps;
	while(0 < steps)
	{
		img_pix_put(all, x1, y1, 16776960);
		x1 += x_inc;
		y1 += y_inc;
		steps--;
	}
}

void	ft_render_(t_global *all)
{
	int	i;
	int	j;

	i = -1;
	mlx_clear_window(all->mlx->mlx_ptr, all->mlx->mlx_win);
	while (all->map->map[++i])
	{
		j = -1;
		while (all->map->map[i][++j])
		{
			if (all->map->map[i][j] == '1')
				ft_block_1(all, 16711680, j, i);
			else if (all->map->map[i][j] == '0')
				ft_block_1(all, 255, j, i);
			else if (ft_derection(all->map->map[i][j]))
				ft_block_1(all, 255, j, i);
		}
	}
	ft_render_move(all);
}

void	ft_rays_casting(t_global *all)
{
	// int		colums = 0;
	double	rayangle = all->mini->rotateangle - (FOV / 2);
	int		i = 0;
	while(i < WIN_WIDTH)
	{
		double tmpx = all->pos_x + cos(rayangle) * 45;
		double tmpy = all->pos_y + sin(rayangle) * 45;
		// if (ft_checkwall(all, tmpx, tmpy) == 1)
			ft_draw_line(all, all->pos_x, all->pos_y, tmpx, tmpy);
		rayangle += (FOV / NUM_RAYS);
		i++;
	}
}

void	ft_render_move(t_global *all)
{
	ft_PutCircle(all, all->pos_x, all->pos_y, all->mini->radius);
	double tmpx = all->pos_x + cos(all->mini->rotateangle) * 32;
	double tmpy = all->pos_y + sin(all->mini->rotateangle) * 32;
	ft_draw_line(all, all->pos_x, all->pos_y, tmpx, tmpy);
	ft_rays_casting(all);
}

void	initialite_mini(t_global *all)
{
	all->mini->rotateangle = (3 * M_PI) / 2;
	all->mini->rotatespeed = 1.5 * ( M_PI / 180);
	all->mini->movespeed = 2.0;
	all->mini->walkdirection = 0;
	all->mini->turndirection = 0;
	all->mini->directionangle = 0;
	all->mini->radius = 3;
	all->mini->x = 0;
	all->mini->y = 0;
	all->mini->movesteps = 0;
}

void	ft_replace(t_global *all)
{
	all->mini->img = mlx_new_image(all->mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	all->mini->addr = mlx_get_data_addr(all->mini->img, &all->mini->bpp, &all->mini->size_line, &all->mini->endian);
	ft_render_(all);
	// ft_render_mini_map(all);
	mlx_put_image_to_window(all->mlx->mlx_ptr,all->mlx->mlx_win, all->mini->img, 0, 0);
}

void	ft_mlx(t_global *all)
{

	all->mlx = malloc(sizeof(t_mlx));
	if (!all->mlx)
		return (exit(1));
	all->mini = malloc(sizeof(t_mini));
	if (!all->mini)
		return (exit(1));
	initialite_mini(all);
	all->mlx->mlx_ptr = mlx_init();
	all->mlx->mlx_win = mlx_new_window(all->mlx->mlx_ptr, WIN_WIDTH ,WIN_HEIGHT, "cub3D");
	ft_find_position(all, &all->pos_x, &all->pos_y);
	all->pos_x *= 30;
	all->pos_y *= 30;
	ft_replace(all);
}
