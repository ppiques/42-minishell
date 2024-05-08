/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_parser.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesnoye <ldesnoye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 15:30:52 by ldesnoye          #+#    #+#             */
/*   Updated: 2022/05/14 15:30:54 by ldesnoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	mega_split(t_cmd *cmd)
{
	int		i;
	int		len;
	char	*str;

	cmd->split_extracted = malloc((cmd->str_count + 1) * sizeof(char **));
	if (!cmd->split_extracted)
		return (-1);
	cmd->split_extracted[0] = NULL;
	i = 0;
	while (cmd->extracted[i])
	{
		cmd->split_extracted[i] = smart_split(cmd->extracted[i]);
		if (!cmd->split_extracted[i])
			return (-1);
		if (ft_isquote(cmd->extracted[i][0]))
		{
			str = cmd->split_extracted[i][0];
			len = ft_strlen(str);
			cmd->split_extracted[i][0] = ft_substr(str, 1, len - 2);
			free(str);
		}
		i++;
		cmd->split_extracted[i] = NULL;
	}
	return (0);
}

static int	cmd_handler(t_cmd *cmd, t_box *box)
{
	if (redirs(cmd) == -1 || remove_chevron(cmd) == -1)
		return (cmd_free(cmd, 1));
	str_counter(cmd);
	if (str_extractor(cmd, box) == -1)
		return (cmd_free(cmd, 2));
	if (mega_split(cmd) == -1)
		return (cmd_free(cmd, 3));
	if (create_args(cmd) == -1)
		return (cmd_free(cmd, 4));
	return (0);
}

int	parse_cmds(t_box *box)
{
	t_cmd	**tab;
	int		i;
	int		j;

	tab = pipe_split(box->input, box->nb_of_cmds);
	i = 0;
	j = 0;
	while (tab[i])
	{
		if (cmd_handler(tab[i], box) == -1)
		{
			while (j < i)
				cmd_free(tab[j++], 4);
			return (-1);
		}
		i++;
	}
	box->line = tab;
	return (0);
}
