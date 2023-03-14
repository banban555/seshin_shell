/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoyoung <seoyoung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 20:07:38 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/19 16:53:08 by seoyoung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_make_list(t_all *all, t_lexer_node *node)
{
	if (all->head_of_lexer_list == NULL)
		all->head_of_lexer_list = node;
	else if (all->head_of_lexer_list != NULL)
		ft_add_lexer_node(all, node);
}

void	ft_init_info(t_token_info **info, t_all *all)
{
	*info = (t_token_info *)ft_calloc(sizeof(t_token_info), 1);
	(*info)->re = 0;
	(*info)->cmd = 0;
	(*info)->in_temp = all->in_redirect_sign;
	(*info)->out_temp = all->out_redirect_sign;
	(*info)->pipe_temp = all->pipe_sign;
}

void	ft_print_lexer(t_all *all)
{
	t_lexer_node	*curr;
	int				j;

	j = 0;
	curr = all->head_of_lexer_list;
	while (curr != NULL)
	{
		printf("node[%d]", j);
		ft_print_lexer_value(curr);
		curr = curr->next;
		j++;
	}
}

void	ft_print_lexer_value(t_lexer_node *curr)
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
