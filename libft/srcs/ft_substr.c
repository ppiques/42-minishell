/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesnoye <ldesnoye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:29:14 by ldesnoye          #+#    #+#             */
/*   Updated: 2021/11/29 18:29:14 by ldesnoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	calc_max(int start, int len, int size)
{
	if (start + len > size)
		return (size - start);
	else
		return (len);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*new;
	size_t	size;
	size_t	max;
	size_t	i;

	size = ft_strlen(s);
	if (start >= size || len == 0)
	{
		new = malloc(sizeof(char));
		if (!new)
			return (NULL);
		new[0] = 0;
	}
	else
	{
		max = calc_max(start, len, size);
		new = malloc(sizeof(char) * (max + 1));
		if (!new)
			return (NULL);
		i = -1;
		while (++i < max)
			new[i] = s[start + i];
		new[i] = 0;
	}
	return (new);
}
