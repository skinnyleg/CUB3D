/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:14:07 by med-doba          #+#    #+#             */
/*   Updated: 2022/11/03 21:46:11 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

int	key_hook(int keycode, t_global *all)
{
	if (keycode == 53)
	{
		destroy_all(all);
		exit(0);
	}
	else if (keycode == 13)
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
	if (x < WIN_WIDTH && y < WIN_HEIGHT)
	{
		pixel = all->mini->addr + (y * all->mini->size_line + x * (all->mini->bpp / 8));
		*(int *)pixel = color;
	}
}

void	ft_block(t_global *all, int color, int j, int i)
{
	int	x;
	int y;

	x = (i * 32);
	while ((x < (i * 32 + 32)))
	{
		y = (j * 32);
		while (y < (j * 32 + 32))
		{
			img_pix_put(all, y, x, color);
			y++;
		}
		x++;
	}
}

void ft_PutCircle(t_global *all, int x, int y, int r)
{
	static const double PI = 3.1415926535;
	double i, angle, x1, y1;

	for(i = 0; i < 360; i += 0.1)
	{
		angle = i;
		x1 = r * cos(angle * PI / 180);
		y1 = r * sin(angle * PI / 180);
		if (i < 5)
			printf("f >> x = %f | y = %f\n", x1, y1);
		img_pix_put(all, x + x1, y + y1, 65280);
	}
}

void	render_background(t_global *all)
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
				ft_block(all, 16711680, j, i);
			else if (all->map->map[i][j] == '0')
				ft_block(all, 255, j, i);
			else if(all->map->map[i][j] == 'N')
				ft_block(all, 16776960, j, i);
		}
	}
	ft_PutCircle(all, 170, 170, 150);
}

void	ft_replace(t_global *all)
{
	all->mini = malloc(sizeof(t_mini));
	if (!all->mini)
		return;
	all->mini->img = mlx_new_image(all->mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	all->mini->addr = mlx_get_data_addr(all->mini->img, &all->mini->bpp, &all->mini->size_line, &all->mini->endian);
	render_background(all);
	mlx_put_image_to_window(all->mlx->mlx_ptr,all->mlx->mlx_win, all->mini->img, 0, 0);
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
