/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesnoye <ldesnoye@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/26 15:07:27 by ldesnoye          #+#    #+#             */
/*   Updated: 2022/04/26 15:07:30 by ldesnoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*cut_str(const char *haystack, const char *needle)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	if (needle[i] == '\0')
		return ((char *)haystack);
	while (haystack[i])
	{
		j = 0;
		if (haystack[i] == needle[j])
		{
			while (haystack[i + j] == needle[j])
			{
				j++;
				if (needle[j] == '\0')
					return ((char *)haystack + i + j);
			}
		}
		i++;
	}
	return (0);
}

char	*get_prompt(char *name)
{
	char	*user;
	char	*prompt;
	char	*buffer;
	char	*path;

	path = getcwd(NULL, 0);
	user = getenv("USER");
	prompt = ft_strjoin(name, "~");
	buffer = ft_strjoin(prompt, cut_str(path, user));
	free(prompt);
	prompt = ft_strjoin(buffer, "$ ");
	free(buffer);
	free(path);
	return (prompt);
}

char	*get_hostname(void)
{
	char	*prompt;
	char	*buffer;
	char	nb[100];
	int		i;
	int		j;

	i = -1;
	j = 0;
	buffer = getenv("SESSION_MANAGER");
	while (buffer[i] != '/')
		i++;
	while (buffer[++i] != '.')
		nb[j++] = buffer[i];
	nb[j] = ':';
	nb[j + 1] = 0;
	prompt = ft_strjoin("", getenv("USER"));
	buffer = ft_strjoin(prompt, "@");
	free(prompt);
	prompt = ft_strjoin(buffer, nb);
	free(buffer);
	return (prompt);
}
