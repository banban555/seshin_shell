/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_dollar_token.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:57:39 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/23 18:57:40 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_make_dollar_token(char **token, char *str)
{
	int	i;
	int	j;
	int	start_index;
	int	end_index;

	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (ft_seperate_token1(str, &start_index, &end_index, &i) == 1)
			token[j++] = ft_cut_string(str, start_index, end_index);
		if (ft_seperate_token2(str, &start_index, &end_index, &i) == 1)
			token[j++] = ft_cut_string(str, start_index, end_index);
		if (ft_seperate_token3(str, &start_index, &end_index, &i) == 1)
			token[j++] = ft_cut_string(str, start_index, end_index);
	}
}

int	ft_seperate_token1(char *str, int *start_index,
		int *end_index, int *i)
{
	if (ft_is_dollar_token_sign(str[*i]) == 0)
	{
		*start_index = *i;
		while (ft_is_dollar_token_sign(str[*i]) == 0 && str[*i] != '\0')
			(*i)++;
		*end_index = (*i) - 1;
		return (1);
	}
	else if (ft_is_dollar_sign(str[*i]) == 1)
	{
		*start_index = (*i)++;
		if (ft_is_question_mark(str[*i]) == 1)
		{
			*end_index = (*i)++;
			return (1);
		}
		while (ft_is_dollar_token_sign(str[*i]) == 0 && str[*i] != '\0')
			(*i)++;
		*end_index = (*i) - 1;
		return (1);
	}
	return (0);
}

int	ft_seperate_token2(char *str, int *start_index,
		int *end_index, int *i)
{
	if (ft_is_quote(str[*i]) == 1)
	{
		*start_index = *i;
		while (ft_is_quote(str[*i]) == 1 && str[*i] != '\0')
			(*i)++;
		*end_index = (*i) - 1;
		return (1);
	}
	else if (ft_is_equal_sign(str[*i]) == 1)
	{
		*start_index = *i;
		while (ft_is_equal_sign(str[*i]) == 1 && str[*i] != '\0')
			(*i)++;
		*end_index = (*i) - 1;
		return (1);
	}
	return (0);
}

int	ft_seperate_token3(char *str, int *start_index,
		int *end_index, int *i)
{
	if (ft_is_space(str[*i]) == 1)
	{
		*start_index = *i;
		while (ft_is_space(str[*i]) == 1 && str[*i] != '\0')
			(*i)++;
		*end_index = (*i) - 1;
		return (1);
	}
	else if (ft_is_slash(str[*i]) == 1)
	{
		*start_index = *i;
		while (ft_is_slash(str[*i]) == 1 && str[*i] != '\0')
			(*i)++;
		*end_index = (*i) - 1;
		return (1);
	}
	return (0);
}
