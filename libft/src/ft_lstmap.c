/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmoubal <hmoubal@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 09:38:45 by hmoubal           #+#    #+#             */
/*   Updated: 2022/08/09 17:58:45 by hmoubal          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/libft.h"

t_list	*ft_lstmap(t_list *lst,	void *(*f)(void *),	void (*del)(void *))
{
	t_list	*p;
	t_list	*o;

	if (!lst || !f || !del)
		return (NULL);
	p = ft_lstnew(f(lst->content));
	if (!p)
	{
		ft_lstclear(&p, del);
		return (NULL);
	}
	lst = lst->next;
	o = p;
	while (lst != NULL)
	{
		p = ft_lstnew(f(lst->content));
		if (!p)
		{
			ft_lstclear(&o, del);
			return (NULL);
		}
		ft_lstadd_back(&o, p);
		lst = lst->next;
	}
	return (o);
}
