/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesnoye <ldesnoye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 15:52:46 by ldesnoye          #+#    #+#             */
/*   Updated: 2022/05/14 15:52:47 by ldesnoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	print_memerror_return(void)
{
	ft_putstr_fd("Debash: memory allocation error\n", 2);
	return (1);
}

t_box	*init_box(void)
{
	t_box	*box;

	box = malloc(sizeof(t_box));
	if (!box)
		return (NULL);
	box->envp = NULL;
	box->prompt = NULL;
	box->input = NULL;
	box->history_size = 0;
	box->pipes = NULL;
	box->nb_of_cmds = 0;
	box->line = NULL;
	box->pid_tab = NULL;
	box->env_list = NULL;
	return (box);
}

void	print_memerror_exit(void)
{
	ft_putstr_fd("Debash: memory allocation error\n", 2);
	exit(1);
}

int	is_only_spaces(char *s)
{
	int	i;

	i = 0;
	if (s)
	{
		while (s[i])
		{
			if (!ft_isspace(s[i]))
				return (0);
			i++;
		}
		return (1);
	}
	return (1);
}

int	has_quotes(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (ft_isquote(s[i]))
			return (1);
		i++;
	}
	return (0);
}
