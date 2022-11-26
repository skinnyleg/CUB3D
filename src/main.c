/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:17:40 by hmoubal           #+#    #+#             */
/*   Updated: 2022/11/26 16:45:14 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"
// #include <X11/Xlib.h>

int	ft_close(t_global *all)
{
	destroy_all(all);
	exit(0);
	return (0);
}

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

int	main(int ac, char **av)
{
	t_global	all;

	if (ac != 2)
		return (printf("Not Enough Arguments\n"), 0);
	parse_map(av, &all);
	ft_mlx(&all);
	mlx_hook(all.mlx->mlx_win, 17, 0, ft_close, &all);
	mlx_hook(all.mlx->mlx_win, 2, (1L << 0), ft_KeyPress, &all);
	mlx_hook(all.mlx->mlx_win, 3, (1L << 1), ft_KeyRelease, &all);
	mlx_hook(all.mlx->mlx_win, 6, (1L << 6), ft_mouse_hook, &all);
	mlx_mouse_hook(all.mlx->mlx_win, ft_mouse_hook, &all);
	mlx_loop_hook(all.mlx->mlx_ptr, key_hook, &all);
	mlx_loop(all.mlx->mlx_ptr);
	destroy_all(&all);
	return (0);
}
