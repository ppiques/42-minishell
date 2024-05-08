/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_var_handler_utils.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiques <ppiques@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/01 05:44:50 by ppiques           #+#    #+#             */
/*   Updated: 2022/05/01 05:55:19 by ppiques          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	right_ambiguous(char *value)
{
	int	i;
	int	redir;
	int	space;

	i = 0;
	redir = 0;
	space = 0;
	while (value[i])
	{
		if (ft_isredir(value[i]))
			redir = 1;
		if (redir && ft_isspace(value[i]))
			space = 1;
		if (redir && space && !ft_isspace(value[i]))
			return (1);
		i++;
	}
	return (0);
}

int	left_ambiguous(char *value)
{
	int	i;
	int	text;
	int	space;

	i = 0;
	text = 0;
	space = 0;
	while (value[i])
	{
		if (!ft_isspace(value[i]))
			text = 1;
		if (text && ft_isspace(value[i]))
			space = 1;
		if (text && space && ft_isredir(value[i]))
			return (1);
		i++;
	}
	return (0);
}

int	ft_delete(char **addr, int pos)
{
	int		i;
	char	*new;

	new = malloc(ft_strlen(*addr) * sizeof(char));
	if (!new)
		return (-1);
	i = 0;
	while ((*addr)[i])
	{
		if (i > pos)
			new[i - 1] = (*addr)[i];
		else if (i < pos)
			new[i] = (*addr)[i];
		i++;
	}
	new[i - 1] = 0;
	free(*addr);
	*addr = new;
	return (0);
}
