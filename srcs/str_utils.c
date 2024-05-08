/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiques <ppiques@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 12:14:37 by ldesnoye          #+#    #+#             */
/*   Updated: 2022/04/30 22:45:23 by ppiques          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//joins s1 and s2 with a '/', creating a path
char	*ft_pathjoin(char const *s1, char const *s2)
{
	int		l1;
	int		l2;
	char	*new;

	if (s1 || s2)
	{
		l1 = ft_strlen(s1);
		l2 = ft_strlen(s2);
		new = malloc((l1 + l2 + 2) * sizeof(char));
		if (!new)
			return (NULL);
		ft_strlcpy(new, s1, l1 + 1);
		new[l1] = '/';
		ft_strlcpy(new + l1 + 1, s2, l2 + 1);
		return (new);
	}
	else
		return (NULL);
}

char	*create_absolute_path(char *basename)
{
	char	*buf;
	char	*s;

	buf = getcwd(NULL, 0);
	s = ft_strjoin(buf, "/");
	free(buf);
	buf = ft_strjoin(s, basename);
	free(s);
	return (buf);
}
