/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_utils2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesnoye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/14 02:36:07 by ldesnoye          #+#    #+#             */
/*   Updated: 2022/05/14 02:36:11 by ldesnoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	special_write(int fd, char *line)
{
	char	c;

	c = '\n';
	if (write(fd, line, ft_strlen(line)) == -1)
		return (-1);
	if (write(fd, &c, 1) == -1)
		return (-1);
	return (0);
}

int	heredoc_freeonwriteerror(char *line, int fd)
{
	free(line);
	close(fd);
	return (-1);
}
