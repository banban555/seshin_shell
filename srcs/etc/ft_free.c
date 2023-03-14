/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:57:17 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/30 10:25:40 by seshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_lexer_node(t_parser_node *node)
{
	t_lexer_node	*curr;
	t_lexer_node	*temp;

	curr = node->start;
	if (curr == NULL)
		return ;
	while (curr->next != NULL)
	{
		temp = curr->next;
		free(curr->value);
		free(curr);
		curr = temp;
	}
	free(curr->value);
	free(curr);
}

void	free_parser_node(t_all *all)
{
	t_parser_node	*parser_curr;
	t_parser_node	*parser_temp;

	parser_curr = all->head_of_parser_list;
	while (parser_curr->next != NULL)
	{
		parser_temp = parser_curr->next;
		if (parser_curr != NULL)
		{
			free_lexer_node(parser_curr);
			free(parser_curr);
			parser_curr = NULL;
		}
		parser_curr = parser_temp;
	}
	if (parser_curr != NULL)
	{
		free_lexer_node(parser_curr);
		free(parser_curr);
		parser_curr = NULL;
	}
}

void	ft_free_all(t_all *all)
{
	if (all->head_of_parser_list != NULL)
		free_parser_node(all);
	all->head_of_lexer_list = NULL;
	all->head_of_parser_list = NULL;
	all->num_of_pipe = 0;
	all->prev_read_fd = 0;
	all->prev_write_fd = 0;
	g_global.signal_status = 0;
	ft_free_signs1(all);
	ft_free_signs2(all);
	return ;
}
