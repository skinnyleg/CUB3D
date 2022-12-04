/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_upper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:47:58 by med-doba          #+#    #+#             */
/*   Updated: 2022/12/04 18:03:38 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

int	check_extension_up(char *str, char *extension)
{
	str++;
	while (*str != '\0' && *str != '.')
		str++;
	if (ft_strcmp(str, extension) != 0)
		return (printf("Error: Wrong extension\n"), 1);
	return (0);
}

int	parse_upper(char **av, t_global *all)
{
	char	*rtn_gnl;
	int		rtn;

	all->fd = open(av[1], O_RDONLY);
	if (all->fd == -1)
		return (perror("open"), 1);
	rtn_gnl = get_next_line(all->fd);
	while (rtn_gnl)
	{
		if (rtn_gnl != NULL && (int)ft_strlen(rtn_gnl) > all->a)
			all->a = ft_strlen(rtn_gnl);
		rtn = ft_rtn_gnl(rtn_gnl, all);
		if (rtn == 2)
			break ;
		if (rtn == 1)
			return (destroy_all(all), 1);
		rtn_gnl = get_next_line(all->fd);
	}
	if (!all->up || ((ft_lstsize_paraup(all->up) < 5
				|| ft_lstsize_paraup(all->up) > 5) || check_double(all->up)))
		return (ft_putendl_fd("Error map last", 2), destroy_all(all), 1);
	return (all->l = 1, 0);
}

int	ft_rtn_gnl(char *rtn_gnl, t_global *all)
{
	char	**ptr;

	rtn_gnl = ft_strtrim_free(rtn_gnl, " \t");
	if (*rtn_gnl != '\0')
	{
		ptr = ft_split(rtn_gnl, ' ');
		if (ft_check_ptr_0(ptr[0]) == 0)
		{
			if (ft_handle_line(ptr, all) == -1)
				return (ft_free_2d(ptr), free(rtn_gnl), 1);
		}
		else
			return (ft_free_2d(ptr), free(rtn_gnl), 2);
		ft_free_2d(ptr);
	}
	return (free(rtn_gnl), 0);
}

int	ft_handle_line(char	**ptr, t_global *all)
{
	t_paraup	*node;
	int			i;
	int			fd;

	i = 0;
	fd = 0;
	while (ptr[i])
		i++;
	if (i > 2 || i == 1)
		return (ft_putendl_fd("Error: map_1", 2), -1);
	if (ft_strcmp(ptr[0], "NO") == 0 || ft_strcmp(ptr[0], "SO") == 0
		|| ft_strcmp(ptr[0], "WE") == 0 || ft_strcmp(ptr[0], "EA") == 0)
	{
		if (check_extension_up(ptr[1], ".xpm") == 1)
			return (-1);
		fd = open(ptr[1], O_RDONLY);
		if (fd == -1)
			return (perror("path_to_texture"), -1);
		node = ft_lstnew_paraup(ptr[0], ptr[1]);
		if (node != NULL)
			return (ft_lstadd_back_paraup(&(all->up), node), close(fd), 0);
	}
	else if (ft_strcmp(ptr[0], "F") == 0 || ft_strcmp(ptr[0], "C") == 0)
	{
		if (ft_handle_c_f(ptr[1], 0) == -1)
			return (ft_putendl_fd("Error: map_2", 2), -1);
		node = ft_lstnew_paraup(ptr[0], ptr[1]);
		if (node != NULL)
			return (ft_lstadd_back_paraup(&(all->up), node), 0);
	}
	return (ft_putendl_fd("Error: map_3", 2), close(fd), -1);
}

int	ft_count_comma(char *ptr)
{
	int	i;
	int j;

	i = 0;
	j = 0;
	while (ptr[i])
	{
		if (ptr[i] == ',')
			j++;
		i++;
	}
	return (j);
}

int	ft_handle_c_f(char *ptr, int i)
{
	int		j;
	char	**tab;
	int		nbr;

	if (ft_count_comma(ptr) > 2)
		return (-1);
	tab = ft_split(ptr, ',');
	while (tab[i])
		i++;
	if (i > 3 || i < 3)
		return (ft_free_2d(tab), -1);
	i = 0;
	while (tab[i])
	{
		j = 0;
		while (tab[i][j])
			if (ft_isdigit(tab[i][j++]) == 0)
				return (ft_free_2d(tab), -1);
		nbr = ft_atoi(tab[i]);
		if (nbr >= 0 && nbr <= 255)
			i++;
		else
			return (ft_free_2d(tab), -1);
	}
	return (ft_free_2d(tab), 0);
}