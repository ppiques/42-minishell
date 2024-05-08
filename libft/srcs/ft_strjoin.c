/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesnoye <ldesnoye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:29:14 by ldesnoye          #+#    #+#             */
/*   Updated: 2021/11/29 18:29:14 by ldesnoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		l1;
	int		l2;
	int		i;
	char	*new;

	l1 = ft_strlen(s1);
	l2 = ft_strlen(s2);
	new = malloc((l1 + l2 + 1) * sizeof(char));
	if (!new)
		return (NULL);
	i = 0;
	while (i < l1)
	{
		new[i] = s1[i];
		i++;
	}
	i = 0;
	while (i < l2)
	{
		new[i + l1] = s2[i];
		i++;
	}
	new[l1 + l2] = 0;
	return (new);
}
