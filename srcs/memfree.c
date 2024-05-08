/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memfree.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiques <ppiques@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 11:48:42 by ldesnoye          #+#    #+#             */
/*   Updated: 2022/04/30 22:45:02 by ppiques          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Free char** created from ft_split function of the libft of 42, the first
// project of the current Common Core (as of 04/21/2022, might be subject to
// change in the future depending on the will of the pedago).
void	free_split(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

// Free var (including name and value str)
void	free_var(void *var)
{
	t_var	*cast;

	if (var)
	{
		cast = (t_var *)var;
		free(cast->name);
		free(cast->value);
	}
	free(var);
}

// free every element of box for the next call to readline
void	free_for_new_line(t_box *box)
{
	int	i;

	i = 0;
	if (box->line)
	{
		while (box->line[i] && i < box->nb_of_cmds)
		{
			cmd_free(box->line[i], 5);
			i++;
		}
	}
	if (box->pipes)
	{
		pipe_full_close(box->pipes, box->nb_of_cmds - 1);
		free(box->pipes);
		box->pipes = NULL;
	}
	free(box->line);
	box->line = NULL;
	free(box->prompt);
	box->prompt = NULL;
	free(box->input);
	box->input = NULL;
	free(box->pid_tab);
	box->pid_tab = NULL;
}

// Free everything.
void	free_box(t_box *box, int flag)
{
	rl_clear_history();
	if (flag == 0)
		free(box->prompt);
	if (flag == 1)
		free_for_new_line(box);
	ft_lstclear(box->env_list, free_var);
	free(box->env_list);
	free(box);
}
