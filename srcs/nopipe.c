/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nopipe.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesnoye <ldesnoye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/08 12:23:30 by ldesnoye          #+#    #+#             */
/*   Updated: 2022/05/08 12:23:34 by ldesnoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minidup(t_cmd *cmd)
{
	if (cmd->fd_in != 0)
		dup2(cmd->fd_in, 0);
	if (cmd->fd_out != 1)
		dup2(cmd->fd_out, 1);
}

int	execute_single_cmd(t_cmd *cmd, t_box *box)
{
	int	ret;

	ret = 1;
	if (!open_list(cmd))
	{
		if (!is_only_spaces(cmd->args[0]) || \
has_quotes(cmd->data))
			ret = faitout_single(cmd, box);
		else
			ret = 0;
	}
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	if (cmd->fd_out != 1)
		close(cmd->fd_out);
	return (ret);
}

static	int	single_fork(t_box *box, t_cmd *cmd, char **paths)
{
	signal(SIGQUIT, SIG_DFL);
	minidup(cmd);
	tryexec(paths, cmd->args, cmd, box);
	free_split(paths);
	return (-1);
}

static int	single_main_process(pid_t pid)
{
	int	status;

	waitpid(pid, &status, 0);
	if (WIFSIGNALED(status))
		return (128 + WTERMSIG(status));
	return (WEXITSTATUS(status));
}

int	faitout_single(t_cmd *cmd, t_box *box)
{
	pid_t	pid;
	char	**paths;

	paths = get_paths(box->env_list);
	if (!paths)
		return (-1);
	if (is_builtin(cmd->args[0]))
	{
		free_split(paths);
		return (exec(box, cmd));
	}
	else
	{
		pid = fork();
		if (!pid)
			return (single_fork(box, cmd, paths));
		else
		{
			free_split(paths);
			return (single_main_process(pid));
		}
	}
}
