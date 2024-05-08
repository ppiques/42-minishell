/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redirs_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesnoye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 14:09:07 by ldesnoye          #+#    #+#             */
/*   Updated: 2022/05/14 14:09:08 by ldesnoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// returns size of the raw string of redirection
// stops at whitespaces or chevrons
int	redir_size(char const *s)
{
	int		i;
	char	quoted;

	i = 0;
	quoted = 0;
	while (s[i] && ((!ft_isspace(s[i]) && !ft_isredir(s[i])) || quoted))
	{
		if (s[i] == quoted)
			quoted = 0;
		else if (!quoted && ft_isquote(s[i]))
			quoted = s[i];
		i++;
	}
	return (i);
}

void	need_to_erase_loop(t_cmd *cmd, int c, int i)
{
	int	j;

	j = 0;
	while (j < c)
	{
		cmd->need_to_erase[j + i] = 1;
		j++;
	}
}
