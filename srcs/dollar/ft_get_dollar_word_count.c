/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_get_dollar_word_count.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:57:51 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/23 18:57:52 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_question_mark(char c)
{
	if (c == '?')
		return (1);
	return (0);
}

int	ft_get_dollar_word_count(char *str)
{
	int	i;
	int	word_count;

	word_count = 0;
	i = 0;
	while (str[i] != '\0')
	{
		ft_word_count_in_dollar1(&word_count, &i, str);
		ft_word_count_in_dollar2(&word_count, &i, str);
	}
	return (word_count);
}

void	ft_word_count_in_dollar1(int *word_count, int *i, char *str)
{
	if (ft_is_dollar_token_sign(str[*i]) == 0)
	{
		(*word_count)++;
		while (ft_is_dollar_token_sign(str[*i]) == 0 && str[*i] != '\0')
			(*i)++;
	}
	else if (ft_is_space(str[*i]) == 1)
	{
		(*word_count)++;
		while (ft_is_space(str[*i]) == 1 && str[*i] != '\0')
			(*i)++;
	}
	else if (ft_is_dollar_sign(str[*i]) == 1)
	{
		(*word_count)++;
		(*i)++;
		while (ft_is_dollar_token_sign(str[*i]) == 0 && str[*i] != '\0')
			(*i)++;
	}
}

void	ft_word_count_in_dollar2(int *word_count, int *i, char *str)
{
	if (ft_is_quote(str[*i]) == 1)
	{
		(*word_count)++;
		while (ft_is_quote(str[*i]) == 1 && str[*i] != '\0')
			(*i)++;
	}
	else if (ft_is_equal_sign(str[*i]) == 1)
	{
		(*word_count)++;
		while (ft_is_equal_sign(str[*i]) == 1 && str[*i] != '\0')
			(*i)++;
	}
	else if (ft_is_question_mark(str[*i]) == 1)
	{
		while (ft_is_question_mark(str[*i]) == 1 && str[*i] != '\0')
			(*i)++;
	}
	else if (ft_is_slash(str[*i]) == 1)
	{
		(*word_count)++;
		while (ft_is_slash(str[*i]) == 1 && str[*i] != '\0')
			(*i)++;
	}
}
