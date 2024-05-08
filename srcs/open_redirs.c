/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_redirs.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesnoye <ldesnoye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/07 13:48:25 by ldesnoye          #+#    #+#             */
/*   Updated: 2022/05/07 13:48:27 by ldesnoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	open_infile(t_cmd *cmd, char *filename)
{
	int		fd;
	char	*error_prompt;

	if (cmd->fd_in != 0)
	{
		close(cmd->fd_in);
		cmd->fd_in = 0;
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		error_prompt = ft_concat("Debash: ", filename);
		if (!error_prompt)
		{
			ft_putstr_fd("Debash: memory allocation error\n", 2);
			return (1);
		}
		perror(error_prompt);
		free(error_prompt);
		return (-1);
	}
	else
		cmd->fd_in = fd;
	return (0);
}

int	open_outfile(t_cmd *cmd, char *filename)
{
	int		fd;
	char	*error_prompt;

	if (cmd->fd_out != 1)
	{
		close(cmd->fd_out);
		cmd->fd_out = 1;
	}
	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 00644);
	if (fd == -1)
	{
		error_prompt = ft_concat("Debash: ", filename);
		if (!error_prompt)
		{
			ft_putstr_fd("Debash: memory allocation error\n", 2);
			return (1);
		}
		perror(error_prompt);
		free(error_prompt);
		return (-1);
	}
	else
		cmd->fd_out = fd;
	return (0);
}

int	open_heredoc(t_cmd *cmd)
{
	int		fd;
	char	*filename;

	filename = heredoc_name(cmd->cmd_ind);
	if (!filename)
		return (-1);
	if (cmd->fd_in != 0)
	{
		close(cmd->fd_in);
		cmd->fd_in = 0;
	}
	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		perror("Debash heredoc");
		free(filename);
		return (-1);
	}
	else
		cmd->fd_in = fd;
	free(filename);
	return (0);
}

int	open_append_outfile(t_cmd *cmd, char *filename)
{
	int		fd;
	char	*error_prompt;

	if (cmd->fd_out != 1)
	{
		close(cmd->fd_out);
		cmd->fd_out = 1;
	}
	fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 00644);
	if (fd == -1)
	{
		error_prompt = ft_concat("Debash: ", filename);
		if (!error_prompt)
		{
			ft_putstr_fd("Debash: memory allocation error\n", 2);
			return (1);
		}
		perror(error_prompt);
		free(error_prompt);
		return (-1);
	}
	else
		cmd->fd_out = fd;
	return (0);
}

// Opens files from redir_list and stores the fd in cmd->fd_in and cmd->fd_out
int	open_list(t_cmd *cmd)
{
	t_list	*link;
	t_redir	*cast;
	int		err;

	link = *cmd->redir_list;
	err = (link != 0);
	while (link && err != -1)
	{
		cast = (t_redir *)link->content;
		if (cast->type == redir_in)
			err = open_infile(cmd, cast->data);
		else if (cast->type == redir_out)
			err = open_outfile(cmd, cast->data);
		else if (cast->type == redir_heredoc)
			err = open_heredoc(cmd);
		else if (cast->type == redir_append)
			err = open_append_outfile(cmd, cast->data);
		link = link->next;
	}
	return (err);
}
