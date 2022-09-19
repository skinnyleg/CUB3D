/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:17:40 by hmoubal           #+#    #+#             */
/*   Updated: 2022/09/18 17:04:49 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

int	check_extension(char **av)
{
	size_t	length;
	int		i;

	length = 4;
	i = 0;
	while (av[1][i] != '\0' && av[1][i] != '.')
		i++;
	if (ft_strlen(&av[1][i]) > length)
		length = ft_strlen(&av[1][i]);
	if (ft_strncmp(&av[1][i], ".cub", length) != 0)
		return (printf("Wrong extension\n"), 1);
	return (0);
}

void	parse_map(char	**av, t_global *all)
{

	if (check_extension(av) == 1)
		exit(1);
	if (parse_upper(av, all) == 1)
		exit(1);
	if (parse_map_walls(av, all) == 1)
		exit(1);
}

int	main(int ac, char **av)
{
	t_global	all;

	if (ac != 2)
		return (printf("Not Enough Arguments\n"), 0);
	parse_map(av, &all);
	return (0);
}
