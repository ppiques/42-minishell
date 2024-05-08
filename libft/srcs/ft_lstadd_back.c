/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lstadd_back.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesnoye <ldesnoye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:29:13 by ldesnoye          #+#    #+#             */
/*   Updated: 2021/11/29 18:29:13 by ldesnoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	add_last(t_list *lst, t_list *new)
{
	if (!lst->next)
		lst->next = new;
	else
		add_last(lst->next, new);
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	if (alst)
	{
		if (*alst)
			add_last(*alst, new);
		else
			*alst = new;
	}
}
