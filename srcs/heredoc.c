/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiques <ppiques@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/30 19:15:39 by ppiques           #+#    #+#             */
/*   Updated: 2022/04/30 22:57:57 by ppiques          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	heredoc(t_box *box, char *filename, char *delim)
{
	int		fd;
	int		quoted;
	char	*line;
	int		ret;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 00644);
	if (fd == -1)
		return (-1);
	g_exit_code = CODE_HEREDOC;
	quoted = ft_isquote(delim[0]);
	line = readline("> ");
	while (line && heredoc_compare(line, delim, quoted))
	{
		ret = heredoc_var_expander(&line, box, quoted);
		if (ret == -1 || special_write(fd, line) == -1)
			heredoc_freeonwriteerror(line, fd);
		free(line);
		line = readline("> ");
	}
	if (!line && g_exit_code == CODE_HEREDOC)
		eof_warning(delim, box);
	rl_replace_line("", 0);
	free(line);
	close(fd);
	return (0);
}

int	heredoc_number(t_box *box, t_list **list, int nb)
{
	t_list	*link;
	t_redir	*cast;
	char	*filename;

	filename = heredoc_name(nb);
	if (!filename)
		return (-1);
	link = *list;
	while (link)
	{
		cast = (t_redir *)link->content;
		if (cast->type == redir_heredoc)
		{
			if (heredoc(box, filename, cast->data) == -1)
			{
				free(filename);
				return (-1);
			}
		}
		if (g_exit_code == CODE_SIGINT)
			return (CODE_SIGINT);
		link = link->next;
	}
	free(filename);
	return (0);
}

void	heredoc_fork(t_box *box, int i)
{
	int	ret;

	ret = heredoc_number(box, box->line[i]->redir_list, i);
	free_box(box, 1);
	exit(ret);
}

int	heredoc_handler(t_box *box)
{
	int		i;
	int		ret;
	pid_t	pid;

	i = 0;
	while (box->line[i])
	{
		if (box->line[i]->redir_list)
		{
			g_exit_code = CODE_MAINHEREDOC;
			pid = fork();
			if (pid == -1)
				return (-1);
			else if (pid == 0)
				heredoc_fork(box, i);
			else
			{
				waitpid(pid, &ret, 0);
				if (WEXITSTATUS(ret))
					return (WEXITSTATUS(ret));
			}
		}
		i++;
	}
	return (0);
}

int	heredoc_deleter(t_box *box)
{
	int		i;
	char	*name;

	i = 0;
	while (box->line[i])
	{
		name = heredoc_name(i);
		if (!name)
			return (-1);
		unlink(name);
		free(name);
		i++;
	}
	return (0);
}
