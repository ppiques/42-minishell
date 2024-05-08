/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesnoye <ldesnoye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:29:13 by ldesnoye          #+#    #+#             */
/*   Updated: 2021/11/29 18:29:13 by ldesnoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	do_all(int n, char *str, int power, long abs)
{
	int	i;

	i = 0;
	if (n < 0)
	{
		str[0] = '-';
		i++;
	}
	while (power > 0)
	{
		str[i] = abs / power + '0';
		abs %= power;
		power /= 10;
		i++;
	}
	str[i] = 0;
}

char	*ft_itoa(int n)
{
	char	*str;
	int		power;
	long	abs;
	int		count;

	if (n < 0)
		abs = -(long)n;
	else
		abs = (long)n;
	power = 1;
	count = 1;
	while (power <= abs / 10)
	{
		power *= 10;
		count++;
	}
	str = malloc((count + (n < 0) + 1) * sizeof(char));
	if (!str)
		return (0);
	do_all(n, str, power, abs);
	return (str);
}
