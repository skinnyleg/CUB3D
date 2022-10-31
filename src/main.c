/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:17:40 by hmoubal           #+#    #+#             */
/*   Updated: 2022/10/31 14:09:44 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

int	check_extension(char *str, char *extension)
{
	size_t	length;
	int		i;

	length = 4;
	i = 0;
	while (str[i] != '\0' && str[i] != '.')
		i++;
	if (ft_strlen(&str[i]) > length)
		length = ft_strlen(&str[i]);
	if (ft_strncmp(&str[i], extension, length) != 0)
		return (printf("Wrong extension\n"), 1);
	return (0);
}

void	ft_init(t_global	*all)
{
	all->a = 0;
	all->l = 0;
	all->up = NULL;
	all->map = NULL;
	all->mlx = NULL;
	all->player = NULL;
}

void	parse_map(char	**av, t_global *all)
{
	ft_init(all);
	if (check_extension(av[1], ".cub") == 1)
		exit(1);
	if (parse_upper(av, all) == 1)
		exit(1);
	if (parse_lower(av, all) == 1)
		exit(1);
}
//med-doba
int	key_press(int keycode, t_param *param)
{
	if (keycode == )
	return (0);
}

int	main(int ac, char **av)
{
	t_global	all;
	void		*mlx;
	void		*mlx_win;
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;

	if (ac != 2)
		return (printf("Not Enough Arguments\n"), 0);
	parse_map(av, &all);
	mlx = mlx_init();
	mlx_win = mlx_new_window(mlx, 1920, 1080, "cub3D");
	img = mlx_new_image(mlx, 1920, 1080);
	addr = mlx_get_data_addr(img, &bits_per_pixel, &line_length, &endian);
	mlx_pixel_put(mlx, mlx_win, 5, 5, 0x00FF0000);
	mlx_put_image_to_window(mlx, mlx_win, img, 0, 0);
	mlx_hook(mlx_win, int x_event, int x_mask, int (*funct)(), void *param);
	mlx_loop(mlx);
	destroy_all(&all);
	return (0);
}
