/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_upper.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/16 18:47:58 by med-doba          #+#    #+#             */
/*   Updated: 2022/09/16 19:20:30 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

int	parse_upper(char	**av, t_global *all)
{
	int		fd;
	char	rtn_gnl;
	char	**ptr;

	(void)all;
	if ((fd = open(av[1], O_RDONLY)) == -1)
		return (perror("fd"), 1);
	rtn_gnl = get_next_line(fd);
	while(rtn_gnl)
	{
		ptr = ft_split(rtn_gnl, ' ');

		rtn_gnl = get_next_line(fd);
	}
	close(fd);
	return (0);
}

int	ft_handle_line(char	**ptr)
{
	int	i;
	int	j;

	i = -1;
	while (ptr[++i])
		if (i == 2)
			return (-1);
	j = 0;
	while (ptr[i][j])
	{
		j++;
	}
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

t_paraup	*ft_lstnew_env(char *name, char *value)
{
	t_paraup	*node;

	node = (t_paraup *)malloc(sizeof(t_paraup));
	if (node == NULL)
		return (NULL);
	node->dir = ft_strdup(name);
	if (value)
		node->value = ft_strdup(value);
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
