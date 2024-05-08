/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiques <ppiques@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 15:17:22 by ppiques           #+#    #+#             */
/*   Updated: 2022/04/30 15:20:56 by ppiques          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	next_pipe(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '|')
	{
		if (ft_isquote(s[i]))
		{
			i += skip_first_char(s + i);
			if (s[i])
				i++;
		}
		else
			i++;
	}
	return (i);
}

char	*extract_str(char *base, char quote)
{
	char	*end;
	int		len;
	char	*new;

	end = ft_strchr(base + 1, quote);
	if (!end)
		return (NULL);
	len = end - base;
	new = ft_substr(base, 1, len);
	return (new);
}

int	skip_first_char(const char *s)
{
	int	i;

	i = 1;
	while (s[i] && s[i] != *s)
		i++;
	return (i);
}

int	count_cmds(const char *s)
{
	char	quote;
	int		total;
	int		i;

	i = 0;
	total = 1;
	quote = 0;
	while (s[i])
	{
		if (!quote)
		{
			if (ft_isquote(s[i]))
				quote = s[i];
			if (s[i] == '|')
				total++;
		}
		else
		{
			if (s[i] == quote)
				quote = 0;
		}
		i++;
	}
	return (total);
}
