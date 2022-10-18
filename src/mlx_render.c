/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 13:24:41 by hmoubal           #+#    #+#             */
/*   Updated: 2022/10/17 23:48:45 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

int	set_mlx(t_global *all)
{
	t_mlx	*mlx_cpy;
	t_map	*map_cpy;

	map_cpy = all->map;
	all->mlx = (t_mlx *)malloc(sizeof(t_mlx) * 1);
	if (all->mlx == NULL)
		return (destroy_all(all), -1);
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

void	render_block(t_global *all, int i, int j, int color)
{
	int		x;
	int		y;
	t_mlx	*mlx;

	mlx = all->mlx;
	x = i * TILE_SIZE;
	while (x < ((i * TILE_SIZE) + TILE_SIZE))
	{
		y = j * TILE_SIZE;
		while (y < ((j * TILE_SIZE) + TILE_SIZE))
		{
			pixel_put(mlx, x, y, color);
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

int	render_map(t_global *all)
{
	int	color;

	all->a = 0;
	color = 16711680;
	while (all->a < all->map->height)
	{
		all->l = 0;
		while (all->l < all->map->width)
		{
			if (all->map->map[all->a][all->l] != ' ')
			{
				if (all->map->map[all->a][all->l] == '1')
					render_block(all, all->a, all->l, 8421504);
				if (all->map->map[all->a][all->l] == '0')
					render_block(all, all->a, all->l, 65280);
				if (all->map->map[all->a][all->l] == 'N')
					render_block(all, all->a, all->l, color);
			}
			all->l++;
		}
		all->a++;
	}
	mlx_put_image_to_window(all->mlx->mlx_ptr, all->mlx->mlx_win, all->mlx->image, 0, 0);
	mlx_destroy_image(all->mlx->mlx_ptr, all->mlx->image);
	mlx_hook(all->mlx->mlx_win, 17, 0, ft_close, all);
	mlx_loop(all->mlx->mlx_ptr);
	return (0);
}

void	mlx_render(t_global *all)
{
	if (set_mlx(all) == -1)
		exit(1);
	if (render_map(all) == -1)
		exit(1);
}
