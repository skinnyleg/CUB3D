/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keys.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 15:55:11 by hmoubal           #+#    #+#             */
/*   Updated: 2022/11/12 16:53:03 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

int	keypress(int keycode, t_global *all)
{
	if (keycode == 53)
		ft_close(all);
	if (keycode == 13)
		all->player->udd = 1;
	if (keycode == 1)
		all->player->udd = -1;
	if (keycode == 123)
		all->player->rla = -1;
	if (keycode == 124)
		all->player->rla = 1;
	if (keycode == 0)
		all->player->rld = 1;
	if (keycode == 2)
		all->player->rld = -1;
	return (0);
}

int	keyrelease(int keycode, t_global *all)
{
	if (keycode == 13)
		all->player->udd = 0;
	if (keycode == 1)
		all->player->udd = 0;
	if (keycode == 123)
		all->player->rla = 0;
	if (keycode == 124)
		all->player->rla = 0;
	if (keycode == 0)
		all->player->rld = 0;
	if (keycode == 2)
		all->player->rld = 0;
	return (0);
}

void	forward_back_motion(t_global *all)
{
	double		x;
	double		y;
	t_player	*p;

	p = all->player;
	x = p->pos_tilex;
	y = p->pos_tiley;
	y += ((double)(p->vel * p->udd) * sin(p->rotateangle));
	x += ((double)(p->vel * p->udd) * cos(p->rotateangle));
	if (iswall(all, x, y) == 0)
	{
		p->y = y - (p->pos_tiley - p->y);
		p->x = x - (p->pos_tilex - p->x);
	}
}

void	left_right_motion(t_global *all)
{
	double		x;
	double		y;
	t_player	*p;

	p = all->player;
	x = p->pos_tilex;
	y = p->pos_tiley;
	x += sin(p->rotateangle) * (double)(p->rld * p->vel);
	y -= cos(p->rotateangle) * (double)(p->rld * p->vel);
	if (iswall(all, x, y) == 0)
	{
		p->y = y - (p->pos_tiley - p->y);
		p->x = x - (p->pos_tilex - p->x);
	}
}

int	move_player(t_global *all)
{
	t_player	*p;
	t_mlx		*mlx_cpy;
	double		tmp_rotate;

	mlx_cpy = all->mlx;
	p = all->player;
	if (p->udd == 0 && p->rld == 0 && p->rla == 0)
		return (0);
	forward_back_motion(all);
	left_right_motion(all);
	tmp_rotate = p->rotateangle + (p->rotatespeed * p->rla);
	ft_normalize_angle(&tmp_rotate);
	p->rotateangle = tmp_rotate;
	mlx_destroy_image(mlx_cpy->mlx_ptr, mlx_cpy->image);
	mlx_clear_window(mlx_cpy->mlx_ptr, mlx_cpy->mlx_win);
	raycaster(all);
	return (0);
}
