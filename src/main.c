/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:17:40 by hmoubal           #+#    #+#             */
/*   Updated: 2022/11/02 22:42:04 by hmoubal          ###   ########.fr       */
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
	all->rays = NULL;
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
	mlx_render(&all);
	destroy_all(&all);
	return (0);
}
