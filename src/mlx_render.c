/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/22 20:27:45 by hmoubal           #+#    #+#             */
/*   Updated: 2022/11/02 23:25:38by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

void	init_player(t_player *player)
{
	player->x = 0;
	player->y = 0;
	player->vel = 1;
	player->rld = 0;
	player->rla = 0;
	player->udd = 0;
	player->rotateangle = M_PI / 2 ;
	player->rotatespeed = 1 * (M_PI / 180);
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
	all->rays = (t_rays *)malloc(sizeof(t_rays) * NUM_RAYS);
	if (all->rays == NULL)
		return(destroy_all(all), -1);
	return (0);
}

void	pixel_put(t_mlx *mlx, int x, int y, int color)
{
	if ((x >= 0 && x < WIN_WIDTH) && (y >= 0 && y < WIN_HEIGHT))
	{
		*((int *)&mlx->get_addr[(y * mlx->sl) + (x * mlx->bpp / 8)]) = color;
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
	(void)color;
	p = all->player;
	p->tile_height = WIN_HEIGHT / all->map->height;
	p->tile_width = WIN_WIDTH / all->map->width;
	x = i * p->tile_width;
	while (x < ((i * p->tile_width) + p->tile_width))
	{
		y = j * p->tile_height;
		while (y < ((j * p->tile_height) + p->tile_height))
		{
			// pixel_put(all->mlx, x, y, color);
			y++;
		}
		x++;
	}
}

void	render_rays(t_global *all, t_rays ray, double x, double y)
{
	int	dx;
	int	dy;
	double	ddx;
	double	ddy;
	double	x_inc;
	double	y_inc;
	int		step;

	(void)all;
	dx = (ray.xnext - x);
	dy = (ray.ynext - y);
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
		// pixel_put(all->mlx, dx, dy, 16711680);
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

double	distance_calcul(t_global *all, t_rays ray)
{
	double	ret;

	ret = sqrt((ray.xnext - all->player->pos_tilex) * (ray.xnext - all->player->pos_tilex)\
		 + (ray.ynext - all->player->pos_tiley) * (ray.ynext - all->player->pos_tiley));
	return (ret);
}

void	horiz_intersect(t_global *all, t_rays *ray)
{
	ray->distance_horiz = INT_MAX;
	ray->ynext = floor((all->player->pos_tiley / all->player->tile_height)) * all->player->tile_height;
	if (!ray->up)
		ray->ynext += all->player->tile_height;
	ray->xnext = all->player->pos_tilex - ((all->player->pos_tiley - ray->ynext) / tan(ray->rad));
	ray->ystep = all->player->tile_height;
	if (ray->up == true)
		ray->ystep *= -1;
	ray->xstep = all->player->tile_height / tan(ray->rad);
	if ((ray->right == true && ray->xstep < 0) || (ray->right == false && ray->xstep > 0))
		ray->xstep *= -1;
	if (ray->up == true)
		ray->ynext--;
	while (ray->xnext >= 0 && ray->xnext <= WIN_WIDTH && ray->ynext >= 0 && ray->ynext <= WIN_HEIGHT)
	{
		if (iswall(all, ray->xnext, ray->ynext) == 1)
		{
			if (ray->up == false)
				ray->ynext++;
			ray->horzx = ray->xnext;
			ray->horzy = ray->ynext;
			ray->distance_horiz = distance_calcul(all, *ray);
			break ;
		}
		ray->xnext += ray->xstep;
		ray->ynext += ray->ystep;
	}
}

void	vertic_intersect(t_global *all, t_rays *ray)
{
	ray->distance_vertic = INT_MAX;
	ray->xnext = floor((all->player->pos_tilex / all->player->tile_width)) * all->player->tile_width;
	if (ray->right == true)
		ray->xnext += all->player->tile_width;
	ray->ynext = all->player->pos_tiley - (tan(ray->rad) * (all->player->pos_tilex - ray->xnext));
	ray->xstep = all->player->tile_width;
	if (ray->right == false)
		ray->xstep *= -1;
	ray->ystep = all->player->tile_width * tan(ray->rad);
	if ((ray->up == true && ray->ystep > 0) || (ray->up == false && ray->ystep < 0))
		ray->ystep *= -1;
	if (ray->right == false)
		ray->xnext--;
	while (ray->xnext >= 0 && ray->xnext <= WIN_WIDTH && ray->ynext >= 0 && ray->ynext <= WIN_HEIGHT)
	{
		if (iswall(all, ray->xnext, ray->ynext) == 1)
		{
			if (ray->right == true)
				ray->xnext++;
			ray->vertx = ray->xnext;
			ray->verty = ray->ynext;
			ray->distance_vertic = distance_calcul(all, *ray);
			break ;
		}
		ray->xnext += ray->xstep;
		ray->ynext += ray->ystep;
	}
}

void	cast_render(t_global *all, t_rays *ray)
{
	horiz_intersect(all, ray);
	vertic_intersect(all, ray);
	if (ray->distance_horiz < ray->distance_vertic)
	{
		ray->ynext = ray->horzy;
		ray->xnext = ray->horzx;
		ray->dist_const = ray->distance_horiz;
	}
	if (ray->distance_horiz >= ray->distance_vertic)
	{
		ray->xnext = ray->vertx;
		ray->ynext = ray->verty;
		ray->dist_const = ray->distance_vertic;
	}
}

void	fill_ray(t_rays *ray, double deg)
{
	ray->rad = deg;
	ray->up = deg > M_PI && deg < (2 * M_PI);
	ray->right = (deg >= 0 && deg < (M_PI * 0.5)) || (deg > (1.5 * M_PI) && deg <= (2 * M_PI));
}

void	render_wall(t_global *all, int i, double wallheight)
{
	double	x;
	double	y;
	double	tmpx;
	double	tmpy;

	x = i * STRIP_WIDTH;
	tmpx = i * STRIP_WIDTH;
	tmpy = ((double)WIN_HEIGHT / 2) - (wallheight / 2);
	while (x < tmpx + STRIP_WIDTH)
	{
		y = tmpy;
		while (y < tmpy + wallheight)
		{
			pixel_put(all->mlx, x, y, 16777215);
			y++;
		}
		x++;
	}
}

void	render3Dwalls(t_global *all)
{
	double	dist_proj;
	double	wall_height;
	int		i;

	i = 0;
	dist_proj = (WIN_WIDTH / 2) / (tan(FOV_RAD / 2));
	while (i < NUM_RAYS)
	{
		wall_height = dist_proj * ((double)all->player->tile_height / all->rays[i].dist_const);
		render_wall(all, i, wall_height);
		i++;
	}
}

void	render_player(t_global *all, int i, int j)
{
	double		degree;
	int			count;
	t_player	*p;
	double		inc_deg;

	count = 0;
	p = all->player;
	p->tile_height = WIN_HEIGHT / all->map->height;
	p->tile_width = WIN_WIDTH / all->map->width;
	p->pos_tilex = p->x + (i * p->tile_width);
	p->pos_tiley = p->y + (j * p->tile_height);
	degree = (all->player->rotateangle - (FOV_RAD / 2));
	inc_deg = ((double)FOV / (double)NUM_RAYS);
	while (count < NUM_RAYS)
	{
		ft_normalize_angle(&degree);
		fill_ray(&all->rays[count], degree);
		cast_render(all, &all->rays[count]);
		degree += (inc_deg * (M_PI / 180));
		count++;
	}
	render3Dwalls(all);
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

	if (x < 0 || x > WIN_WIDTH || y < 0 || y > WIN_HEIGHT)
		return (1);
	gridx = floor((x / all->player->tile_width));
	gridy = floor((y / all->player->tile_height));
	if (gridy <= all->map->height && all->map->map[gridy] != NULL && all->map->map[gridy][gridx] == '1')
		return (1);
	return (0);
}

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

int	move_player(t_global *all)
{
	t_player	*p;
	t_mlx		*mlx_cpy;
	double		x;
	double		y;
	double		tmp_rotate;

	mlx_cpy = all->mlx;
	p = all->player;
	x = p->pos_tilex;
	y = p->pos_tiley;
	if (p->udd == 0 && p->rld == 0 && p->rla == 0)
		return (0);
	if (p->udd != 0)
	{
		y += ((double)(p->vel * p->udd) * sin(p->rotateangle));
		x += ((double)(p->vel * p->udd) * cos(p->rotateangle));
		if (iswall(all, x, y) == 0)
		{
			p->y = y - (p->pos_tiley - p->y);
			p->x = x - (p->pos_tilex - p->x);
		}
	}
	if (p->rld != 0)
	{
		x += sin(p->rotateangle) * (double)(p->rld * p->vel);
		y -= cos(p->rotateangle) * (double)(p->rld * p->vel);
		if (iswall(all, x, y) == 0)
		{
			p->y = y - (p->pos_tiley - p->y);
			p->x = x - (p->pos_tilex - p->x);
		}
	}
	tmp_rotate = p->rotateangle + (p->rotatespeed * p->rla);
	ft_normalize_angle(&tmp_rotate);
	p->rotateangle = tmp_rotate;
	mlx_destroy_image(mlx_cpy->mlx_ptr, mlx_cpy->image);
	mlx_clear_window(mlx_cpy->mlx_ptr, mlx_cpy->mlx_win);
	raycaster(all);
	return (0);
}

int	find_pos_p(t_global *all)
{
	t_map	*map;

	map = all->map;
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
					return (0);
			}
			all->l++;
		}
		all->a++;
	}
	return (-1);
}

int	raycaster(t_global *all)
{
	t_mlx	*mlx_cpy;

	mlx_cpy = all->mlx;
	mlx_cpy->image = mlx_new_image(mlx_cpy->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx_cpy->get_addr = mlx_get_data_addr(mlx_cpy->image, &(mlx_cpy->bpp), &(mlx_cpy->sl), &(mlx_cpy->ed));
	if (mlx_cpy->get_addr == NULL)
		return (destroy_all(all), -1);
	render_player(all, all->l, all->a);
	mlx_put_image_to_window(mlx_cpy->mlx_ptr, mlx_cpy->mlx_win, mlx_cpy->image, 0, 0);
	return (0);
}

void	mlx_render(t_global *all)
{
	if (set_mlx(all) == -1)
		exit(1);
	if (find_pos_p(all) == -1)
		exit(1);
	if (raycaster(all) == -1)
		exit(1);
}
