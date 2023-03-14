/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_token_utils1.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:39:25 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/15 14:19:48 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_closed_quote(char const *str, int *i)
{
	if (str[(*i)] == '\'')
	{	
		if (ft_check_closed_single_quote(str, i) < 0)
		{
			printf("seha_bash: syntax error near unexpected token `\'\'\n");
			return (-1);
		}
	}
	else if (str[(*i)] == '\"')
	{	
		if (ft_check_closed_double_quote(str, i) < 0)
		{
			printf("seha_bash: syntax error near unexpected token `\"\'\n");
			return (-1);
		}
	}
	return (0);
}

int	ft_check_closed_single_quote(char const *str, int *i)
{
	++(*i);
	if (str[(*i)] == '\'')
		return (0);
	else
	{
		while (str[(*i)] && str[(*i)] != '\'')
			++(*i);
		if (str[(*i)] != '\0')
			return (0);
	}
	return (-1);
}

int	ft_check_closed_double_quote(char const *str, int *i)
{
	++(*i);
	if (str[(*i)] == '\"')
		return (0);
	else
	{
		while (str[(*i)] && str[(*i)] != '\"')
			++(*i);
		if (str[(*i)] != '\0')
			return (0);
	}
	return (-1);
}

void	ft_count_during_no_delim(const char *str, int *j, int *word_len)
{
	char	quote;

	quote = 0;
	if (str[(*j)] == '\'' || str[(*j)] == '\"')
	{
		quote = str[(*j)];
		++(*j);
		while (str[(*j)] != quote)
			ft_count_two_variable(j, word_len);
		++(*j);
	}
	else
		ft_count_two_variable(j, word_len);
	return ;
}

void	ft_count_two_variable(int *a, int *b)
{
	++(*a);
	++(*b);
	return ;
}
