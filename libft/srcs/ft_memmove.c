/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesnoye <ldesnoye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:29:14 by ldesnoye          #+#    #+#             */
/*   Updated: 2021/11/29 18:29:14 by ldesnoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	size_t	i;

	if (dest || src)
	{
		if (dest < src)
		{
			i = 0;
			while (i < n)
			{
				*(t_byte *)(dest + i) = *(t_byte *)(src + i);
				i++;
			}
		}
		else
		{
			i = n;
			while (i--)
				*(t_byte *)(dest + i) = *(t_byte *)(src + i);
		}
	}
	return (dest);
}
