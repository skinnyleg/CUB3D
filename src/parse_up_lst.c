/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_up_lst.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: med-doba <med-doba@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/09/25 20:40:26 by med-doba          #+#    #+#             */
/*   Updated: 2022/09/25 23:08:26 by med-doba         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/CUB3D.h"

void	ft_free_2d(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
		free(ptr[i++]);
	free(ptr);
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
	node->repate = repate;
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
