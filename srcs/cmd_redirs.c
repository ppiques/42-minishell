/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_redirs.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiques <ppiques@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 15:10:07 by ldesnoye          #+#    #+#             */
/*   Updated: 2022/04/30 18:55:06 by ppiques          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Create t_list element with a pointer to a redir object
int	ft_addredir(char *data, t_redirtype type, t_list **list)
{
	t_redir	*redir;
	t_list	*new;

	redir = malloc(sizeof(t_redir));
	if (!redir)
		return (-1);
	redir->data = data;
	redir->type = type;
	redir->is_ambiguous = 0;
	new = ft_lstnew((void *)redir);
	if (!new)
	{
		free(redir);
		return (-1);
	}
	ft_lstadd_back(list, new);
	return (0);
}

static int	normed_redirs_if(char *s, int i, t_cmd *cmd)
{
	int	result;

	result = -1;
	if (s[i] == '<' && s[i + 1] != '<')
		result = ft_infile(s, i, cmd) + 1;
	else if (s[i] == '<' && s[i + 1] == '<')
		result = ft_heredoc(s, i, cmd) + 2;
	else if (s[i] == '>' && s[i + 1] != '>')
		result = ft_outfile(s, i, cmd) + 1;
	else if (s[i] == '>' && s[i + 1] == '>')
		result = ft_append(s, i, cmd) + 2;
	return (result);
}

// Sets infile, outfile, and heredoc to the corresponding text values
// and append to 1 if needs be
int	redirs(t_cmd *cmd)
{
	int		i;
	int		result;
	char	quoted;

	i = 0;
	quoted = 0;
	while (cmd->data[i])
	{
		if (ft_isredir(cmd->data[i]) && !quoted)
			result = normed_redirs_if(cmd->data, i, cmd);
		else
		{
			if (ft_isquote(cmd->data[i]) && quoted && cmd->data[i] == quoted)
				quoted = 0;
			else if (ft_isquote(cmd->data[i]) && !quoted)
				quoted = cmd->data[i];
			result = 1;
		}
		if (result == -1)
			return (-1);
		i += result;
	}
	return (0);
}

// Remove chevrons from cmd->data
int	remove_chevron(t_cmd *cmd)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	i = 0;
	j = 0;
	len = 0;
	while (cmd->need_to_erase[i] != -1)
		len += !cmd->need_to_erase[i++];
	new_str = malloc((len + 1) * sizeof(char));
	if (!new_str)
		return (-1);
	i = 0;
	while (cmd->data[j])
	{
		if (cmd->need_to_erase[j] == 0)
			new_str[i++] = cmd->data[j];
		j++;
	}
	new_str[i] = 0;
	free(cmd->data);
	cmd->data = new_str;
	return (0);
}
