/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiques <ppiques@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/23 21:37:02 by ldesnoye          #+#    #+#             */
/*   Updated: 2022/04/27 20:07:25 by ppiques          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Initialize 1 variable
t_var	*create_var(char *name, char *value)
{
	t_var	*var;

	var = malloc(sizeof(t_var));
	if (!var)
		return (NULL);
	var->name = name;
	var->value = value;
	return (var);
}

// Adds var from str of format "name=value" to t_var list
int	add_envvar(const char *s, t_list **list)
{
	char	*name;
	char	*value;
	int		equals;
	t_var	*new_var;
	t_list	*link;

	equals = ind_equal(s);
	name = ft_substr(s, 0, equals);
	value = ft_strdup(s + equals + 1);
	if (!name || !value)
		return (magical_free(name, value, NULL));
	new_var = create_var(name, value);
	if (!new_var)
		return (magical_free(name, value, NULL));
	link = ft_lstnew(new_var);
	if (!link)
	{
		free_var(new_var);
		return (magical_free(name, value, NULL));
	}
	ft_lstadd_back(list, link);
	return (0);
}

int	add_var(char *name, char *value, t_list **list)
{
	t_var	*var;
	t_list	*link;

	var = create_var(name, value);
	if (!var)
	{
		free(name);
		free(value);
		return (-1);
	}
	link = ft_lstnew(var);
	if (!link)
	{
		free_var(var);
		return (-1);
	}
	ft_lstadd_back(list, link);
	return (0);
}

int	add_special_vars(t_list **list)
{
	char	*value;
	char	*name;

	name = ft_strdup("");
	value = ft_strdup("$");
	if (!name || !value)
		return (magical_free(name, value, list));
	if (add_var(name, value, list))
		return (magical_free(NULL, NULL, list));
	name = ft_strdup("?");
	value = ft_strdup("0");
	if (!name || !value)
		return (magical_free(name, value, list));
	if (add_var(name, value, list))
		return (magical_free(NULL, NULL, list));
	value = ft_strdup("");
	if (!value)
		return (magical_free(NULL, NULL, list));
	if (add_var(NULL, value, list))
		return (magical_free(NULL, value, list));
	return (0);
}

// Creates envp list with the env variables values
int	create_envp_list(const char **envp, t_box *box)
{
	t_list	**list;
	int		i;

	list = malloc(sizeof(t_list *));
	box->env_list = list;
	if (!list)
		return (-1);
	*list = NULL;
	i = 0;
	while (envp[i])
	{
		if (add_envvar(envp[i++], list))
			return (magical_free(NULL, NULL, list));
	}
	if (add_special_vars(list))
		return (magical_free(NULL, NULL, list));
	return (0);
}
