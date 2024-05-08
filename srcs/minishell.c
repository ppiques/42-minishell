/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiques <ppiques@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/08 16:34:43 by cferrari          #+#    #+#             */
/*   Updated: 2022/05/01 05:22:23 by ppiques          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

unsigned int	g_exit_code = CODE_STD;

int	cmd_exec(t_box *box, int ret)
{
	g_exit_code = CODE_EXEC;
	if (box->nb_of_cmds == 1)
		ret = execute_single_cmd(box->line[0], box);
	else if (box->nb_of_cmds >= 2)
	{
		box->pid_tab = create_processes(box->nb_of_cmds, box);
		if (!box->pid_tab)
			return (print_memerror_return());
		pipe_full_close(box->pipes, box->nb_of_cmds - 1);
		ret = wait_all_processes(box->pid_tab);
	}
	if (save_exitcode(box->env_list, ret))
		return (1);
	g_exit_code = CODE_STD;
	return (0);
}

int	from_heredoc_to_exec(t_box *box, t_syntaxerror err, int malloc_check)
{
	int				ret;

	ret = heredoc_handler(box);
	if (ret == -1)
		return (print_memerror_return());
	else if (!err && malloc_check == 0 && !(ret == CODE_SIGINT))
	{
		if (cmd_exec(box, ret))
			return (1);
	}
	if (g_exit_code == CODE_SIGINT)
	{
		if (save_exitcode(box->env_list, g_exit_code))
			return (1);
	}
	return (0);
}

int	actual_input(t_box *box)
{
	t_syntaxerror	err;
	int				malloc_check;

	add_history(box->input);
	box->nb_of_cmds = count_cmds(box->input);
	if (parse_cmds(box) == -1)
		return (print_memerror_return());
	err = syntax_checker(box);
	if (err)
	{
		print_syntaxerror(err);
		if (save_exitcode(box->env_list, 2))
			return (1);
	}
	malloc_check = pipe_handler(box);
	if (malloc_check == 0)
		malloc_check = cmd_redir_expander(box);
	if (from_heredoc_to_exec(box, err, malloc_check))
		return (1);
	malloc_check = (heredoc_deleter(box) || malloc_check);
	if (!err && malloc_check)
		return (print_memerror_return());
	return (0);
}

int	command_loop(t_box *box)
{
	while (1)
	{
		box->prompt = ft_strdup("Debash:~$ ");
		if (!box->prompt)
			return (print_memerror_return());
		box->input = readline(box->prompt);
		if (g_exit_code == CODE_SIGINT)
		{
			if (save_exitcode(box->env_list, CODE_SIGINT))
				return (1);
		}
		box->history_size++;
		if (!box->input)
		{
			printf("exit\n");
			return (0);
		}
		if (box->input[0])
		{
			if (actual_input(box))
				return (1);
		}
		free_for_new_line(box);
	}
}

int	main(int ac, char **av, const char **envp)
{
	t_box	*box;
	int		ret;

	(void)ac;
	(void)av;
	box = init_box();
	if (!box)
		print_memerror_exit();
	box->envp = envp;
	box->history_size = 0;
	if (create_envp_list(envp, box))
	{
		free(box->env_list);
		free(box);
		print_memerror_exit();
	}
	signal(SIGQUIT, SIG_IGN);
	signal(SIGINT, treat_sig);
	ret = command_loop(box);
	free_box(box, ret);
	exit(ret);
}
