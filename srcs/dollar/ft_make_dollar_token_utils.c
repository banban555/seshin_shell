/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_dollar_token_utils.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:57:45 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/23 18:57:46 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_dollar_token_sign(char c)
{
	int	is_dollar_token_sign;

	is_dollar_token_sign = 0;
	if (ft_is_space(c) || ft_is_dollar_sign(c)
		|| ft_is_quote(c) || ft_is_equal_sign(c) || ft_is_slash(c)
		|| ft_is_question_mark(c))
		is_dollar_token_sign = 1;
	return (is_dollar_token_sign);
}

char	*ft_join_token(char **token)
{
	int		i;
	char	*temp;
	char	*result;

	result = NULL;
	temp = NULL;
	i = 0;
	while (token[i] != NULL)
	{
		temp = result;
		result = ft_strjoin(temp, token[i]);
		free(temp);
		temp = NULL;
		i++;
	}
	return (result);
}
