/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:31:09 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/23 18:06:56 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_parser_node *node)
{
	t_lexer_node	*curr;

	curr = node->start->next;
	if (curr == NULL)
		printf("\n");
	else
	{
		if (ft_is_n_option(&curr))
			ft_print_value(curr);
		else
		{
			ft_print_value(curr);
			printf("\n");
		}
	}
	exit (0);
}

int	ft_is_n_option(t_lexer_node **node)
{
	while ((*node) && (*node)->value[0] == '-' && ft_is_all_n((*node)->value))
	{
		(*node) = (*node)->next;
		if (!(*node) || (*node)->value[0] != '-'
			|| !ft_is_all_n((*node)->value))
			return (1);
	}
	return (0);
}

int	ft_is_all_n(char *str)
{
	int	i;

	i = 1;
	if (str[i] != 'n')
		return (0);
	while (str[i] == 'n')
	{
		++i;
		if (str[i] != 'n' && str[i] != '\0')
			return (0);
	}
	return (1);
}

void	ft_print_value(t_lexer_node *curr)
{
	while (curr)
	{
		if (curr->type == OPTION || curr->type == ARGUMENT)
		{	
			printf("%s", curr->value);
			if (curr->next != NULL
				&& (curr->next->type == OPTION
					|| curr->next->type == ARGUMENT))
				printf(" ");
		}
		curr = curr->next;
	}
	return ;
}
