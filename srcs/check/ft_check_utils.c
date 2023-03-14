/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:33:26 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/17 12:09:05 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_pipe_sign(char *str, int *i)
{
	++*i;
	if (str[*i] == '\'' || str[*i] == '\"')
		return (0);
	if (str[*i] == '|' || str[*i] == '\0')
	{
		printf("seha_bash: syntax error near unexpected token `%c'\n", str[*i]);
		return (-1);
	}
	while (str[(*i)++] == ' ')
	{
		if (str[*i] == '\'' || str[*i] == '\"')
			return (0);
		if (str[*i] == '|' || str[*i] == '\0')
		{
			printf("seha_bash: ");
			printf("syntax error near unexpected token `%c'\n", str[*i]);
			return (-1);
		}
	}
	return (0);
}

int	ft_check_redirection_sign(char *str, int *i)
{
	if (str[*i] == '>')
	{
		++(*i);
		if (ft_check_out_redirection_sign(str, i) < 0)
			return (-1);
	}
	else
	{
		++(*i);
		if (ft_check_in_redirection_sign(str, i) < 0)
			return (-1);
	}
	return (0);
}

int	ft_check_out_redirection_sign(char *str, int *i)
{
	int	res;

	if (str[*i] == '\'' || str[*i] == '\"')
		return (0);
	if (str[*i] == '<' || str[*i] == '\0' || str[*i] == '\n')
	{
		printf("seha_bash: syntax error near unexpected token `%c'\n", str[*i]);
		return (-1);
	}
	else if (str[*i] == '>' && str[(*i) + 1] == '>')
	{
		printf("seha_bash: syntax error near unexpected token");
		printf(" `%c%c'\n", str[*i], str[(*i) + 1]);
		return (-1);
	}
	while (str[(*i)++] == ' ')
	{
		res = ft_check_out_redirection_sign_error(str, i);
		if (res <= 0)
			return (res);
	}
	return (0);
}

int	ft_check_in_redirection_sign(char *str, int *i)
{
	int	res;

	if (str[*i] == '\'' || str[*i] == '\"')
		return (0);
	if (str[*i] == '>' || str[*i] == '\0' || str[*i] == '\n')
	{
		printf("seha_bash: syntax error near unexpected token `%c'\n", str[*i]);
		return (-1);
	}
	else if (str[*i] == '<' && ((str[(*i) + 1] == '>')
			|| (str[(*i) + 1] == '<')))
	{
		printf("seha_bash: syntax error near unexpected token");
		printf(" `%c%c'\n", str[*i], str[(*i) + 1]);
		return (-1);
	}
	while (str[(*i)++] == ' ')
	{
		res = ft_check_in_redirection_sign_error(str, i);
		if (res <= 0)
			return (res);
	}
	return (0);
}
