/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesnoye <ldesnoye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/29 18:29:14 by ldesnoye          #+#    #+#             */
/*   Updated: 2021/11/29 18:29:14 by ldesnoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	print_abs_nb(int n, int fd)
{
	char	digit;
	int		power_of_ten;

	if (n == 0)
	{
		write(fd, &"0", 1);
	}
	else
	{
		power_of_ten = 1;
		while (n / power_of_ten >= 10)
		{
			power_of_ten *= 10;
		}
		while (power_of_ten != 0)
		{
			digit = '0' + (n / power_of_ten);
			n = n % power_of_ten;
			power_of_ten /= 10;
			write(fd, &digit, 1);
		}
	}
}

void	ft_putnbr_fd(int n, int fd)
{
	if (n == -2147483648)
	{
		write(fd, &"-2147483648", 11);
	}
	else
	{
		if (n < 0)
		{
			write(fd, &"-", 1);
			n *= (-1);
		}
		print_abs_nb(n, fd);
	}
}
