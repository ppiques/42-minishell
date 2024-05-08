/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   safe_atol.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesnoye <ldesnoye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/25 10:54:55 by ldesnoye          #+#    #+#             */
/*   Updated: 2022/01/25 10:54:57 by ldesnoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static int	overflow(long int n, char c, int sign)
{
	long int	max;

	max = 9223372036854775807;
	if (sign == 1)
	{
		if (n > max / 10 || (n == max / 10 && c > '7'))
			return (1);
	}
	else
	{
		if (n > max / 10 || (n == max / 10 && c > '8'))
			return (1);
	}
	return (0);
}

long int	safe_atol(char *s)
{
	long int	sum;
	int			i;
	int			sign;

	sum = 0;
	sign = 1;
	if (s)
	{
		i = (s[0] == '-' || s[0] == '+');
		sign = (s[0] == '-') * (-1) + (s[0] != '-');
		while (s[i] >= '0' && s[i] <= '9' && !overflow(sum, s[i], sign))
		{
			sum = sum * 10 + (s[i] - '0');
			i++;
		}
		if (s[i])
			return (0);
	}
	return (sum * sign);
}
