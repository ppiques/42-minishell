/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redirs_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesnoye <ldesnoye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 11:30:53 by ldesnoye          #+#    #+#             */
/*   Updated: 2022/05/05 11:30:54 by ldesnoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Create and add t_redir object of type infile to cmd->redir_list
int	ft_infile(char *s, int i, t_cmd *cmd)
{
	int		c;
	char	*newstr;

	cmd->need_to_erase[i] = 1;
	i++;
	while (ft_isspace(s[i]))
	{
		cmd->need_to_erase[i] = 1;
		i++;
	}
	c = redir_size(s + i);
	need_to_erase_loop(cmd, c, i);
	newstr = ft_substr(s, i, c);
	if (!newstr)
		return (-1);
	if (ft_addredir(newstr, redir_in, cmd->redir_list))
	{
		free(newstr);
		return (-1);
	}
	return (c);
}

// Create and add t_redir object of type heredoc to cmd->redir_list
int	ft_heredoc(char *s, int i, t_cmd *cmd)
{
	int		c;
	char	*newstr;

	cmd->need_to_erase[i] = 1;
	cmd->need_to_erase[i + 1] = 1;
	i += 2;
	while (ft_isspace(s[i]))
	{
		cmd->need_to_erase[i] = 1;
		i++;
	}
	c = redir_size(s + i);
	need_to_erase_loop(cmd, c, i);
	newstr = ft_substr(s, i, c);
	if (!newstr)
		return (-1);
	if (ft_addredir(newstr, redir_heredoc, cmd->redir_list))
	{
		free(newstr);
		return (-1);
	}
	return (c);
}

// Create and add t_redir object of type outfile to cmd->redir_list
int	ft_outfile(char *s, int i, t_cmd *cmd)
{
	int		c;
	char	*newstr;

	cmd->need_to_erase[i] = 1;
	i++;
	while (ft_isspace(s[i]))
	{
		cmd->need_to_erase[i] = 1;
		i++;
	}
	c = redir_size(s + i);
	need_to_erase_loop(cmd, c, i);
	newstr = ft_substr(s, i, c);
	if (!newstr)
		return (-1);
	if (ft_addredir(newstr, redir_out, cmd->redir_list))
	{
		free(newstr);
		return (-1);
	}
	return (c);
}

// Create and add t_redir object of type append to cmd->redir_list
int	ft_append(char *s, int i, t_cmd *cmd)
{
	int		c;
	char	*newstr;

	cmd->need_to_erase[i] = 1;
	cmd->need_to_erase[i + 1] = 1;
	i += 2;
	while (ft_isspace(s[i]))
	{
		cmd->need_to_erase[i] = 1;
		i++;
	}
	c = redir_size(s + i);
	need_to_erase_loop(cmd, c, i);
	newstr = ft_substr(s, i, c);
	if (!newstr)
		return (-1);
	if (ft_addredir(newstr, redir_append, cmd->redir_list))
	{
		free(newstr);
		return (-1);
	}
	return (c);
}
