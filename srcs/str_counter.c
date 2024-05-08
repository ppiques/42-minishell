/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_counter.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiques <ppiques@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:05:39 by ppiques           #+#    #+#             */
/*   Updated: 2022/04/27 18:53:47 by ppiques          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// skips the chars until you leave the quotes
int	skip_quote(t_cmd *cmd, int i)
{
	char	quote;
	int		len;

	len = 1;
	quote = cmd->data[i];
	while (cmd->data[i + len] && cmd->data[i + len] != quote)
		len++;
	quote = 0;
	if (cmd->data[i + len])
		len++;
	return (len);
}

// skips the chars until you leave the variable
int	skip_dollar(t_cmd *cmd, int i)
{
	int	len;

	len = 1;
	while (is_varchar(cmd->data[i + len]))
		len++;
	if (len == 1 && cmd->data[i + 1] == '?')
		return (2);
	return (len);
}

// skips the chars until you find a var, a quote, or end of string
int	skip_text(t_cmd *cmd, int i)
{
	int	len;

	len = 0;
	while (cmd->data[i + len] && !ft_isquote(cmd->data[i + len]) && \
	cmd->data[i + len] != '$' && !ft_isspace(cmd->data[i + len]))
		len++;
	return (len);
}

// skips the spaces
int	skip_space(t_cmd *cmd, int i)
{
	int	len;

	len = 0;
	while (ft_isspace(cmd->data[i + len]))
		len++;
	return (len);
}

// Count the different strings needed
int	str_counter(t_cmd *cmd)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (cmd->data[i])
	{
		if (cmd->data[i])
			count++;
		if (ft_isquote(cmd->data[i]))
			i += skip_quote(cmd, i);
		else if (cmd->data[i] == '$')
			i += skip_dollar(cmd, i);
		else if (ft_isspace(cmd->data[i]))
			i += skip_space(cmd, i);
		else if (cmd->data[i])
			i += skip_text(cmd, i);
	}
	cmd->str_count = count;
	return (0);
}
