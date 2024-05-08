/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesnoye <ldesnoye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 00:30:44 by ldesnoye          #+#    #+#             */
/*   Updated: 2022/05/12 00:30:46 by ldesnoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	true_unset(t_list **env_list, char *name)
{
	t_list	*link;
	t_list	*prev;
	t_var	*cast;

	link = *env_list;
	prev = link;
	while (link)
	{
		cast = (t_var *)link->content;
		if (!ft_strncmp(cast->name, name, ft_strlen(name) + 1))
		{
			if (prev == link)
				*env_list = link->next;
			else
				prev->next = link->next;
			ft_lstdelone(link, free_var);
			return (0);
		}
		prev = link;
		link = link->next;
	}
	return (0);
}

int	ft_unset(t_box *box, t_cmd *cmd)
{
	int	i;
	int	ret;

	i = 1;
	ret = 0;
	while (cmd->args[i])
	{
		if (check_varname(cmd->args[i]))
			true_unset(box->env_list, cmd->args[i]);
		else
		{
			print_invalid("unset", cmd->args[i]);
			ret = 1;
		}
		i++;
	}
	return (ret);
}
