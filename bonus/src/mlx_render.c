/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_render.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 15:42:30 by hmoubal           #+#    #+#             */
/*   Updated: 2022/12/04 20:07:20 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

double	distance_calcul(t_global *all, t_rays ray)
{
	double	ret;

	ret = sqrt ((ray.xnext - all->player->pos_tilex) \
		* (ray.xnext - all->player->pos_tilex) \
		+ (ray.ynext - all->player->pos_tiley) \
		* (ray.ynext - all->player->pos_tiley));
	return (ret);
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
			if (map->map[all->a][all->l] == 'N'\
					|| map->map[all->a][all->l] == 'E'\
					|| map->map[all->a][all->l] == 'W'\
					|| map->map[all->a][all->l] == 'S')
				return (ft_direction_player(all, map->map[all->a][all->l]), 0);
			all->l++;
		}
		all->a++;
	}
	return (destroy_all(all), -1);
}

void	init_player(t_player *player)
{
	player->x = 0;
	player->y = 0;
	player->vel = 5;
	player->rld = 0;
	player->rla = 0;
	player->udd = 0;
	player->rotateangle = M_PI / 2 ;
	player->rotatespeed = 2 * (M_PI / 180);
}

int	set_mlx(t_global *all)
{
	t_mlx	*mlx_cpy;

	all->mlx = (t_mlx *)malloc(sizeof(t_mlx) * 1);
	if (all->mlx == NULL)
		return (ft_putendl_fd("Error", 2), destroy_all(all), -1);
	all->mlx->mlx_ptr = NULL;
	all->mlx->image = NULL;
	all->mlx->mlx_win = NULL;
	all->player = (t_player *)malloc(sizeof(t_player) * 1);
	if (all->player == NULL)
		return (ft_putendl_fd("Error", 2), destroy_all(all), -1);
	init_player(all->player);
	mlx_cpy = all->mlx;
	mlx_cpy->mlx_ptr = mlx_init();
	if (mlx_cpy->mlx_ptr == NULL)
		return (ft_putendl_fd("Error", 2), destroy_all(all), -1);
	mlx_cpy->mlx_win = mlx_new_window(mlx_cpy->mlx_ptr, \
		WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	all->num_rays = (WIN_WIDTH / STRIP_WIDTH);
	all->rays = (t_rays *)malloc(sizeof(t_rays) * all->num_rays);
	if (all->rays == NULL)
		return (ft_putendl_fd("Error", 2), destroy_all(all), -1);
	return (0);
}

void	mlx_render(t_global *all)
{
	if (set_mlx(all) == -1)
		exit(1);
	if (find_pos_p(all) == -1)
		exit(1);
	if (set_textures(all) == -1)
		exit(1);
	if (raycaster(all) == -1)
		exit(1);
}
