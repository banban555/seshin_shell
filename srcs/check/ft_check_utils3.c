/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_utils3.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 16:36:39 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/17 11:53:51 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_is_env(t_all *all, char *lower_cmd)
{
	if (ft_strcmp("env", lower_cmd) == 0)
	{
		free(lower_cmd);
		ft_env(all);
	}
}

void	ft_is_exit(t_parser_node *node, char *lower_cmd)
{
	if (ft_strcmp("exit", lower_cmd) == 0)
	{
		free(lower_cmd);
		ft_exit_in_child_process(node);
	}
}

int	ft_check_syntax_error_about_sign(char *input, int *i)
{
	if (input[*i] == '|')
	{	
		if (*i == 0)
		{
			ft_putstr_fd("seha_bash: ", 2);
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
			return (-1);
		}
		if (ft_check_pipe_sign(input, i) < 0)
			return (-1);
	}
	else if ((input[*i] == '<') || (input[*i] == '>'))
	{
		if (ft_check_redirection_sign(input, i) < 0)
			return (-1);
	}
	return (0);
}

int	ft_check_syntax_error_without_quote(char *input, int *i)
{
	int	tmp;

	tmp = *i;
	if (ft_check_syntax_error_about_sign(input, i) < 0)
	{
		g_global.exit_status = 258 * 256;
		free(input);
		return (-1);
	}
	if ((input[*i] != '\'') && (input[*i] != '\"'))
		*i = tmp;
	else
		--(*i);
	return (0);
}
