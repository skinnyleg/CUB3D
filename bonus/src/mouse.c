/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/05 22:36:21 by hmoubal           #+#    #+#             */
/*   Updated: 2022/12/06 00:00:05 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

int	ft_mouse_hook(int x, int y, t_global *all)
{
	static int	axe_x;
	t_player	*p;

	(void)y;
	p = all->player;
	if (x > WIN_WIDTH || x < 0 || y < 0 || y > WIN_HEIGHT)
	{
		p->rla = 0;
		return (0);
	}
	if (x == axe_x)
		p->rla = 0;
	if (x > axe_x)
		p->rla = 1;
	if (x < axe_x)
		p->rla = -1;
	axe_x = x;
	return (0);
}
