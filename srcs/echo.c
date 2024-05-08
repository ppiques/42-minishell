/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesnoye <ldesnoye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/13 19:37:41 by ldesnoye          #+#    #+#             */
/*   Updated: 2022/05/13 19:37:43 by ldesnoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	is_option_n(char *s)
{
	int	i;

	if (s)
	{
		if (s[0] != '-')
			return (0);
		if (s[1] != 'n')
			return (0);
		i = 2;
		while (s[i])
		{
			if (s[i] != 'n')
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}

static void	print_with_spaces(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		ft_putstr_fd(tab[i], 1);
		if (tab[i + 1])
			ft_putchar_fd(' ', 1);
		i++;
	}
}

static void	i_hate_the_norme(int newline, t_box *box)
{
	if (newline)
		ft_putchar_fd('\n', 1);
	free_box(box, 1);
	exit(0);
}

int	ft_echo(t_cmd *cmd, t_box *box)
{
	int		newline;
	int		i;
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		minidup(cmd);
		newline = 1;
		i = 1;
		if (cmd->args[1])
		{
			while (is_option_n(cmd->args[i]))
			{
				newline = 0;
				i++;
			}
			print_with_spaces(cmd->args + i);
		}
		i_hate_the_norme(newline, box);
	}
	else
		waitpid(pid, &i, 0);
	return (0);
}
