/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:14:07 by med-doba          #+#    #+#             */
/*   Updated: 2022/11/05 21:52:47 by med-doba         ###   ########.fr       */
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

void	ft_player_pix(t_global *all, int color, int j, int i)
{
	int	x;
	int	y;
	i= 0;
	j =0;

	y = ((int) all->pos_y * 30 + i);
	while ((y < ((int) all->pos_y * 30 + 3 +i)))
	{
		x = ((int) all->pos_x * 30 +j);
		while (x < ((int)all->pos_x * 30 + 3 + j))
		{

				img_pix_put(all, x++, y, color);
				puts("zz");
		}
		y++;
	}
}

void	ft_render_(t_global *all, char c)
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
			{
				ft_block_1(all, 255, j, i);
				ft_render_move(all, c);
			}
		}
	}
}
void	initialite_mini(t_global *all)
{
	all->mini->rotateangle = M_PI / 2;
	all->mini->rotatespeed = 2 * ( M_PI / 180);
	all->mini->movespeed = 1.0;
	all->mini->walkdirection = 0;
	all->mini->turndirection = 0;
	all->mini->radius = 3;
	all->mini->x = 0;
	all->mini->y = 0;
}

void	ft_render_move(t_global *all, char c)
{
	// double	movesteps_x;
	// double	movesteps_y;

	// mlx_clear_window(all->mlx->mlx_ptr, all->mlx->mlx_win);
	// all->mini->rotateangle += all->mini->turndirection * all->mini->rotatespeed;
	// if (c == 'x')
	// {
	// 	movesteps_x = all->mini->walkdirection * all->mini->movespeed;
	// 	all->pos_x += movesteps_x;
	// }
	// if (c == 'y')
	// {
	// 	movesteps_y = all->mini->turndirection * all->mini->movespeed;
	// 	all->pos_y += movesteps_y;
	// }
	c = 0;
	ft_PutCircle(all, all->pos_x, all->pos_y, all->mini->radius);
}

void	ft_replace(t_global *all, char c)
{
	all->mini->img = mlx_new_image(all->mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	all->mini->addr = mlx_get_data_addr(all->mini->img, &all->mini->bpp, &all->mini->size_line, &all->mini->endian);
	ft_render_(all, c);
	// ft_render_move(all);
	// ft_render_mini_map(all);
	mlx_put_image_to_window(all->mlx->mlx_ptr,all->mlx->mlx_win, all->mini->img, 0, 0);
}

void	ft_mlx(t_global *all)
{

	all->mlx = malloc(sizeof(t_mlx));
	if (!all->mlx)
		return ;
	all->mini = malloc(sizeof(t_mini));
	if (!all->mini)
		return;
	initialite_mini(all);
	all->mlx->mlx_ptr = mlx_init();
	all->mlx->mlx_win = mlx_new_window(all->mlx->mlx_ptr, WIN_WIDTH ,WIN_HEIGHT, "cub3D");
	ft_find_position(all, &all->pos_x, &all->pos_y);
	all->pos_x *= 30;
	all->pos_y *= 30;
	printf("x = %d >>> y = %d\n", all->pos_x, all->pos_y);
	ft_replace(all, 0);
	mlx_hook(all->mlx->mlx_win, 02, 1L<<0, key_hook, all);
	mlx_loop(all->mlx->mlx_ptr);
}
