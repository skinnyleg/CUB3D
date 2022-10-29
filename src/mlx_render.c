/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:27:45 by hmoubal           #+#    #+#             */
/*   Updated: 2022/10/29 17:18:42 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

void	init_player(t_player *player)
{
	player->x = 0;
	player->y = 0;
	player->vel = 3;
	player->rld = 0;
	player->udd = 0;
	player->rotateangle = M_PI / 2 ;
	player->rotatespeed = 10 * (M_PI / 180);
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
	t_player	*p;

	// aspect_ratio(all, &tile_width, &tile_height);
	p = all->player;
	p->tile_height = WIN_HEIGHT / all->map->height;
	p->tile_width = WIN_WIDTH / all->map->width;
	x = i * p->tile_width;
	while (x < ((i * p->tile_width) + p->tile_width))
	{
		y = j * p->tile_height;
		while (y < ((j * p->tile_height) + p->tile_height))
		{
			pixel_put(all->mlx, x, y, color);
			y++;
		}
		x++;
	}
}

void	render_rays(t_global *all, double degree, int x, int y)
{
	int		dx;
	int		dy;
	double		ddx;
	double		ddy;
	double	x_inc;
	double	y_inc;
	int		step;

	dx = cos(degree) * 60;
	dy = sin(degree) * 60;
	if (abs(dx) > abs(dy))
		step = abs(dx);
	else
		step = abs(dy);
	x_inc = ((double)dx / (double)step);
	y_inc = ((double)dy / (double)step);
	dx = x;
	dy = y;
	ddx = dx;
	ddy = dy;
	while (step != 0)
	{
		pixel_put(all->mlx, dx, dy, 16711680);
		ddx += x_inc;
		ddy += y_inc;
		dx = round(ddx);
		dy = round(ddy);
		step--;
	}
}

void	ft_normalize_angle(double *angle)
{
	*angle = fmod(*angle, (2 * M_PI));
	if (*angle < 0)
		*angle = (2 * M_PI) + *angle;
}

void	render_player(t_global *all, int i, int j, int color)
{
	double		degree;
	t_player	*p;

	p = all->player;
	p->tile_height = WIN_HEIGHT / all->map->height;
	p->tile_width = WIN_WIDTH / all->map->width;
	p->pos_tilex = p->x;
	p->pos_tiley = p->y;
	// p->pos_tilex += i * p->tile_width + (p->tile_width / 2);
	p->pos_tilex += i * p->tile_width;
	// while (p->pos_tilex < ((i * p->tile_width) + p->tile_width + p->x))
	// {
		// p->pos_tiley = p->y;
		// p->pos_tiley += j * p->tile_height + (p->tile_height / 2);
		p->pos_tiley += j * p->tile_height;
		// while (p->pos_tiley < ((j * p->tile_height) + p->tile_height + p->y))
		// {
			pixel_put(all->mlx, p->pos_tilex, p->pos_tiley, color);
			// p->pos_tiley++;
		// }
		// p->pos_tilex++;
	// }
	// p->pos_tilex = p->x + (i * p->tile_width) + (p->tile_width / 2);
	// p->pos_tiley = p->y + (j * p->tile_height) + (p->tile_height / 2);
	// degree = (all->player->rotateangle - (FOV / 2));
	degree = (all->player->rotateangle);
	int count = 0;
	while (count < 1)
	{
		ft_normalize_angle(&degree);
		// printf("angle == %f\n", degree);
		render_rays(all, degree, p->pos_tilex, p->pos_tiley);
		degree += (0.04 * (M_PI / 180));
		count++;
	}
	p->pos_tilex = p->x + (i * p->tile_width);
	p->pos_tiley = p->y + (j * p->tile_height);
}

int	ft_close(t_global *all)
{
	destroy_all(all);
	exit(0);
	return (0);
}

int	iswall(t_global *all, double x, double y)
{
	int	gridx;
	int	gridy;

	// printf("x == %f\ny == %f\n", x, y);
	if (x < 0 || x > WIN_WIDTH || y < 0 || y > WIN_HEIGHT)
	{
		// printf("max bounderies\n");
		return (1);
	}
	gridx = floor((x / all->player->tile_width));
	gridy = floor((y / all->player->tile_height));
	// printf("gridx == %d\ngridy == %d\n",gridx, gridy);
	if (all->map->map[gridy] != NULL && all->map->map[gridy][gridx] == '1')
		return (1);
	return (0);
}

void	move_forward(t_global *all)
{
	t_player	*p;
	t_mlx		*mlx_cpy;
	double		x;
	double		y;

	mlx_cpy = all->mlx;
	p = all->player;
	p->udd = 1;
	x = p->pos_tilex;
	y = p->pos_tiley;
	y += (p->vel * p->udd * sin(p->rotateangle));
	x += (p->vel * p->udd * cos(p->rotateangle));
	if (iswall(all, x, y) == 0)
	{
		p->y = y - (p->pos_tiley - p->y);
		p->x = x - (p->pos_tilex - p->x);
	}
	// p->x +=(p->vel * p->udd);
	// printf("degree == %f\nsin(degree) == %f\ncos(degree) == %f\ny == %d\nx == %d\n", p->rotateangle, sin(p->rotateangle), cos(p->rotateangle), p->y , p->x);
	// printf("udd == %d\n", p->udd);
	mlx_destroy_image(mlx_cpy->mlx_ptr, mlx_cpy->image);
	// mlx_clear_window(mlx_cpy->mlx_ptr, mlx_cpy->mlx_win);
	render_minimap(all);
}

void	move_backwards(t_global *all)
{
	t_player	*p;
	t_mlx		*mlx_cpy;
	double		x;
	double		y;

	mlx_cpy = all->mlx;
	p = all->player;
	p->udd = -1;
	x = p->pos_tilex;
	y = p->pos_tiley;
	y += (p->vel * p->udd * sin(all->player->rotateangle));
	x += (p->vel * p->udd * cos(all->player->rotateangle));
	if (iswall(all, x, y) == 0)
	{
		p->y = y - (p->pos_tiley - p->y);
		p->x = x - (p->pos_tilex - p->x);
	}
	// p->x +=(p->vel * p->udd);
	// p->y = p->y + (p->vel * p->udd);
	mlx_destroy_image(mlx_cpy->mlx_ptr, mlx_cpy->image);
	// mlx_clear_window(mlx_cpy->mlx_ptr, mlx_cpy->mlx_win);
	render_minimap(all);
}

void	move_left(t_global *all)
{
	t_player	*p;
	t_mlx		*mlx_cpy;
	double		x;
	double		y;
	// int			i;
	// int			j;

	mlx_cpy = all->mlx;
	p = all->player;
	p->udd = 1;
	x = p->pos_tilex;
	y = p->pos_tiley;
	// x = p->x + sin(p->rotateangle) * (double)(p->udd * p->vel);
	// y = p->y - cos(p->rotateangle) * (double)(p->udd * p->vel);
	x += sin(p->rotateangle) * (double)(p->udd * p->vel);
	y -= cos(p->rotateangle) * (double)(p->udd * p->vel);
	if (iswall(all, x, y) == 0)
	{
		p->y = y - (p->pos_tiley - p->y);
		p->x = x - (p->pos_tilex - p->x);
	}
	// printf("cos == %f\nsin == %f\n", (double)p->vel * (double)p->udd * cos(p->rotateangle), sin(p->rotateangle));
	// p->x +=(p->vel * p->udd);
	// printf("degree == %f\nsin(degree) == %f\ncos(degree) == %f\ny == %d\nx == %d\n", p->rotateangle, sin(p->rotateangle), cos(p->rotateangle), p->y , p->x);
	// printf("udd == %d\n", p->udd);
	mlx_destroy_image(mlx_cpy->mlx_ptr, mlx_cpy->image);
	// mlx_clear_window(mlx_cpy->mlx_ptr, mlx_cpy->mlx_win);
	render_minimap(all);
}

void	move_right(t_global *all)
{
	t_player	*p;
	t_mlx		*mlx_cpy;
	double		x;
	double		y;

	mlx_cpy = all->mlx;
	p = all->player;
	p->udd = -1;
	// p->y += (p->vel * p->udd * cos(all->player->rotateangle));
	// p->x += (p->vel * p->udd * sin(all->player->rotateangle));
	x = p->pos_tilex;
	y = p->pos_tiley;
	x += sin(p->rotateangle) * (double)(p->udd * p->vel);
	y -= cos(p->rotateangle) * (double)(p->udd * p->vel);
	if (iswall(all, x, y) == 0)
	{
		p->y = y - (p->pos_tiley - p->y);
		p->x = x - (p->pos_tilex - p->x);
	}
	// p->x +=(p->vel * p->udd);
	// p->y = p->y + (p->vel * p->udd);
	mlx_destroy_image(mlx_cpy->mlx_ptr, mlx_cpy->image);
	// mlx_clear_window(mlx_cpy->mlx_ptr, mlx_cpy->mlx_win);
	render_minimap(all);
}


void	rotate_left(t_global *all)
{
	t_player	*p;
	t_mlx		*mlx_cpy;
	double		tmp_rotate;

	mlx_cpy = all->mlx;
	p = all->player;
	p->rld = -1;
	tmp_rotate = p->rotateangle + (p->rotatespeed * p->rld);
	ft_normalize_angle(&tmp_rotate);
	p->rotateangle = tmp_rotate;
	// p->rotateangle += p->rotatespeed * p->rld;
	// p->x = p->x + (p->vel * p->rld);
	mlx_destroy_image(mlx_cpy->mlx_ptr, mlx_cpy->image);
	// mlx_clear_window(mlx_cpy->mlx_ptr, mlx_cpy->mlx_win);
	render_minimap(all);
}

void	rotate_right(t_global *all)
{
	t_player	*p;
	t_mlx		*mlx_cpy;
	double		tmp_rotate;

	mlx_cpy = all->mlx;
	p = all->player;
	p->rld = 1;
	tmp_rotate = p->rotateangle + (p->rotatespeed * p->rld);
	ft_normalize_angle(&tmp_rotate);
	p->rotateangle = tmp_rotate;
	// p->rotateangle += p->rotatespeed * p->rld;
	// p->x = p->x + (p->vel * p->rld);
	mlx_destroy_image(mlx_cpy->mlx_ptr, mlx_cpy->image);
	// mlx_clear_window(mlx_cpy->mlx_ptr, mlx_cpy->mlx_win);
	render_minimap(all);
}


int	ft_keystroke_ubuntu(int keycode, t_global *all)
{
	if (keycode == 65307)
		ft_close(all);
	if (keycode == 119)
		move_forward(all);
	if (keycode == 115)
		move_backwards(all);
	if (keycode == 65361)
		rotate_left(all);
	if (keycode == 65363)
		rotate_right(all);
	if (keycode == 97)
		move_left(all);
	if (keycode == 100)
		move_right(all);
	return (0);
}

int	ft_keystroke(int keycode, t_global *all)
{
	if (keycode == 53)
		ft_close(all);
	if (keycode == 13)
		move_forward(all);
	if (keycode == 1)
		move_backwards(all);
	if (keycode == 123)
		rotate_left(all);
	if (keycode == 124)
		rotate_right(all);
	if (keycode == 0)
		move_left(all);
	if (keycode == 2)
		move_right(all);
	return (0);
}

int	render_minimap(t_global *all)
{
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
	mlx_hook(all->mlx->mlx_win, 17, 0, ft_close, all);
	// mlx_hook(all->mlx->mlx_win, 2, 0, ft_keystroke, all);
	mlx_key_hook(all->mlx->mlx_win, ft_keystroke_ubuntu, all);
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
