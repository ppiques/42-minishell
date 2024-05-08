/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_extractor_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesnoye <ldesnoye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 20:25:49 by ldesnoye          #+#    #+#             */
/*   Updated: 2022/05/05 20:25:52 by ldesnoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	add_text(t_cmd *cmd, int i, int j, int space)
{
	int		len;
	char	*new;

	if (space)
		len = skip_space(cmd, i);
	else
		len = skip_text(cmd, i);
	new = ft_substr(cmd->data, i, len);
	if (!new)
		return (-1);
	cmd->extracted[j] = new;
	cmd->extracted[j + 1] = 0;
	return (len);
}

int	add_dollar(t_cmd *cmd, int i, int j, t_box *box)
{
	char	*name;
	char	*stock_value;
	char	*value;

	name = extract_varname(cmd->data + i);
	if (!name)
		return (-1);
	stock_value = get_value(box->env_list, name);
	value = ft_strdup(stock_value);
	free(name);
	if (!value)
		return (-1);
	cmd->extracted[j] = value;
	cmd->extracted[j + 1] = 0;
	return (skip_dollar(cmd, i));
}

static int	quote_loop(t_cmd *cmd, t_box *box, int j)
{
	int	k;
	int	stock;

	k = 0;
	if (cmd->extracted[j])
	{
		while (cmd->extracted[j][k])
		{
			if (cmd->extracted[j][k] == '$')
				stock = replace_var(cmd->extracted[j], k, box->env_list, \
				&cmd->extracted[j]);
			else
				stock = 1;
			if (stock == -1)
				return (-1);
			k += stock;
		}
	}
	return (0);
}

int	add_quote(t_cmd *cmd, int i, int j, t_box *box)
{
	char	quote;
	char	*str;
	int		result;

	quote = cmd->data[i];
	result = skip_quote(cmd, i);
	str = ft_substr(cmd->data, i, result);
	if (!str)
		return (-1);
	cmd->extracted[j] = str;
	cmd->extracted[j + 1] = 0;
	if (quote == '"')
	{
		if (quote_loop(cmd, box, j) == -1)
			return (-1);
	}
	return (result);
}
