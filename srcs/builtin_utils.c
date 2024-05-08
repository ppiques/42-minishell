/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesnoye <ldesnoye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/11 16:35:00 by ldesnoye          #+#    #+#             */
/*   Updated: 2022/05/12 00:38:44 by ldesnoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_var_export(void *var)
{
	t_var	*cast;
	char	*name;

	cast = (t_var *)var;
	name = cast->name;
	if (!name || !ft_strncmp("?", name, 2) || !ft_strncmp("", name, 1))
		return ;
	ft_putstr_fd("declare -x ", 1);
	ft_putstr_fd(cast->name, 1);
	ft_putstr_fd("=", 1);
	ft_putendl_fd(cast->value, 1);
}

int	print_invalid(char *cmd_name, char *arg)
{
	ft_putstr_fd("Debash: ", 2);
	ft_putstr_fd(cmd_name, 2);
	ft_putstr_fd(": `", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd("\': not a valid identifier\n", 2);
	return (1);
}

char	*ft_concat(char *ref, char *val)
{
	char	*new;

	new = malloc((ft_strlen(ref) + ft_strlen(val) + 1) * sizeof(char));
	if (!new)
		return (NULL);
	ft_strlcpy(new, ref, ft_strlen(ref) + 1);
	ft_strlcpy(new + ft_strlen(ref), val, ft_strlen(val) + 1);
	return (new);
}

t_var	*get_envvar(t_list **list, char *name)
{
	t_list	*link;
	t_var	*var;

	link = *list;
	while (link)
	{
		var = (t_var *)link->content;
		if (var->name)
		{
			if (!ft_strncmp(name, var->name, ft_strlen(var->name) + 1))
				return (var);
		}
		link = link->next;
	}
	return (var);
}

int	add_front_var(char *name, char *value, t_list **list)
{
	t_var	*var;
	t_list	*link;

	var = create_var(name, value);
	if (!var)
	{
		free(name);
		free(value);
		ft_putstr_fd("Debash: memory allocation error\n", 2);
		return (1);
	}
	link = ft_lstnew(var);
	if (!link)
	{
		free_var(var);
		ft_putstr_fd("Debash: memory allocation error\n", 2);
		return (1);
	}
	ft_lstadd_front(list, link);
	return (0);
}
