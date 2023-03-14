/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_is_char1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:31:09 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/23 18:59:38 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_alpha(char c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	return (0);
}

int	ft_is_underbar(char c)
{
	if (c == '_')
		return (1);
	return (0);
}

int	ft_is_number(char c)
{
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	ft_is_equal_sign(char c)
{
	int	is_equal;

	is_equal = 0;
	if (c == '=')
		is_equal = 1;
	return (is_equal);
}

int	ft_is_quote(char c)
{
	int	is_quote;

	is_quote = 0;
	if (c == '\'' || c == '\"')
		is_quote = 1;
	return (is_quote);
}
