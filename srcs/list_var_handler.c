/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_var_handler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiques <ppiques@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 02:38:37 by ppiques           #+#    #+#             */
/*   Updated: 2022/05/01 05:55:09 by ppiques          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_ambiguous(char *s, t_box *box)
{
	char	*varname;
	t_list	*link;
	t_var	*c;

	varname = extract_varname(s);
	if (!varname)
		return (-1);
	link = *box->env_list;
	while (link)
	{
		c = (t_var *)link->content;
		if (ft_strncmp(varname, c->name, ft_strlen(varname) + 1))
		{
			free(varname);
			return (left_ambiguous(c->value) || right_ambiguous(c->value));
		}
		link = link->next;
	}
	free(varname);
	return (0);
}

int	full_replace(char **s, t_box *box, int i, char quote)
{
	int		ret;

	while ((*s)[i])
	{
		if (ft_isquote((*s)[i]) && (!quote || quote == (*s)[i]))
		{
			quote = !quote * (*s)[i];
			if (ft_delete(s, i))
				return (-1);
		}
		else if ((*s)[i] == '$' && quote != '\'')
		{
			ret = is_ambiguous(*s + i, box);
			if (ret)
				return (ret);
			ret = replace_var(*s, i, box->env_list, s);
			if (ret == -1)
				return (ret);
			i = ret;
		}
		else
			i++;
	}
	return (0);
}

int	list_var_expander(t_list **list, t_box *box)
{
	t_list	*link;
	t_redir	*cast;
	int		i;

	link = *list;
	while (link)
	{
		cast = (t_redir *)link->content;
		if (cast->type != redir_heredoc)
		{
			i = full_replace(&(cast->data), box, 0, 0);
			if (i == 1)
			{
				ft_putstr_fd("Debash: ", 2);
				ft_putstr_fd(cast->data, 2);
				ft_putstr_fd(": ambiguous redirect\n", 2);
				return (1);
			}
			else if (i == -1)
				return (-1);
		}
		link = link->next;
	}
	return (0);
}

int	cmd_redir_expander(t_box *box)
{
	int	i;

	i = 0;
	while (box->line[i])
	{
		if (list_var_expander(box->line[i]->redir_list, box))
			return (-1);
		i++;
	}
	return (0);
}
