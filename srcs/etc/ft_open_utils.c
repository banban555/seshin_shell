/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_open_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoyoung <seoyoung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 12:10:57 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/27 14:59:48 by seoyoung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delete_lexer_node(t_lexer_node *curr)
{
	t_lexer_node	*delete_node;

	delete_node = curr->next;
	curr->next = curr->next->next;
	delete_node->next = NULL;
	if (ft_is_outfile(delete_node) == 1)
		close(delete_node->fd);
	if (delete_node->value != NULL)
	{
		free(delete_node->value);
		delete_node->value = NULL;
	}
	free(delete_node);
	delete_node = NULL;
}

void	ft_remove_outfile(t_parser_node *parser_curr, int num_of_outredirection)
{
	t_lexer_node	*lexer_curr;

	lexer_curr = parser_curr->start;
	while (lexer_curr->next != NULL)
	{
		while ((ft_is_out(lexer_curr->next) == 1) && (lexer_curr->next != NULL)
			&& (num_of_outredirection > 1))
		{
			if (ft_is_outfile(lexer_curr->next) == 1)
				num_of_outredirection--;
			ft_delete_lexer_node(lexer_curr);
		}
		lexer_curr = lexer_curr->next;
	}
}
