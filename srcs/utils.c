/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiques <ppiques@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 01:52:19 by cferrari          #+#    #+#             */
/*   Updated: 2022/04/29 17:11:37 by ppiques          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	save_exitcode(t_list **env_list, int n)
{
	char	*new;
	t_var	*exitvar;

	new = ft_itoa(n % 256);
	if (!new)
	{
		ft_putstr_fd("Debash: memory allocation error\n", 2);
		return (1);
	}
	exitvar = get_envvar(env_list, "?");
	free(exitvar->value);
	exitvar->value = new;
	return (0);
}

void	treat_sig(int sig)
{
	if (sig == SIGINT)
	{
		ft_putchar_fd('\n', 1);
		if (g_exit_code == CODE_STD || g_exit_code == CODE_SIGINT)
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
		if (g_exit_code == CODE_HEREDOC)
			close(STDIN_FILENO);
		if (g_exit_code != CODE_EXEC)
			g_exit_code = CODE_SIGINT;
	}
}

int	exec(t_box *box, t_cmd *cmd)
{
	char	*str;
	int		ret;

	ret = 0;
	str = cmd->args[0];
	if (!ft_strncmp(str, "exit", 5))
		ret = ft_exit(box, cmd);
	else if (!ft_strncmp(str, "echo", 5))
		ret = ft_echo(cmd, box);
	else if (!ft_strncmp(str, "cd", 3) && cmd->args[1])
		ret = cd(cmd);
	else if (!ft_strncmp(str, "pwd", 4))
		ret = pwd(box, cmd);
	else if (!ft_strncmp(str, "env", 4))
		ret = ft_env(box, cmd);
	else if (!ft_strncmp(str, "export", 7))
		ret = ft_export(box, cmd);
	else if (!ft_strncmp(str, "unset", 6))
		ret = ft_unset(box, cmd);
	return (ret);
}

int	is_builtin(char *str)
{
	int	ret;

	if (!str)
		return (0);
	ret = !ft_strncmp(str, "echo", 5);
	ret = (ret || !ft_strncmp(str, "cd", 3));
	ret = (ret || !ft_strncmp(str, "pwd", 4));
	ret = (ret || !ft_strncmp(str, "export", 7));
	ret = (ret || !ft_strncmp(str, "unset", 6));
	ret = (ret || !ft_strncmp(str, "env", 4));
	ret = (ret || !ft_strncmp(str, "exit", 5));
	return (ret);
}
