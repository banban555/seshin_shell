/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:56:31 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/29 16:44:56 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_print_parser(t_all *all)
{
	t_parser_node	*parser_curr;
	t_lexer_node	*curr;
	int				i;
	int				j;

	i = 0;
	parser_curr = all->head_of_parser_list;
	while (parser_curr != NULL)
	{
		curr = parser_curr->start;
		printf("\033[1;31mparser_node[%d]\n\033[0m", i);
		j = 0;
		while (curr != NULL)
		{
			printf("node[%d]", j);
			ft_print_parser_value(curr);
			curr = curr->next;
			j++;
		}
		parser_curr = parser_curr->next;
		i++;
	}
}

void	ft_print_parser_value(t_lexer_node *curr)
{
	if (curr->type == REDIRECTION)
		printf("{ type : %s, value : %s }\n", "REDIRECTION", curr->value);
	else if (curr->type == INFILE)
		printf("{ type : %s, value : %s }\n", "INFILE", curr->value);
	else if (curr->type == OUTFILE1)
		printf("{ type : %s, value : %s }\n", "OUTFILE1", curr->value);
	else if (curr->type == OUTFILE2)
		printf("{ type : %s, value : %s }\n", "OUTFILE2", curr->value);
	else if (curr->type == HEREDOC)
		printf("{ type : %s, value : %s }\n", "HEREDOC", curr->value);
	else if (curr->type == PIPE)
		printf("{ type : %s, value : %s }\n", "PIPE", curr->value);
	else if (curr->type == CMD)
		printf("{ type : %s, value : %s }\n", "CMD", curr->value);
	else if (curr->type == OPTION)
		printf("{ type : %s, value : %s }\n", "OPTION", curr->value);
	else if (curr->type == ARGUMENT)
		printf("{ type : %s, value : %s }\n", "ARGUMENT", curr->value);
}

void	ft_add_parser_node(t_all *all, t_parser_node *node)
{
	t_parser_node	*curr;

	curr = all->head_of_parser_list;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = node;
}

void	ft_node(t_all *all, int i, t_parser_node **node, t_lexer_node **curr)
{
	if (i == all->num_of_pipe)
	{
		(*node)->start = *curr;
		while (*curr != NULL)
			*curr = (*curr)->next;
		(*node)->end = *curr;
	}
	else
	{
		(*node)->start = *curr;
		while ((*curr)->type != PIPE)
			*curr = (*curr)->next;
		(*node)->end = *curr;
		*curr = (*curr)->next;
		(*node)->end->next = NULL;
	}
}

void	ft_make_parser(t_all *all)
{
	t_lexer_node	*curr;
	t_parser_node	*node;
	int				i;

	i = 0;
	curr = all->head_of_lexer_list;
	while (i <= all->num_of_pipe)
	{
		node = (t_parser_node *)ft_calloc(sizeof(t_parser_node), 1);
		node->num = i;
		ft_node(all, i, &node, &curr);
		if (all->head_of_parser_list == NULL)
			all->head_of_parser_list = node;
		else
			ft_add_parser_node(all, node);
		i++;
	}
}
