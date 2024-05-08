/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiques <ppiques@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/05 14:35:01 by ldesnoye          #+#    #+#             */
/*   Updated: 2022/04/27 20:08:33 by ppiques          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Searches for the variable with name *name in the list, and returns its value
// THE STR RETURNED MUST NOT BE FREED
char	*get_value(t_list **list, char *name)
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
				return (var->value);
		}
		link = link->next;
	}
	return (var->value);
}

// "$testing 123" -> return "testing" (must be freed)
char	*extract_varname(char *s)
{
	int		i;
	char	*name;

	i = 1;
	while (is_varchar(s[i]))
		i++;
	if (i == 1 && s[i] == '?')
		i++;
	name = malloc(i * sizeof(char));
	if (!name)
		return (NULL);
	if (s[1] == '?')
	{
		name[0] = '?';
		name[1] = 0;
		return (name);
	}
	i = 1;
	while (is_varchar(s[i]))
	{
		name[i - 1] = s[i];
		i++;
	}
	name[i - 1] = 0;
	return (name);
}

static int	free_varname(char *varname)
{
	free(varname);
	return (-1);
}

// In str *base, replaces variable at position start with its value
// start must be the position of the $.
// replace_var("test $cc pouic", 5, box) where $cc=42 returns "test 42 pouic"
int	replace_var(char *base, int start, t_list **env_list, char **addr)
{
	char	*varname;
	int		baselen;
	char	*var;
	char	*new;
	int		varlen;

	varname = extract_varname(base + start);
	if (!varname)
		return (-1);
	baselen = ft_strlen(base);
	var = get_value(env_list, varname);
	varlen = ft_strlen(varname);
	new = malloc((baselen - varlen + ft_strlen(var)) * sizeof(char));
	if (!new)
		return (free_varname(varname));
	ft_strlcpy(new, base, start + 1);
	if (var)
		ft_strlcpy(new + start, var, ft_strlen(var) + 1);
	ft_strlcpy(new + start + ft_strlen(var), base + start + varlen + 1, \
baselen - start - varlen);
	free(varname);
	free(base);
	*addr = new;
	return (start + ft_strlen(var));
}

// returns 1 if s is a correct variable name
// (alnum or _ that doesnt start with a number)
// and 0 otherwise.
int	check_varname(char *s)
{
	int	i;

	i = 0;
	if (!ft_isalpha(s[i]) && s[i] != '_')
		return (0);
	else
	{
		while (s[i])
		{
			if (!is_varchar(s[i]))
				return (0);
			i++;
		}
		return (1);
	}
}
