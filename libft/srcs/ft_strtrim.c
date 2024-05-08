/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesnoye <ldesnoye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:29:14 by ldesnoye          #+#    #+#             */
/*   Updated: 2021/11/29 18:29:14 by ldesnoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	is_in(char c, char const *charset)
{
	int	i;

	i = 0;
	while (charset[i])
	{
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

static int	scan_end(int len, char const *s, char const *set)
{
	int	i;
	int	count;

	count = 0;
	i = 0;
	while (is_in(s[len - i - 1], set))
	{
		i++;
		count++;
	}
	return (count);
}

static int	check(char const *s1, char const *set)
{
	int	i;

	i = 0;
	while (s1[i])
	{
		if (!is_in(s1[i], set))
			return (1);
		i++;
	}
	return (0);
}

char	*create_new(int l, int start, char const *s1)
{
	int		j;
	char	*new;

	j = 0;
	new = malloc((l + 1 - start) * sizeof(char));
	if (!new)
		return (NULL);
	while (j < l - start)
	{
		new[j] = s1[start + j];
		j++;
	}
	new[j] = 0;
	return (new);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		l;
	int		start;
	char	*new;

	if (!check(s1, set))
	{
		new = malloc(sizeof(char));
		new[0] = 0;
		return (new);
	}
	start = 0;
	l = ft_strlen(s1);
	l -= scan_end(l, s1, set);
	while (is_in(s1[start], set))
		start++;
	new = create_new(l, start, s1);
	return (new);
}
