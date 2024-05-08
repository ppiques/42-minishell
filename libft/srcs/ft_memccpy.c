/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesnoye <ldesnoye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:29:14 by ldesnoye          #+#    #+#             */
/*   Updated: 2021/11/29 18:29:14 by ldesnoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dest, const void *src, int c, size_t n)
{
	size_t	i;

	i = 0;
	while (i < n)
	{
		*(t_byte *)(dest + i) = *(t_byte *)(src + i);
		if (*(t_byte *)(src + i) == (t_byte)c)
			return (dest + i + 1);
		i++;
	}
	return (0);
}
