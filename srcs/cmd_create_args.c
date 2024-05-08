/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_create_args.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesnoye <ldesnoye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 15:32:26 by ldesnoye          #+#    #+#             */
/*   Updated: 2022/05/14 15:32:27 by ldesnoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	tab_size(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

static void	malloc_args(t_cmd *cmd)
{
	int	total_size;
	int	i;

	total_size = 0;
	i = 0;
	while (cmd->split_extracted[i])
	{
		total_size += tab_size(cmd->split_extracted[i]);
		i++;
	}
	cmd->args = malloc((total_size + 1) * sizeof(char *));
}

static int	join_args_to_prev(t_cmd *cmd, int i, int j)
{
	char	*stock;

	stock = ft_strjoin(cmd->args[j - 1], cmd->split_extracted[i][0]);
	if (!stock)
		return (-1);
	free(cmd->args[j - 1]);
	free(cmd->split_extracted[i][0]);
	cmd->args[j - 1] = stock;
	return (1);
}

static int	add_args_loop(t_cmd *cmd, int i, int j, int k)
{
	while (cmd->split_extracted[i][k])
	{
		cmd->args[j] = cmd->split_extracted[i][k];
		cmd->args[j + 1] = NULL;
		k++;
		j++;
	}
	return (j);
}

int	create_args(t_cmd *cmd)
{
	int		i;
	int		j;
	int		k;
	char	***split;

	malloc_args(cmd);
	if (!cmd->args)
		return (-1);
	i = 0;
	j = 0;
	split = cmd->split_extracted;
	cmd->args[0] = NULL;
	while (split[i])
	{
		k = 0;
		if (j > 0 && ((split[i - 1][0] && split[i][0])))
		{
			k = join_args_to_prev(cmd, i, j);
			if (k == -1)
				return (-1);
		}
		j = add_args_loop(cmd, i, j, k);
		i++;
	}
	return (0);
}
