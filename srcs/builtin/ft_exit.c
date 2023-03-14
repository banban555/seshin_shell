/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:33:24 by hayelee           #+#    #+#             */
/*   Updated: 2021/10/02 17:02:32 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_exit_in_parent_process(t_all *all, t_parser_node *node)
{
	t_lexer_node	*first;

	first = ft_find_node_by_two_type(node->start, OPTION, ARGUMENT);
	printf("exit\n");
	if (first == NULL)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &(all->child_term));
		exit(0);
	}
	if (ft_aredigits(first->value) == 0 && first->next == NULL)
	{
		tcsetattr(STDIN_FILENO, TCSANOW, &(all->child_term));
		exit(ft_atoi(first->value));
	}
	if (ft_aredigits(first->value) == 0 && first->next != NULL)
	{
		printf("seha_bash: exit: too many arguments\n");
		g_global.exit_status = 256;
		return (-1);
	}
	if (ft_aredigits(first->value) != 0)
		ft_numeric_argument_required(all, first->value);
	return (0);
}

void	ft_numeric_argument_required(t_all *all, char *str)
{
	printf("seha_bash: exit: %s: numeric argument required\n", str);
	tcsetattr(STDIN_FILENO, TCSANOW, &(all->child_term));
	exit(255);
}

void	ft_exit_in_child_process(t_parser_node *node)
{
	t_lexer_node	*first;

	first = ft_find_node_by_two_type(node->start, OPTION, ARGUMENT);
	if (first == NULL)
		exit(0);
	if (ft_aredigits(first->value) == 0 && first->next == NULL)
		exit(ft_atoi(first->value));
	if (ft_aredigits(first->value) == 0 && first->next != NULL)
	{
		ft_putstr_fd("seha_bash: exit: too many arguments\n", 2);
		exit(1);
	}
	if (ft_aredigits(first->value) != 0)
	{
		ft_putstr_fd("seha_bash: exit: ", 2);
		ft_putstr_fd(first->value, 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		exit(255);
	}
	return ;
}

t_lexer_node	*ft_find_node_by_two_type(t_lexer_node *node,
	int type_one, int type_two)
{
	t_lexer_node	*curr;

	curr = node;
	while (curr != NULL)
	{
		if (curr->type == type_one || curr->type == type_two)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}
