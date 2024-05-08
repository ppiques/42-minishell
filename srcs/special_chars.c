/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   special_chars.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ldesnoye <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/14 14:07:26 by ldesnoye          #+#    #+#             */
/*   Updated: 2022/05/05 14:09:12 by ldesnoye         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isspace(char c)
{
	return (c == ' ' || c == '\t' || c == '\r' || c == '\n' || c == '\v' || \
c == '\f');
}

int	ft_isquote(char c)
{
	return (c == '"' || c == '\'');
}

int	ft_isredir(char c)
{
	return (c == '<' || c == '>');
}

int	ft_ismeta(char c)
{
	return (ft_isquote(c) || ft_isredir(c) || c == '|');
}

// returns true if c is a correct character for a variable name
int	is_varchar(char c)
{
	return (ft_isalnum(c) || c == '_');
}
