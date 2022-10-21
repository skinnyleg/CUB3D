/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:24:41 by hmoubal           #+#    #+#             */
/*   Updated: 2022/10/18 17:31:41by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

void	init_player(t_player *player)
{
	player->x = 0;
	player->y = 0;
	player->xvel = 2;
	player->yvel = 2;
	player->RLD = 0;
	player->UDD = 0;
}

int	set_mlx(t_global *all)
{
	t_mlx	*mlx_cpy;
	t_map	*map_cpy;

	map_cpy = all->map;
	all->mlx = (t_mlx *)malloc(sizeof(t_mlx) * 1);
	if (all->mlx == NULL)
		return (destroy_all(all), -1);
	all->player = (t_player *)malloc(sizeof(t_player) * 1);
	if (all->player == NULL)
		return (destroy_all(all), -1);
	init_player(all->player);
	mlx_cpy = all->mlx;
	all->mlx->mlx_ptr = mlx_init();
	if (all->mlx->mlx_ptr == NULL)
		return (destroy_all(all), -1);
	mlx_cpy->mlx_win = mlx_new_window(mlx_cpy->mlx_ptr, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	mlx_cpy->image = mlx_new_image(all->mlx->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx_cpy->get_addr = mlx_get_data_addr(mlx_cpy->image, &(mlx_cpy->bits_per_pixel), &(mlx_cpy->size_line), &(mlx_cpy->endian));
	if (mlx_cpy->get_addr == NULL)
		return (destroy_all(all), -1);
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

void	aspect_ratio(t_global *all , int *tile_width, int *tile_height)
{
	double resizewidth = all->map->width;
	double resizeheight = all->map->height;
	double aspect = resizewidth / resizeheight;
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
	*tile_width = (resizewidth / all->map->width) + 4;
	*tile_height = (resizeheight / all->map->height) + 4;
}

void	render_block(t_global *all, int i, int j, int color)
{
	int		x;
	int		y;
	int		tile_width;
	int		tile_height;

	aspect_ratio(all, &tile_width, &tile_height);
	x = i * tile_width;
	while (x < ((i * tile_width) + tile_width))
	{
		y = j * tile_height;
		while (y < ((j * tile_height) + tile_height))
		{
			pixel_put(all->mlx, x, y, color);
			y++;
		}
		x++;
	}
}

void	render_player(t_global *all, int i, int j, int color)
{
	int			tile_width;
	int			tile_height;
	int			x;
	int			y;

	x = all->player->x;
	y = all->player->y;
	aspect_ratio(all, &tile_width, &tile_height);
	x += i * tile_width;
	while (x < ((i * tile_width) + tile_width))
	{
		y += j * tile_height;
		while (y < ((j * tile_height) + tile_height))
		{
			pixel_put(all->mlx, x, y, color);
			y++;
		}
		x++;
	}
}

int	ft_close(t_global *all)
{
	destroy_all(all);
	exit(0);
	return (0);
}

// int	ft_keystroke

int	render_minimap(t_global *all)
{
	int		color;
	t_map	*map;

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
					render_player(all, all->l, all->a, 16711680);
			}
			all->l++;
		}
		all->a++;
	}
	mlx_put_image_to_window(all->mlx->mlx_ptr, all->mlx->mlx_win, all->mlx->image, 0, 0);
	mlx_destroy_image(all->mlx->mlx_ptr, all->mlx->image);
	mlx_hook(all->mlx->mlx_win, 17, 0, ft_close, all);
	// mlx_key_hook(all->mlx->mlx_win, ft_keystroke, all);
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
