/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesnoye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/15 02:58:52 by ldesnoye          #+#    #+#             */
/*   Updated: 2022/05/15 02:58:59 by ldesnoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*extract_export_name(char *arg)
{
	int		i;
	char	*name;

	i = 0;
	if (ft_isdigit(arg[0]))
		return (NULL);
	while (arg[i] && arg[i] != '=' && arg[i] != '+')
	{
		if (!(is_varchar(arg[i])))
			return (NULL);
		i++;
	}
	if (arg[i] == '+' && arg[i + 1] != '=')
		return (NULL);
	name = ft_substr(arg, 0, i);
	return (name);
}
