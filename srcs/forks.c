/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   forks.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesnoye <ldesnoye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 14:16:37 by ldesnoye          #+#    #+#             */
/*   Updated: 2022/05/05 14:16:39 by ldesnoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	megadup(t_cmd *cmd, t_box *box)
{
	int	fd_in;
	int	fd_out;

	fd_in = 0;
	if (cmd->fd_in != 0)
		fd_in = cmd->fd_in;
	else if (cmd->cmd_ind != 0)
		fd_in = box->pipes[2 * (cmd->cmd_ind - 1)];
	if (fd_in != 0)
		dup2(fd_in, 0);
	fd_out = 1;
	if (cmd->fd_out != 1)
		fd_out = cmd->fd_out;
	else if (cmd->cmd_ind != box->nb_of_cmds - 1)
		fd_out = box->pipes[2 * cmd->cmd_ind + 1];
	if (fd_out != 1)
		dup2(fd_out, 1);
}

int	execute_cmd(t_cmd *cmd, t_box *box)
{
	int	ret;

	ret = 1;
	signal(SIGQUIT, SIG_DFL);
	if (!open_list(cmd))
	{
		if (!is_only_spaces(cmd->args[0]) || \
has_quotes(cmd->data))
			ret = faitout(cmd, box);
		else
			ret = 0;
	}
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	if (cmd->fd_out != 1)
		close(cmd->fd_out);
	exit(ret);
}

pid_t	*create_processes(int nb, t_box *box)
{
	pid_t	*tab;
	pid_t	pid;
	int		i;

	tab = malloc((nb + 1) * sizeof(pid_t));
	if (!tab)
		return (NULL);
	i = 0;
	tab[0] = 0;
	while (i < nb)
	{
		pid = fork();
		if (!pid)
		{
			free(tab);
			execute_cmd(box->line[i], box);
		}
		else
		{
			tab[i] = pid;
			tab[i + 1] = 0;
		}
		i++;
	}
	return (tab);
}

int	wait_all_processes(pid_t *pid_tab)
{
	int	status;
	int	i;

	i = 0;
	while (pid_tab[i])
	{
		waitpid(pid_tab[i], &status, 0);
		i++;
	}
	if (WIFSIGNALED(status))
		return (WTERMSIG(status));
	return (WEXITSTATUS(status));
}
