/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesnoye <ldesnoye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/05 19:51:22 by ldesnoye          #+#    #+#             */
/*   Updated: 2022/05/05 19:51:26 by ldesnoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*heredoc_name(int i)
{
	char	*nb_str;
	char	*filename;
	char	*base;
	int		j;

	base = ".heredoc_tmp_";
	nb_str = ft_itoa(i);
	if (!nb_str)
		return (NULL);
	filename = malloc((ft_strlen(nb_str) + 14) * sizeof(char));
	if (!filename)
	{
		free(nb_str);
		return (NULL);
	}
	ft_strlcpy(filename, base, 14);
	j = 0;
	while (nb_str[j])
	{
		filename[13 + j] = nb_str[j];
		j++;
	}
	filename[13 + j] = 0;
	free(nb_str);
	return (filename);
}

void	eof_warning(char *delim, t_box *box)
{
	size_t	i;
	int		clc;

	ft_putstr_fd("Debash: warning: here-document at line ", 2);
	ft_putnbr_fd(box->history_size, 2);
	ft_putstr_fd(" delimited ", 2);
	ft_putstr_fd("by end-of-file (wanted `", 2);
	clc = ft_isquote(delim[0]);
	if (!clc)
		ft_putstr_fd(delim, 2);
	else
	{
		i = 1;
		while (i < ft_strlen(delim - 2))
		{
			ft_putchar_fd(delim[i], 2);
			i++;
		}
	}
	ft_putstr_fd("')\n", 2);
}

int	heredoc_compare(char *line, char *delim, int quoted)
{
	int	len;

	len = ft_strlen(delim);
	if (quoted)
		return (ft_strncmp(line, delim + 1, len - 2));
	else
		return (ft_strncmp(line, delim, len));
}

int	heredoc_var_expander(char **line_addr, t_box *box, int quoted)
{
	int		i;
	int		add;
	char	*line;

	i = 0;
	line = *line_addr;
	if (quoted)
		return (0);
	while (line[i])
	{
		if (line[i] == '$')
		{
			add = replace_var(line, i, box->env_list, line_addr);
			if (add == -1)
				return (-1);
		}
		else
			add = 1;
		i += add;
	}
	return (0);
}
