/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_type.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:31:09 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/23 18:57:31 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_move_pointer(int **pointer)
{
	(*pointer)++;
	(*pointer)++;
}

int	ft_str_is_redirection2(char *str, int **in, int **out)
{
	if (ft_strcmp(str, "<") == 0 && *(*in) == 2)
	{
		(*in)++;
		return (1);
	}
	else if (ft_strcmp(str, ">") == 0 && *(*out) == 2)
	{
		(*out)++;
		return (2);
	}
	return (0);
}

int	ft_str_is_redirection(char *str, int **in, int **out)
{
	int	i;
	int	*tmp_in;
	int	*tmp_out;
	int	result;

	i = 0;
	tmp_in = *in;
	tmp_out = *out;
	tmp_in++;
	tmp_out++;
	result = ft_str_is_redirection2(str, in, out);
	if (result != 0)
		return (result);
	else if (ft_strcmp(str, "<<") == 0 && *(*in) == 2 && *tmp_in == 2)
	{
		ft_move_pointer(in);
		return (3);
	}
	else if (ft_strcmp(str, ">>") == 0 && *(*out) == 2 && *tmp_out == 2)
	{
		ft_move_pointer(out);
		return (4);
	}
	return (0);
}

int	ft_str_is_pipe(char *str, int **pipe_sign)
{
	int	i;

	i = 0;
	if (str[i] == '|' && *(*pipe_sign) == 2)
	{
		(*pipe_sign)++;
		return (1);
	}
	return (0);
}

int	ft_is_option(char *str)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		return (1);
	return (0);
}
