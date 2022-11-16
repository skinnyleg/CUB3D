/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 15:52:33 by hmoubal           #+#    #+#             */
/*   Updated: 2022/11/16 20:23:23 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

void	pixel_put(t_mlx *mlx, int x, int y, int color)
{
	if ((x >= 0 && x < WIN_WIDTH) && (y >= 0 && y < WIN_HEIGHT))
	{
		*((int *)&mlx->get_addr[(y * mlx->sl) + (x * mlx->bpp / 8)]) = color;
	}
}

void	ft_normalize_angle(double *angle)
{
	*angle = fmod(*angle, (2 * M_PI));
	if (*angle < 0)
		*angle = (2 * M_PI) + *angle;
}

void	fill_ray(t_rays *ray, double deg)
{
	ray->rad = deg;
	ray->right = false;
	ray->up = false;
	if ((deg > M_PI) && (deg < (2 * M_PI)))
		ray->up = true;
	if (deg < (M_PI * 0.5) || deg > (1.5 * M_PI))
		ray->right = true;
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
	// p->tile_height = 32;
	// p->tile_width = 32;
	p->pos_tilex = p->x + (i * p->tile_width);
	p->pos_tiley = p->y + (j * p->tile_height);
	// pixel_put(all->mlx, p->pos_tilex, p->pos_tiley, 16711680);
	degree = (all->player->rotateangle - ((double)FOV * (M_PI / 180) / 2));
	inc_deg = ((double)FOV / (double)all->num_rays);
	while (count < all->num_rays)
	{
		ft_normalize_angle(&degree);
		fill_ray(&all->rays[count], degree);
		cast_render(all, &all->rays[count]);
		degree += (inc_deg * (M_PI / 180));
		count++;
	}
	render3dwalls(all);
}

void	render_minimap(t_global *all)
{
	int		i;
	int		j;
	t_map	*map;

	i = 0;
	map = all->map;
	while (map->map[i] != NULL)
	{
		j = 0;
		while (map->map[i][j] != '\0')
		{
			if (map->map[i][j] != ' ')
			{
				if (map->map[i][j] == '1')
					render_block(all, j, i, 8421504);
				else
					render_block(all, j, i, 65280);
				if (map->map[i][j] == '0')
					render_block(all, j, i, 65280);
			}
			j++;
		}
		i++;
	}
}

int	raycaster(t_global *all)
{
	t_mlx	*mlx_cpy;

	mlx_cpy = all->mlx;
	mlx_cpy->image = mlx_new_image(mlx_cpy->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	mlx_cpy->get_addr = mlx_get_data_addr(mlx_cpy->image, \
		&(mlx_cpy->bpp), &(mlx_cpy->sl), &(mlx_cpy->ed));
	if (mlx_cpy->get_addr == NULL)
		return (destroy_all(all), -1);
	// render_minimap(all);
	background_render(all);
	render_player(all, all->l, all->a);
	mlx_put_image_to_window(mlx_cpy->mlx_ptr, \
		mlx_cpy->mlx_win, mlx_cpy->image, 0, 0);
	return (0);
}
