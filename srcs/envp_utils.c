/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesnoye <ldesnoye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 12:27:31 by ldesnoye          #+#    #+#             */
/*   Updated: 2022/05/05 12:27:32 by ldesnoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// Free 2 char* and a list pointed to by t_list **list
int	magical_free(char *s1, char *s2, t_list **list)
{
	free(s1);
	free(s2);
	if (list)
		ft_lstclear(list, free_var);
	return (-1);
}

// Returns index of the next '='
int	ind_equal(const char *s)
{
	int	i;

	i = 0;
	while (s[i] && s[i] != '=')
		i++;
	if (!s[i])
		return (-1);
	return (i);
}

// Prints var unless var->name is a special value
void	print_var(void *var)
{
	t_var	*cast;
	char	*name;

	cast = (t_var *)var;
	name = cast->name;
	if (!name || !ft_strncmp("?", name, 2) || !ft_strncmp("", name, 1))
		return ;
	ft_putstr_fd(cast->name, 1);
	ft_putstr_fd("=", 1);
	ft_putendl_fd(cast->value, 1);
}
