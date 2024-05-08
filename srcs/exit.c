/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesnoye <ldesnoye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 00:34:38 by ldesnoye          #+#    #+#             */
/*   Updated: 2022/05/12 00:34:39 by ldesnoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_zeroes(char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		if (s[i] == '+' || s[i] == '-')
			i++;
		while (s[i])
		{
			if (s[i] != '0')
				return (0);
			i++;
		}
	}
	return (1);
}

int	ft_exit(t_box *box, t_cmd *cmd)
{
	long int	ret;
	int			error;

	ret = safe_atol(cmd->args[1]);
	error = 1;
	if (!ret)
		error = !is_zeroes(cmd->args[1]);
	if (!ret && error)
	{
		ft_putstr_fd("Debash: exit: ", 2);
		ft_putstr_fd(cmd->args[1], 2);
		ft_putstr_fd(": numeric argument required", 2);
		ret = 2;
	}
	else if (cmd->args[1] && cmd->args[2])
	{
		ft_putstr_fd("Debash: exit: too many arguments", 2);
		return (1);
	}
	free_box(box, 1);
	(void)box;
	exit(ret % 256);
}
