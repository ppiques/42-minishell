/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_extractor.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiques <ppiques@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 17:34:04 by ppiques           #+#    #+#             */
/*   Updated: 2022/04/30 15:15:03 by ppiques          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	calc_result(t_cmd *cmd, int i, int j, t_box *box)
{
	int	result;

	result = -1;
	if (ft_isquote(cmd->data[i]))
		result = add_quote(cmd, i, j - 1, box);
	else if (cmd->data[i] == '$')
		result = add_dollar(cmd, i, j - 1, box);
	else if (ft_isspace(cmd->data[i]))
		result = add_text(cmd, i, j - 1, 1);
	else if (cmd->data[i])
		result = add_text(cmd, i, j - 1, 0);
	return (result);
}

// Count the different strings needed
int	str_extractor(t_cmd *cmd, t_box *box)
{
	int		i;
	int		j;
	int		result;

	cmd->extracted = malloc((cmd->str_count + 1) * sizeof(char *));
	if (!cmd->extracted)
		return (-1);
	i = 0;
	j = 0;
	cmd->extracted[0] = 0;
	while (cmd->data[i])
	{
		if (cmd->data[i])
			j++;
		result = calc_result(cmd, i, j, box);
		if (result == -1)
			return (-1);
		i += result;
	}
	return (0);
}
