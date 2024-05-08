/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstmap.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesnoye <ldesnoye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:29:13 by ldesnoye          #+#    #+#             */
/*   Updated: 2021/11/29 18:29:13 by ldesnoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	delafter(t_list *lst, void (*del)(void *))
{
	if (!lst->next)
		ft_lstdelone(lst, del);
	else
	{
		delafter(lst->next, del);
		ft_lstdelone(lst, del);
	}
}

static t_list	*safenew(void *content, void *(*f)(void *),
				t_list *next, void (*del)(void *))
{
	t_list	*new;

	new = malloc(sizeof(t_list));
	if (!new)
	{
		delafter(next, del);
		return (NULL);
	}
	new->next = next;
	new->content = f(content);
	return (new);
}

t_list	*ft_lstmap(t_list *lst, void *(*f)(void *), void (*del)(void *))
{
	t_list	*stock;

	if (!lst->next)
		return (safenew(lst->content, f, 0, del));
	else
	{
		stock = ft_lstmap(lst->next, f, del);
		if (!stock)
			return (NULL);
		return (safenew(lst->content, f, stock, del));
	}
}
