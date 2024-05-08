/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_handler.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiques <ppiques@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 23:19:49 by ppiques           #+#    #+#             */
/*   Updated: 2022/05/01 05:38:22 by ppiques          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	pipe_closer(int i, int *pipes, int max)
{
	int	j;

	j = 0;
	while (j < 2 * max)
	{
		if (!(j == 2 * (i - 1) || j == 2 * i + 1))
			close(pipes[j]);
		j++;
	}
	return (0);
}

void	pipe_full_close(int *pipes, int max)
{
	int	ind;

	ind = 0;
	if (pipes)
	{
		while (ind < 2 * max)
		{
			if (pipes[ind] != 0 && pipes[ind] != 1)
				close(pipes[ind]);
			ind++;
		}
	}
}

int	pipe_handler(t_box *box)
{
	int	*pipes_tab;
	int	i;
	int	j;

	i = box->nb_of_cmds;
	pipes_tab = malloc((2 * i - 1) * sizeof(int));
	if (!pipes_tab)
		return (-1);
	j = 0;
	while (j < i - 1)
	{
		if (pipe(pipes_tab + 2 * j))
		{
			pipe_full_close(pipes_tab, j);
			free(pipes_tab);
			return (-1);
		}
		j++;
	}
	pipes_tab[2 * i - 2] = 0;
	box->pipes = pipes_tab;
	return (0);
}
