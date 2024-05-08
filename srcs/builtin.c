/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiques <ppiques@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 06:20:53 by cferrari          #+#    #+#             */
/*   Updated: 2022/04/25 17:08:07 by ppiques          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	cd_error(int ret, t_cmd *cmd)
{
	char	*error_prompt;

	if (ret)
	{
		error_prompt = ft_concat("Debash: cd: ", cmd->args[1]);
		if (!error_prompt)
		{
			ft_putstr_fd("Debash: memory allocation error\n", 2);
			return (1);
		}
		perror(error_prompt);
		free(error_prompt);
	}
	return (ret);
}

static int	cd_tilde(t_cmd *cmd)
{
	char	*path;
	char	*buffer;
	int		ret;

	path = ft_strjoin("/mnt/nfs/homes/", getenv("USER"));
	if (!path)
	{
		ft_putstr_fd("Debash: memory allocation error\n", 2);
		return (1);
	}
	buffer = ft_strjoin(path, cmd->args[1] + 1);
	if (!buffer)
	{
		free(path);
		ft_putstr_fd("Debash: memory allocation error\n", 2);
		return (1);
	}
	ret = chdir(buffer);
	free(buffer);
	free(path);
	return (ret);
}

int	cd(t_cmd *cmd)
{
	int		ret;

	if (!cmd->args[1])
		return (0);
	if (cmd->args[2])
	{
		ft_putstr_fd("Debash: cd: too many arguments\n", 2);
		return (1);
	}
	if (cmd->args[1][0] == '~')
		ret = !(!(cd_tilde(cmd)));
	else
		ret = !(!(chdir(cmd->args[1])));
	ret = cd_error(ret, cmd);
	return (ret);
}

int	pwd(t_box *box, t_cmd *cmd)
{
	char	*path;
	pid_t	pid;
	int		status;

	pid = fork();
	if (!pid)
	{
		minidup(cmd);
		path = getcwd(NULL, 0);
		if (!path)
		{
			perror("Debash: pwd");
			return (1);
		}
		ft_putendl_fd(path, 1);
		free(path);
		free_box(box, 1);
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
	return (WEXITSTATUS(status));
}

int	ft_env(t_box *box, t_cmd *cmd)
{
	int		status;
	pid_t	pid;

	pid = fork();
	if (!pid)
	{
		minidup(cmd);
		ft_lstiter(*box->env_list, print_var);
		free_box(box, 1);
		exit(0);
	}
	else
		waitpid(pid, &status, 0);
	return (0);
}
