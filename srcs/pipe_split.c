/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_split.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiques <ppiques@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 14:33:01 by ldesnoye          #+#    #+#             */
/*   Updated: 2022/04/30 15:40:44 by ppiques          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	*new_need_to_erase(int len_plus)
{
	int	i;
	int	*need_to_erase;

	i = 0;
	need_to_erase = malloc(len_plus * sizeof(int));
	if (!need_to_erase)
		return (NULL);
	while (i < len_plus)
	{
		need_to_erase[i] = 0;
		i++;
	}
	need_to_erase[len_plus - 1] = -1;
	return (need_to_erase);
}

static	void	free_new_cmd(t_cmd *cmd, char *new, int *need_to_erase)
{
	free(cmd);
	free(new);
	free(need_to_erase);
}

// NEWCMD PREND EN ENTREE LEN+1
static t_cmd	*new_cmd(const char *s, int cmd_len)
{
	t_cmd	*cmd;
	char	*new;
	int		*need_to_erase;

	cmd = malloc(sizeof(t_cmd));
	new = malloc(cmd_len * sizeof(char));
	need_to_erase = new_need_to_erase(cmd_len);
	if (!new || !cmd || !need_to_erase)
	{
		free_new_cmd(cmd, new, need_to_erase);
		return (NULL);
	}
	cmd->redir_list = malloc(sizeof(t_list *));
	if (!cmd->redir_list)
	{
		free_new_cmd(cmd, new, need_to_erase);
		return (NULL);
	}
	*cmd->redir_list = NULL;
	ft_strlcpy(new, s, cmd_len);
	cmd->data = new;
	cmd->need_to_erase = need_to_erase;
	cmd->args = NULL;
	return (cmd);
}

static int	add_cmd(const char *s, int i, t_cmd **tab, int j)
{
	int		pipe;
	t_cmd	*new;
	int		ind;

	pipe = next_pipe(s + i);
	new = new_cmd(s + i, pipe + 1);
	if (!new)
		return (-1);
	new->cmd_ind = j;
	new->fd_in = 0;
	new->fd_out = 1;
	ind = 0;
	while (tab[ind])
		ind++;
	tab[ind] = new;
	tab[ind + 1] = NULL;
	return (pipe);
}

t_cmd	**pipe_split(const char *s, int cmds)
{
	t_cmd	**cmd_tab;
	int		i;
	int		j;
	int		add;

	cmd_tab = malloc((cmds + 1) * sizeof(t_cmd *));
	cmd_tab[0] = NULL;
	i = 0;
	j = 0;
	while (s[i])
	{
		add = add_cmd(s, i, cmd_tab, j);
		i += add;
		if (s[i])
			i++;
		j++;
	}
	if (s[0] && s[i - 1] == '|')
		add = add_cmd(s, i, cmd_tab, j);
	return (cmd_tab);
}
