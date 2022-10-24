/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:27:45 by hmoubal           #+#    #+#             */
/*   Updated: 2022/10/24 14:15:28y hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

void	init_player(t_player *player)
{
	player->x = 0;
	player->y = 0;
	player->vel = 10;
	player->rld = 0;
	player->udd = 0;
	player->rotateangle = M_PI ;
	player->rotatespeed = 20 * (M_PI / 180);
}

int	set_mlx(t_global *all)
{
	t_mlx	*mlx_cpy;

	all->mlx = (t_mlx *)malloc(sizeof(t_mlx) * 1);
	if (all->mlx == NULL)
		return (destroy_all(all), -1);
	all->player = (t_player *)malloc(sizeof(t_player) * 1);
	if (all->player == NULL)
		return (destroy_all(all), -1);
	init_player(all->player);
	mlx_cpy = all->mlx;
	mlx_cpy->mlx_ptr = mlx_init();
	if (mlx_cpy->mlx_ptr == NULL)
		return (destroy_all(all), -1);
	mlx_cpy->mlx_win = mlx_new_window(mlx_cpy->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	return (0);
}

void	pixel_put(t_mlx *mlx, int x, int y, int color)
{
	if ((x >= 0 && x < WIN_WIDTH) && (y >= 0 && y < WIN_HEIGHT))
	{
		*((int *)&mlx->get_addr[(y * mlx->size_line) + \
		(x * mlx->bits_per_pixel / 8)]) = color;
	}
}

void	aspect_ratio(t_global *all, int *tile_width, int *tile_height)
{
	double	resizewidth;
	double	resizeheight;
	double	aspect;

	resizewidth = all->map->width;
	resizeheight = all->map->height;
	aspect = resizewidth / resizeheight;
	if (resizewidth > MINI_WIDTH)
	{
		resizewidth = MINI_WIDTH;
		resizeheight = resizewidth / aspect;
	}
	if (resizeheight > MINI_HEIGHT)
	{
		aspect = resizewidth / resizeheight;
		resizeheight = MINI_HEIGHT;
		resizewidth = resizeheight * aspect;
	}
	*tile_width = (resizewidth / all->player->x) + 4;
	*tile_height = (resizeheight / all->player->y) + 4;
}

void	render_block(t_global *all, int i, int j, int color)
{
	int		x;
	int		y;
	// int		tile_width;
	// int		tile_height;

	// aspect_ratio(all, &tile_width, &tile_height);
	// tile_height = TILE_SIZE;
	// tile_width = TILE_SIZE;
	x = i * TILE_SIZE;
	while (x < ((i * TILE_SIZE) + TILE_SIZE))
	{
		y = j * TILE_SIZE;
		while (y < ((j * TILE_SIZE) + TILE_SIZE))
		{
			pixel_put(all->mlx, x, y, color);
			y++;
		}
		x++;
	}
}

void	render_rays(t_global *all, double degree, int color)
{
	int		dx;
	int		dy;
	double		ddx;
	double		ddy;
	double	x_inc;
	double	y_inc;
	int		step;

	dx = 1000 - all->player->x;
	dy = (tan(degree) * dx);
	printf("dx == %d\ndy == %d\ndegree == %f\ntan(degree) == %f\n", dx, dy, degree, tan(degree));
	if (abs(dx) > abs(dy))
		step = abs(dx);
	else
		step = abs(dy);
	x_inc = ((double)dx / (double)step);
	y_inc = ((double)dy / (double)step);
	dx = all->player->x;
	dy = all->player->y;
	ddx = all->player->x;
	ddy = all->player->y;
	while (step != 0)
	{
		pixel_put(all->mlx, dx, dy, color);
		ddx += x_inc;
		ddy += y_inc;
		dx = round(ddx);
		dy = round(ddy);
		step--;
	}
}

void	render_player(t_global *all, int i, int j, int color)
{
	// int			tile_width;
	// int			tile_height;
	double		x;
	double		y;
	double		degree;

	(void)i;
	(void)j;
	x = 500;
	y = 500;
	all->player->x = x;
	all->player->y = y;
	pixel_put(all->mlx, x, y, color);
	// if (all->player->rotateangle > 2 * M_PI)
	// {
	// 	printf("lol\n");
	// 	all->player->rotateangle = 0;
	// }
	degree = all->player->rotateangle * (M_PI / 180);
	printf("degree == %f\ndest == %f\n",all->player->rotateangle, ((all->player->rotateangle - FOV) * (M_PI / 180)));
	while (degree > (double)((all->player->rotateangle - FOV) * (M_PI / 180)))
	{
		// printf("lol\n");
		render_rays(all, degree, color);
		degree -= (2 * (M_PI / 180));
		printf("inside degree == %f\n", (degree * 180) / M_PI);
	}
	// aspect_ratio(all, &tile_width, &tile_height);
	// x += i * tile_width;
	// while (x < ((i * tile_width) + tile_width + all->player->x))
	// {
		// y += j * tile_height;
		// while (y < ((j * tile_height) + tile_height + all->player->y))
		// {
			// y++;
		// }
		// x++;
	// }
}

int	ft_close(t_global *all)
{
	destroy_all(all);
	exit(0);
	return (0);
}

void	move_up(t_global *all)
{
	t_player	*p;
	t_mlx		*mlx_cpy;

	mlx_cpy = all->mlx;
	p = all->player;
	p->udd = -1;
	p->y = p->y + (p->vel * p->udd);
	mlx_clear_window(mlx_cpy->mlx_ptr, mlx_cpy->mlx_win);
	render_minimap(all);
}

void	move_down(t_global *all)
{
	t_player	*p;
	t_mlx		*mlx_cpy;

	mlx_cpy = all->mlx;
	p = all->player;
	p->udd = 1;
	p->y = p->y + (p->vel * p->udd);
	mlx_clear_window(mlx_cpy->mlx_ptr, mlx_cpy->mlx_win);
	render_minimap(all);
}

void	move_left(t_global *all)
{
	t_player	*p;
	t_mlx		*mlx_cpy;

	mlx_cpy = all->mlx;
	p = all->player;
	p->rld = -1;
	p->rotateangle += p->rotatespeed * p->rld;
	// p->x = p->x + (p->vel * p->rld);
	mlx_clear_window(mlx_cpy->mlx_ptr, mlx_cpy->mlx_win);
	render_minimap(all);
}

void	move_right(t_global *all)
{
	t_player	*p;
	t_mlx		*mlx_cpy;

	mlx_cpy = all->mlx;
	p = all->player;
	p->rld = 1;
	p->rotateangle += p->rotatespeed * p->rld;
	// p->x = p->x + (p->vel * p->rld);
	mlx_clear_window(mlx_cpy->mlx_ptr, mlx_cpy->mlx_win);
	render_minimap(all);
}

int	ft_keystroke(int keycode, t_global *all)
{
	if (keycode == 53)
		ft_close(all);
	if (keycode == 13)
		move_up(all);
	if (keycode == 1)
		move_down(all);
	if (keycode == 0)
		move_left(all);
	if (keycode == 2)
		move_right(all);
	return (0);
}

int	render_minimap(t_global *all)
{
	int		color;
	t_map	*map;
	t_mlx	*mlx_cpy;

	mlx_cpy = all->mlx;
	all->player->rld = 0;
	all->player->udd = 0;
	mlx_cpy->image = mlx_new_image(all->mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx_cpy->get_addr = mlx_get_data_addr(mlx_cpy->image, &(mlx_cpy->bits_per_pixel), &(mlx_cpy->size_line), &(mlx_cpy->endian));
	if (mlx_cpy->get_addr == NULL)
		return (destroy_all(all), -1);
	map = all->map;
	all->a = 0;
	color = 16711680;
	while (all->a < map->height)
	{
		all->l = 0;
		while (all->l < map->width)
		{
			if (map->map[all->a][all->l] != ' ')
			{
				if (map->map[all->a][all->l] == '1')
					render_block(all, all->l, all->a, 8421504);
				if (map->map[all->a][all->l] == '0')
					render_block(all, all->l, all->a, 65280);
				if (map->map[all->a][all->l] == 'N' || map->map[all->a][all->l] == 'E' || map->map[all->a][all->l] == 'W'
						|| map->map[all->a][all->l] == 'S')
					render_block(all, all->l, all->a, 65280);
			}
			all->l++;
		}
		all->a++;
	}
	all->a = 0;
	while (all->a < map->height)
	{
		all->l = 0;
		while (all->l < map->width)
		{
			if (map->map[all->a][all->l] != ' ')
			{
				if (map->map[all->a][all->l] == 'N' || map->map[all->a][all->l] == 'E' || map->map[all->a][all->l] == 'W'
						|| map->map[all->a][all->l] == 'S')
					render_player(all, all->l, all->a, 16711680);
			}
			all->l++;
		}
		all->a++;
	}
	mlx_put_image_to_window(all->mlx->mlx_ptr, all->mlx->mlx_win, all->mlx->image, 0, 0);
	mlx_destroy_image(all->mlx->mlx_ptr, all->mlx->image);
	mlx_hook(all->mlx->mlx_win, 17, 0, ft_close, all);
	mlx_hook(all->mlx->mlx_win, 2, 0, ft_keystroke, all);
	mlx_loop(all->mlx->mlx_ptr);
	return (0);
}

void	mlx_render(t_global *all)
{
	if (set_mlx(all) == -1)
		exit(1);
	if (render_minimap(all) == -1)
		exit(1);
}
