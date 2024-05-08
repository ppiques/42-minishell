/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax_checker.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiques <ppiques@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/29 15:19:28 by ppiques           #+#    #+#             */
/*   Updated: 2022/05/01 06:12:33 by ppiques          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_syntaxerror	redir_error(t_list *ganon)
{
	t_redir	*cast;

	if (ganon)
	{
		cast = (t_redir *)ganon->content;
		if (cast->type == redir_in)
			return (error_infile);
		else if (cast->type == redir_out)
			return (error_outfile);
		else if (cast->type == redir_append)
			return (error_append);
		else
			return (error_heredoc);
	}
	else
		return (error_next);
}

t_syntaxerror	redirlist_checker(t_list **redirs)
{
	t_list	*link;
	t_redir	*cast;

	if (redirs)
	{
		link = *redirs;
		while (link)
		{
			cast = (t_redir *)link->content;
			if (!cast->data[0])
				return (redir_error(link->next));
			else
				link = link->next;
		}
	}
	return (error_ok);
}

t_syntaxerror	pipe_checker(t_cmd **cmd_line, int i)
{
	t_cmd	*cmd;

	cmd = cmd_line[i + 1];
	if (cmd)
		return (error_pipe);
	else if (i == 0)
		return (error_ok);
	else
		return (error_newline);
}

t_syntaxerror	syntax_checker(t_box *box)
{
	int				i;
	t_syntaxerror	ret;

	i = 0;
	while (box->line[i])
	{
		if (!box->line[i]->args[0] && !*box->line[i]->redir_list)
			return (pipe_checker(box->line, i));
		ret = redirlist_checker(box->line[i]->redir_list);
		if (ret == error_next)
		{
			if (box->line[i + 1])
				return (error_pipe);
			else
				return (error_newline);
		}
		else if (ret != error_ok)
			return (ret);
		i++;
	}
	return (ret);
}

void	print_syntaxerror(t_syntaxerror err)
{
	if (err == error_ok)
		return ;
	else if (err == error_pipe)
		ft_putstr_fd("Debash: syntax error near unexpected token `|'\n", 2);
	else if (err == error_newline)
	{
		ft_putstr_fd("Debash: ", 2);
		ft_putstr_fd("syntax error near unexpected token `newline'\n", 2);
	}
	else if (err == error_infile)
		ft_putstr_fd("Debash: syntax error near unexpected token `<'\n", 2);
	else if (err == error_heredoc)
		ft_putstr_fd("Debash: syntax error near unexpected token `<<'\n", 2);
	else if (err == error_outfile)
		ft_putstr_fd("Debash: syntax error near unexpected token `>'\n", 2);
	else if (err == error_append)
		ft_putstr_fd("Debash: syntax error near unexpected token `>>'\n", 2);
}
