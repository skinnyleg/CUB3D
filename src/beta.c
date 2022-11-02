/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:14:07 by med-doba          #+#    #+#             */
/*   Updated: 2022/11/02 10:49:35 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

int	key_hook(int keycode, t_global *all)
{
	if (keycode == 13)
		ft_up(all);
	else if (keycode == 1)
		ft_down(all);
	else if (keycode == 0)
		ft_left(all);
	else if (keycode == 2)
		ft_rigth(all);
	return (0);
}

void	img_pix_put(t_global *all, int x, int y, int color)
{
	char	*pixel;

	pixel = all->mini->addr + (y * all->mini->size_line + x * (all->mini->bpp / 8));
	*(int *)pixel = color;
}

void	render_background(t_global *all)
{
	int	i;
	int	j;
	int	x,y;
	int lop_y = 0;
	int lop_x = 0;

	i = 0;
	y = 0;
	while (i < WIN_HEIGHT && all->map->map[y])
	{
		j = 0;
		x = 0;
		while (j < WIN_WIDTH && all->map->map[y][x])
		{
			if (all->map->map[y][x] == '1')
			{
				lop_x= j + 30;
				while (j < lop_x)
					img_pix_put(all, j++, i, 16711680);
			}
			else if (all->map->map[y][x] == '0')
			{
				lop_x = j + 30;
				while (j < lop_x)
					img_pix_put(all, j++, i, 255);
			}
			x++;
		}
		if (lop_y == i)
		{
			lop_y += 30;
			y++;
		}
		++i;
	}
}

void	ft_replace(t_global *all)
{
	all->mini = malloc(sizeof(t_mini));
	if (!all->mini)
		return;
	all->mini->img = mlx_new_image(all->mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	all->mini->addr = mlx_get_data_addr(all->mini->img, &all->mini->bpp, &all->mini->size_line, &all->mini->endian);
	mlx_clear_window(all->mlx->mlx_ptr, all->mlx->mlx_win);
	render_background(all);
	mlx_put_image_to_window(all->mlx->mlx_ptr,all->mlx->mlx_win, all->mini->img, 0, 0);
	mlx_loop(all->mlx->mlx_ptr);
}

void	ft_mlx(t_global *all)
{
	all->mlx = malloc(sizeof(t_mlx));
	if (!all->mlx)
		return ;
	all->mlx->mlx_ptr = mlx_init();
	all->mlx->mlx_win = mlx_new_window(all->mlx->mlx_ptr, WIN_WIDTH ,WIN_HEIGHT, "cub3D");
	ft_replace(all);
	mlx_key_hook(all->mlx->mlx_win, key_hook, all);
	mlx_loop(all->mlx->mlx_ptr);
}
