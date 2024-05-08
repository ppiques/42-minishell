/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tryexec.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesnoye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/01 15:43:42 by ldesnoye          #+#    #+#             */
/*   Updated: 2021/12/01 15:43:43 by ldesnoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**get_paths(t_list **env_list)
{
	char	*paths;

	paths = get_value(env_list, "PATH");
	return (ft_split(paths, ':'));
}

void	direct_exec(char **args, char **envp, t_box *box)
{
	int		acc_ret;
	char	*error_prompt;

	acc_ret = access(args[0], X_OK);
	if (acc_ret == 0)
		execve(args[0], args, envp);
	error_prompt = ft_concat("Debash: ", args[0]);
	if (!error_prompt)
	{
		ft_putstr_fd("Debash: memory allocation error\n", 2);
		free_box(box, 1);
		exit(1);
	}
	perror(error_prompt);
	free_box(box, 1);
	exit(127 + acc_ret);
}

void	loop_exec(char **paths, char **args, char **envp, t_box *box)
{
	char	*s;
	int		acc_ret;

	while (paths && *paths)
	{
		s = ft_pathjoin(*paths, args[0]);
		if (!s)
		{
			free_box(box, 1);
			exit(1);
		}
		acc_ret = access(s, F_OK);
		if (acc_ret == 0)
		{
			acc_ret = access(s, X_OK);
			if (acc_ret == 0)
				execve(s, args, envp);
			ft_putstr_fd("Debash: ", 2);
			perror(args[0]);
			free_box(box, 1);
			exit(127 + acc_ret);
		}
		free(s);
		paths++;
	}
}

void	tryexec(char **paths, char **args, t_cmd *cmd, t_box *box)
{
	char	*japln;
	char	*error_prompt;

	japln = ft_strchr(args[0], '/');
	if ((paths && !paths[0]) || japln)
		direct_exec(args, (char **)box->envp, box);
	else
	{
		if (!is_only_spaces(args[0]))
			loop_exec(paths, args, (char **)box->envp, box);
		error_prompt = ft_concat(args[0], ": command not found\n");
		if (!error_prompt)
		{
			ft_putstr_fd("Debash: memory allocation error\n", 2);
			free_box(box, 1);
			exit(1);
		}
		ft_putstr_fd(error_prompt, 2);
		free_box(box, 1);
		(void)box;
		exit(127);
	}
	(void)cmd;
}

int	faitout(t_cmd *cmd, t_box *box)
{
	char	**paths;
	int		ret;

	pipe_closer(cmd->cmd_ind, box->pipes, box->nb_of_cmds - 1);
	paths = get_paths(box->env_list);
	if (!paths)
		return (1);
	megadup(cmd, box);
	if (is_builtin(cmd->args[0]))
	{
		ret = exec(box, cmd);
		exit(ret);
	}
	else
		tryexec(paths, cmd->args, cmd, box);
	return (1);
}
