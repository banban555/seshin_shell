/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:56:05 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/23 18:56:06 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_type_of_file(t_token_info *info)
{
	int	type;

	type = -1;
	if (info->re > 0)
	{
		if (info->re == 1)
			type = INFILE;
		else if (info->re == 2)
			type = OUTFILE1;
		else if (info->re == 3)
			type = HEREDOC;
		else if (info->re == 4)
			type = OUTFILE2;
		info->re = 0;
		return (type);
	}
	return (type);
}

int	ft_check_type_of_sign(t_token_info *info, char *str, t_all *all)
{
	int	type;

	type = -1;
	info->re = ft_str_is_redirection(str,
			&all->in_redirect_sign, &all->out_redirect_sign);
	if (info->re > 0)
	{
		type = REDIRECTION;
		return (type);
	}
	if ((ft_str_is_pipe(str, &all->pipe_sign)) == 1)
	{
		type = PIPE;
		info->cmd = 0;
		return (type);
	}
	return (type);
}

int	ft_check_type_of_token(char *str, t_token_info *info, t_all *all)
{
	int	type;

	type = ft_check_type_of_file(info);
	if (type != -1)
		return (type);
	type = ft_check_type_of_sign(info, str, all);
	if (type != -1)
		return (type);
	if ((info->cmd == 0) && (info->re == 0))
	{
		type = CMD;
		info->cmd = 1;
	}
	else if ((info->cmd == 1) && (info->re == 0)
		&& ft_is_option(str) == 0)
		type = ARGUMENT;
	else if ((info->cmd == 1) && (ft_is_option(str) == 1))
		type = OPTION;
	return (type);
}

void	ft_add_lexer_node(t_all *all, t_lexer_node *node)
{
	t_lexer_node	*curr;

	curr = all->head_of_lexer_list;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = node;
}
