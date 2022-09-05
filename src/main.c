/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/09 17:17:40 by hmoubal           #+#    #+#             */
/*   Updated: 2022/08/12 07:18:20 by hmoubal          ###   ########.fr       */
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

int	parse_upper(char	**av)
{
	int	fd;

	fd = open(av[2], O_RDONLY);
	if (fd < 0)
		return (printf("Can't open map\n"), 1);
	return (0);
}

void	parse_map(char	**av)
{
	if (check_extension(av) == 1)
		exit(1);
	if (parse_upper(av) == 1)
		exit(1);
}

int	main(int ac, char **av)
{
	if (ac != 2)
		return (printf("Not Enough Arguments\n"), 0);
	parse_map(av);
	return (0);
}
