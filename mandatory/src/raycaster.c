/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 15:52:33 by hmoubal           #+#    #+#             */
/*   Updated: 2022/12/04 20:07:04 by hmoubal          ###   ########.fr       */
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
	p->pos_tilex = p->x + ((i * p->tile_width) + p->tile_width / 2);
	p->pos_tiley = p->y + ((j * p->tile_height) + p->tile_height / 2);
	degree = (all->player->rotateangle - (((double)FOV * (M_PI / 180)) / 2));
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

int	raycaster(t_global *all)
{
	t_mlx	*mlx_cpy;

	mlx_cpy = all->mlx;
	mlx_cpy->image = mlx_new_image(mlx_cpy->mlx_ptr, WIN_WIDTH, WIN_HEIGHT);
	if (mlx_cpy->image == NULL)
		return (destroy_all(all), -1);
	mlx_cpy->get_addr = mlx_get_data_addr(mlx_cpy->image, \
		&(mlx_cpy->bpp), &(mlx_cpy->sl), &(mlx_cpy->ed));
	if (mlx_cpy->get_addr == NULL)
		return (destroy_all(all), -1);
	background_render(all);
	render_player(all, all->l, all->a);
	mlx_put_image_to_window(mlx_cpy->mlx_ptr, \
		mlx_cpy->mlx_win, mlx_cpy->image, 0, 0);
	return (0);
}
