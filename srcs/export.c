/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesnoye <ldesnoye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/12 00:30:35 by ldesnoye          #+#    #+#             */
/*   Updated: 2022/05/12 00:30:37 by ldesnoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	export_equal(char *name, char *value, t_list **env_list)
{
	t_var	*var;

	if (!value)
	{
		free(name);
		return (1);
	}
	var = get_envvar(env_list, name);
	if (var->name)
	{
		free(name);
		free(var->value);
		var->value = value;
	}
	else
	{
		if (add_front_var(name, value, env_list))
			return (1);
	}
	return (0);
}

int	export_plus(char *name, char *value, t_list **env_list)
{
	t_var	*var;
	char	*new;

	if (!value)
	{
		free(name);
		return (1);
	}
	var = get_envvar(env_list, name);
	if (var->name)
	{
		new = ft_concat(var->value, value);
		free(name);
		if (!new)
		{
			free(value);
			ft_putstr_fd("Debash: memory allocation error\n", 2);
			return (1);
		}
		free(var->value);
		var->value = new;
	}
	else if (add_front_var(name, value, env_list))
		return (1);
	return (0);
}

int	true_export(t_list **env_list, char *arg)
{
	char	*value;
	char	*name;
	int		i;
	int		j;

	value = NULL;
	name = extract_export_name(arg);
	if (!name || !name[0])
	{
		free(name);
		return (print_invalid("export", arg));
	}
	i = ft_strlen(name);
	j = 2 * (arg[i] == '+') + (arg[i] == '=');
	if (j)
	{
		value = ft_substr(arg, i + j, ft_strlen(arg));
		if (j == 1)
			return (export_equal(name, value, env_list));
		else if (j == 2)
			return (export_plus(name, value, env_list));
	}
	else
		free(name);
	return (0);
}

void	export_fork(t_cmd *cmd, t_box *box)
{
	minidup(cmd);
	ft_lstiter(*box->env_list, print_var_export);
	free_box(box, 1);
	exit(0);
}

int	ft_export(t_box *box, t_cmd *cmd)
{
	int		i;
	pid_t	pid;

	if (!cmd->args[1])
	{
		pid = fork();
		if (!pid)
			export_fork(cmd, box);
		else
		{
			waitpid(pid, &i, 0);
			return (WEXITSTATUS(i));
		}
	}
	else
	{
		i = 1;
		while (cmd->args[i])
		{
			if (true_export(box->env_list, cmd->args[i]))
				return (1);
			i++;
		}
	}
	return (0);
}
