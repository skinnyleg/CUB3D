/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   beta.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 15:14:07 by med-doba          #+#    #+#             */
/*   Updated: 2022/11/29 00:57:32 by med-doba         ###   ########.fr       */
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

	y = (i * TILE_SIZE);
	while ((y < (i * TILE_SIZE + TILE_SIZE)))
	{
		x = (j * TILE_SIZE);
		while (x < (j * TILE_SIZE + TILE_SIZE))
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

double	ft_normilaze(double angle)
{
	angle = fmod(angle, (2 * M_PI));
	if (angle < 0)
		angle += (2 * M_PI);
	return (angle);
}

double	ft_distance(t_global *all, double x1, double y1, double x2, double y2)
{
	(void)all;
	return (sqrt((x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1)));
}

double	ft_intersection_x(t_global *all, double rayangle)
{
	double	delta_x;
	double	delta_y;
	double	x_hit;
	double	y_hit;
	all->raycast->y_hor_wall = 0;
	all->raycast->x_hor_wall = 0;

	y_hit = floor(all->pos_y / (double)TILE_SIZE) * (double)TILE_SIZE;
	if (rayangle > 0 && rayangle < M_PI)//fac down
		y_hit += TILE_SIZE;
	x_hit = all->pos_x + ((y_hit - all->pos_y) / tan(rayangle));
	delta_y = TILE_SIZE;
	if (rayangle > M_PI && rayangle < (2 * M_PI))
		delta_y *= -1;
	delta_x = (double)TILE_SIZE / tan(rayangle);
	if (delta_x > 0 && (rayangle > (0.5 * M_PI) || rayangle < (1.5 * M_PI))){
			// puts("left");
			delta_x *= -1;
		}
	if (delta_x < 0 && (rayangle < (0.5 * M_PI) || rayangle > (1.5 * M_PI))){
			// puts("right");
			delta_x *= -1;
		}
	double	next_y = y_hit;
	double	next_x = x_hit;
	if (rayangle > M_PI && rayangle < (2 * M_PI))
		next_y--;
	while (next_x >= 0 && next_x <= WIN_WIDTH && next_y >= 0 && next_y <= WIN_HEIGHT)
	{
		if (!ft_checkwall(all, next_x, next_y))
		{
			if (rayangle > M_PI && rayangle < (2 * M_PI))
				next_y++;
			if (rayangle > M_PI && rayangle < (2 * M_PI))
			{
				all->raycast->y_hor_wall = next_y-1;
				all->raycast->x_hor_wall = next_x;
			}
			else if (rayangle > 0 && rayangle < (M_PI))
			{
				all->raycast->y_hor_wall = next_y+0.5;
				all->raycast->x_hor_wall = next_x;
			}
			else
			{
				all->raycast->y_hor_wall = next_y;
				all->raycast->x_hor_wall = next_x;
			}
			// all->raycast->y_hor_wall = next_y+1;
			// all->raycast->x_hor_wall = next_x+1;
			return (ft_distance(all, all->pos_x, all->pos_y, all->raycast->x_hor_wall, all->raycast->y_hor_wall));
			break ;
		}
		else
		{
			next_y += delta_y;
			next_x += delta_x;
		}
	}
	return (INT_MAX);
}

double	ft_intersection_y(t_global *all, double rayangle)
{
	double	delta_x;
	double	delta_y;
	double	x_hit;
	double	y_hit;
	all->raycast->y_ver_wall = 0;
	all->raycast->x_ver_wall = 0;

	x_hit = floor(all->pos_x / (double)TILE_SIZE) * (double)TILE_SIZE;
	if (rayangle < (0.5 * M_PI) || rayangle > (1.5 * M_PI))//facright
		x_hit += TILE_SIZE;
	y_hit = all->pos_y + ((x_hit - all->pos_x) * tan(rayangle));
	delta_x = TILE_SIZE;
	if (rayangle > (0.5 * M_PI) && rayangle < (1.5 * M_PI))//faceleft
		delta_x *= -1;
	delta_y = (double)TILE_SIZE * tan(rayangle);
	if (delta_y > 0 && (rayangle > M_PI && rayangle < (2 * M_PI))){
			// puts("up");
			delta_y *= -1;
		}
	if (delta_y < 0 && (rayangle > 0 && rayangle < (M_PI))){
			// puts("down");
			delta_y *= -1;
		}
	double	next_y = y_hit;
	double	next_x = x_hit;
	if (rayangle > (0.5 * M_PI) && rayangle < (1.5 * M_PI))
		next_x--;
	while (next_x >= 0 && next_x <= WIN_WIDTH && next_y >= 0 && next_y <= WIN_HEIGHT)
	{
		if (!ft_checkwall(all, next_x, next_y))
		{
			//var true;
			// if (rayangle > (0.5 * M_PI) && rayangle < (1.5 * M_PI))
			// 	next_x++;
			if (rayangle > (0.5 * M_PI) && rayangle < (1.5 * M_PI))
			{
				all->raycast->y_ver_wall = next_y;
				all->raycast->x_ver_wall = next_x;
			}
			else if (rayangle < (0.5 * M_PI) || rayangle < (1.5 * M_PI))
			{
				all->raycast->y_ver_wall = next_y;
				all->raycast->x_ver_wall = next_x+1;
			}
			else
			{
				all->raycast->y_ver_wall = next_y;
				all->raycast->x_ver_wall = next_x;
			}

			return (ft_distance(all, all->pos_x, all->pos_y, all->raycast->x_ver_wall, all->raycast->y_ver_wall));
			break ;
		}
		else
		{
			next_y += delta_y;
			next_x += delta_x;
		}
	}
	return (INT_MAX);
}

void	ft_rays_casting(t_global *all)
{
	int		i = 0;
	double	wallinx =0;
	double	walliny=0;
	double	rayangle = all->mini->rotateangle - ((double)FOV / 2);

	all->raycast = malloc(sizeof(t_raycast));
	while(i < NUM_RAYS)
	{
		rayangle = ft_normilaze(rayangle);
		all->raycast->hor_dis = ft_intersection_x(all, rayangle);
		all->raycast->ver_dis = ft_intersection_y(all, rayangle);
		// printf("hordistance == %f _____ vertdistance == %f\n", all->raycast->hor_dis, all->raycast->ver_dis);
		if (all->raycast->hor_dis < all->raycast->ver_dis)
		{
			// puts("hor");
			wallinx = all->raycast->x_hor_wall;
			walliny = all->raycast->y_hor_wall;
		}
		else
		{
			// puts("ver");
			wallinx = all->raycast->x_ver_wall;
			walliny = all->raycast->y_ver_wall;
		}
		ft_draw_line(all, all->pos_x, all->pos_y, wallinx, walliny);

		rayangle += ((double)FOV / (double)NUM_RAYS);
		i++;
		// break;
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

void    ft_direction_player(t_global *all, int i, int j)
{
    if (all->map->map[j][i] == 'N')
        all->mini->rotateangle = (M_PI) / 2;
    else if (all->map->map[j][i] == 'S')
        all->mini->rotateangle = (3 * M_PI) / 2;
    else if (all->map->map[j][i] == 'E')
        all->mini->rotateangle = (M_PI);
    else if (all->map->map[j][i] == 'W')
        all->mini->rotateangle = 0;
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
	ft_direction_player(all, all->pos_x, all->pos_y);
	all->pos_x *= TILE_SIZE;
	all->pos_y *= TILE_SIZE;
	ft_replace(all);
}
