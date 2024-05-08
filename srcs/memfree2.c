/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memfree2.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiques <ppiques@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 19:08:10 by ldesnoye          #+#    #+#             */
/*   Updated: 2022/04/30 22:43:45 by ppiques          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_redir(void *redir)
{
	t_redir	*cast;

	if (redir)
	{
		cast = (t_redir *)redir;
		free(cast->data);
		cast->data = NULL;
	}
	free(redir);
	redir = NULL;
}

void	free_split_tab(char ***tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free_split(tab[i]);
		i++;
	}
	free(tab);
}

int	cmd_free(t_cmd *cmd, int flag)
{
	free(cmd->data);
	free(cmd->need_to_erase);
	ft_lstclear(cmd->redir_list, free_redir);
	*cmd->redir_list = NULL;
	free(cmd->redir_list);
	if (flag >= 2)
		free_split(cmd->extracted);
	if ((flag == 3 || flag == 4) && cmd->split_extracted)
		free_split_tab(cmd->split_extracted);
	if (flag == 4)
		free(cmd->args);
	if (flag == 5)
	{
		free_split((char **)cmd->split_extracted);
		free_split(cmd->args);
	}
	free(cmd);
	return (-1);
}
