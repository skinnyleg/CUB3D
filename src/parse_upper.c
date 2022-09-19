/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_upper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:47:58 by med-doba          #+#    #+#             */
/*   Updated: 2022/09/19 19:24:12 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"
#include <stdio.h>
#include <stdlib.h>

int	parse_upper(char **av, t_global *all)
{
	char	*rtn_gnl;
	char	**ptr;

	if ((all->fd = open(av[1], O_RDONLY)) == -1)
		return (perror("fd"), 1);
	all->up = NULL;
	rtn_gnl = get_next_line(all->fd);
	while(rtn_gnl)
	{
		rtn_gnl = ft_strtrim_free(rtn_gnl, " ");
		if (*rtn_gnl != '\0')
		{
			ptr = ft_split(rtn_gnl, ' ');
			if (ft_check_ptr_0(ptr[0]) == 0)
			{
				if (ft_handle_line(ptr, all) == -1)
					return (ft_free_2d(ptr), free(rtn_gnl), 1);
			}
			else
				break ;
			ft_free_2d(ptr);
		}
		free(rtn_gnl);
		rtn_gnl = get_next_line(all->fd);
	}
	if (all->up && ((ft_lstsize_paraup(all->up) < 5
		|| ft_lstsize_paraup(all->up) > 5) || check_double(all->up)))
		return (ft_putendl_fd("Error map", 2), 1);
	return (0);
}

int ft_check_ptr_0(char *ptr0)
{
	if (ft_strcmp(ptr0, "NO") == 0 || ft_strcmp(ptr0, "SO") == 0
		|| ft_strcmp(ptr0, "WE") == 0 || ft_strcmp(ptr0, "EA") == 0
		|| ft_strcmp(ptr0, "F") == 0 || ft_strcmp(ptr0, "C") == 0)
		return (0);
	return (-1);
}

int	ft_handle_line(char	**ptr, t_global *all)
{
	t_paraup 	*node;
	int			i;

	i = -1;
	while (ptr[++i]);
	if (i > 2 || i == 1)
		return (ft_putendl_fd("Error map", 2), -1);
	if (ft_strcmp(ptr[0], "NO") == 0 || ft_strcmp(ptr[0], "SO") == 0
		|| ft_strcmp(ptr[0], "WE") == 0 || ft_strcmp(ptr[0], "EA") == 0)
	{
		if (open(ptr[1], O_RDONLY) == -1)
			return (perror("path_to_texture"), -1);
		node = ft_lstnew_paraup(ptr[0], ptr[1], 1);
		return (ft_lstadd_back_paraup(&(all->up), node), 0);
	}
	else if (ft_strcmp(ptr[0], "F") == 0 || ft_strcmp(ptr[0], "C") == 0)
	{
		if (ft_handle_c_f(ptr[1]) == -1)
			return (ft_putendl_fd("Error map", 2), -1);
		node = ft_lstnew_paraup(ptr[0], ptr[1], 1);
		return (ft_lstadd_back_paraup(&(all->up), node), 0);
	}
	return (ft_putendl_fd("Error map000", 2), -1);
}

int	ft_handle_c_f(char *ptr)
{
	int		i;
	int		j;
	char	**tab;
	int		nbr;

	i = -1;
	tab = ft_split(ptr, ',');
	while (tab[++i]);
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

int	ft_lstsize_paraup(t_paraup *lst)
{
	int	i;

	i = 0;
	while (lst->next != NULL)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

void	ft_lstadd_back_paraup(t_paraup **lst, t_paraup *new)
{
	t_paraup	*tmp;

	if (lst == NULL || *lst == NULL)
	{
		*lst = new;
		new->next = NULL;
		return ;
	}
	tmp = *lst;
	while ((*lst)->next != NULL)
		*lst = (*lst)->next;
	(*lst)->next = new;
	new->next = NULL;
	*lst = tmp;
}

t_paraup	*ft_lstnew_paraup(char *name, char *value, int repate)
{
	t_paraup	*node;

	node = (t_paraup *)malloc(sizeof(t_paraup));
	if (node == NULL)
		return (NULL);
	node->dir = ft_strdup(name);
	if (value)
		node->value = ft_strdup(value);
	node->repate =repate;
	node->next = NULL;
	return (node);
}

void	ft_free_lst_paraup(t_paraup **head)
{
	t_paraup		*tmp;

	while ((*head))
	{
		free((*head)->value);
		free((*head)->dir);
		tmp = (*head)->next;
		free((*head));
		(*head) = tmp;
	}
}

char	*ft_strtrim_free(char const *s1, char const *set)
{
	int		j;
	int		i;
	char	*hub;

	if (!s1 || !set)
		return (NULL);
	j = 0;
	i = 0;
	while (ft_strchr(set, s1[i]) && s1[i] != '\0')
		i++;
	if (s1[i] == '\0')
	{
		hub = ft_strdup("\0");
		return (free((void *)s1), hub);
	}
	j = ft_strlen(s1);
	while (j != 0 && ft_strchr(set, s1[j - 1]))
		j--;
	hub = malloc(sizeof(char) * (j - i + 1));
	if (hub == NULL)
		return (NULL);
	ft_memcpy (hub, s1 + i, j);
	hub[j] = '\0';
	free((void *)s1);
	return (hub);
}

void	ft_free_2d(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
}

int	check_double(t_paraup *up)
{
	t_paraup *top;
	t_paraup *tmp;
	int		i;

	top = up;
	tmp = up;
	while (top)
	{
		i = 0;
		while (tmp)
		{
			if (ft_strcmp(tmp->dir, top->dir) == 0)
			{
				i++;
				if (i > 1)
					return (1);
			}
			tmp = tmp->next;
		}
		tmp = up;
		top = top->next;
	}
	return (0);
}
