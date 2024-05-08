/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesnoye <ldesnoye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:29:14 by ldesnoye          #+#    #+#             */
/*   Updated: 2021/11/29 18:29:14 by ldesnoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	test_little(const char *big, const char *little)
{
	int	i;

	i = 0;
	while (little[i] && big[i])
	{
		if (little[i] != big[i])
			return (0);
		i++;
	}
	return (1);
}

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	l;
	size_t	b;

	if (!little[0])
		return ((char *)big);
	i = 0;
	l = ft_strlen(little);
	b = ft_strlen(big);
	while (i + l <= len && i + l <= b)
	{
		if (test_little(big + i, little))
			return ((char *)(big + i));
		i++;
	}
	return (0);
}
