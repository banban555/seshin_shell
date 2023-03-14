/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_utils4.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 12:04:26 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/29 16:47:35 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_out_redirection_sign_error(char *str, int *i)
{
	if (str[*i] == '\'' || str[*i] == '\"')
		return (0);
	if (str[*i] == '|' || str[*i] == '<' || str[*i] == '>'
		|| str[*i] == '\0' || str[*i] == '\n')
	{
		printf("seha_bash: syntax error near unexpected token");
		printf(" `%c'\n", str[*i]);
		return (-1);
	}
	return (1);
}

int	ft_check_in_redirection_sign_error(char *str, int *i)
{
	if (str[*i] == '\'' || str[*i] == '\"')
		return (0);
	if (str[*i] == '|' || str[*i] == '<'
		|| str[*i] == '>' || str[*i] == '\0' || str[*i] == '\n')
	{
		printf("seha_bash: syntax error near unexpected token");
		printf(" `%c'\n", str[*i]);
		return (-1);
	}
	return (1);
}

void	ft_count_pipe_number(t_all *all)
{
	t_lexer_node	*node;

	node = all->head_of_lexer_list;
	while (node != NULL)
	{
		if (node->type == PIPE)
			++all->num_of_pipe;
		node = node->next;
	}
}

int	ft_check_lexer_error(char *input, char *new_input, t_all *all)
{
	if (ft_make_lexer(new_input, all) < 0)
	{
		free(input);
		ft_free_all(all);
		free(new_input);
		return (-1);
	}
	return (0);
}
