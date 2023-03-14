/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_is_char2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:31:09 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/23 18:59:42 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_space(char c)
{
	int	is_space;

	is_space = 0;
	if (c == ' ')
		is_space = 1;
	return (is_space);
}

int	ft_is_dollar_sign(char c)
{
	int	is_dollar_sign;

	is_dollar_sign = 0;
	if (c == '$')
		is_dollar_sign = 1;
	return (is_dollar_sign);
}

int	ft_is_sign(char c)
{
	int	is_sign;

	is_sign = 0;
	if (c == '<' || c == '>')
		is_sign = 1;
	return (is_sign);
}

int	ft_is_pipe(char c)
{
	int	is_pipe;

	is_pipe = 0;
	if (c == '|')
		is_pipe = 1;
	return (is_pipe);
}

int	ft_is_slash(char c)
{
	int	is_slash;

	is_slash = 0;
	if (c == '/')
		is_slash = 1;
	return (is_slash);
}
