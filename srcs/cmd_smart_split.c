/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_smart_split.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiques <ppiques@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:04:40 by ldesnoye          #+#    #+#             */
/*   Updated: 2022/04/25 18:14:51 by ppiques          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	word_size(char const *s)
{
	int	i;
	int	quote;

	i = 0;
	quote = 0;
	if (s)
	{
		while (s[i] && (!ft_isspace(s[i]) || quote))
		{
			if (s[i] == quote)
				quote = 0;
			else if (!quote && ft_isquote(s[i]))
				quote = s[i];
			i++;
		}
	}
	return (i);
}

static int	count_words(char const *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (!ft_isspace(s[i]))
		{
			i += word_size(s + i);
			count++;
		}
		else
			i++;
	}
	return (count);
}

static char	*ft_malloc(char const *s)
{
	char	*str;
	int		size;

	size = word_size(s);
	str = malloc(sizeof(char) * (size + 1));
	if (!str)
		return (NULL);
	ft_strlcpy(str, s, size + 1);
	return (str);
}

static int	norme(char **tab, char const *s)
{
	int		j;
	char	*new;

	j = 0;
	while (tab[j])
		j++;
	new = ft_malloc(s);
	if (!new)
	{
		free_split(tab);
		return (-1);
	}
	tab[j] = new;
	tab[j + 1] = NULL;
	return (0);
}

// Splits str into args, based on spaces and quotes
// returns a char ** containing each arg
char	**smart_split(char const *s)
{
	char	**tab;
	int		i;
	int		end;

	i = 0;
	if (!s)
		return (NULL);
	tab = malloc(sizeof(char *) * (count_words(s) + 1));
	if (!tab)
		return (NULL);
	tab[0] = NULL;
	while (s[i])
	{
		while (s[i] && ft_isspace(s[i]))
			i++;
		if (s[i] && !ft_isspace(s[i]))
		{
			norme(tab, s + i);
			end = word_size(s + i);
			i += end;
		}
	}
	return (tab);
}
