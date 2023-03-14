/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:57:00 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/23 18:57:01 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_outfile(t_lexer_node *curr)
{
	if (curr->type == OUTFILE1 || curr->type == OUTFILE2)
	{
		if (curr->type == OUTFILE1)
			curr->fd = open(curr->value, O_RDWR | O_CREAT | O_TRUNC, 0644);
		else if (curr->type == OUTFILE2)
			curr->fd = open(curr->value, O_RDWR | O_CREAT | O_APPEND, 0644);
		if (curr->fd == -1)
		{
			printf("seha_bash: %s: No such file or directory\n", curr->value);
			return (-1);
		}
	}
	return (0);
}

int	ft_is_outredirection(t_lexer_node *curr)
{
	if (curr->type == REDIRECTION)
	{
		if (ft_strcmp(curr->value, ">") == 0
			|| ft_strcmp(curr->value, ">>") == 0)
			return (1);
	}
	return (0);
}

int	ft_is_outfile(t_lexer_node *curr)
{
	if (curr->type == OUTFILE1 || curr->type == OUTFILE2)
		return (1);
	return (0);
}

int	ft_is_out(t_lexer_node *curr)
{
	if (ft_is_outredirection(curr) == 1)
		return (1);
	if (ft_is_outfile(curr) == 1)
		return (1);
	return (0);
}

void	ft_open(t_all *all)
{
	int				num_of_outredirection;
	t_parser_node	*parser_curr;
	t_lexer_node	*lexer_curr;

	parser_curr = all->head_of_parser_list;
	while (parser_curr != NULL)
	{
		num_of_outredirection = 0;
		lexer_curr = parser_curr->start;
		while (lexer_curr != NULL)
		{
			if (ft_is_outredirection(lexer_curr) == 1)
				num_of_outredirection++;
			ft_handle_outfile(lexer_curr);
			lexer_curr = lexer_curr->next;
		}
		if (num_of_outredirection > 1)
			ft_remove_outfile(parser_curr, num_of_outredirection);
		parser_curr = parser_curr->next;
	}
}
