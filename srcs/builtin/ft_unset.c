/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoyoung <seoyoung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:31:09 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/27 15:49:07 by seoyoung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_delete_envp_node(t_all *all, char *key)
{
	t_envp_node	*curr;
	t_envp_node	*delete_node;

	curr = all->head_of_envp_list;
	while (curr->next != NULL)
	{
		if (ft_strcmp(curr->next->key, key) == 0)
		{
			delete_node = curr->next;
			curr->next = delete_node->next;
			delete_node->next = NULL;
			if (delete_node->key != NULL)
				free(delete_node->key);
			if (delete_node->value != NULL)
				free(delete_node->value);
			free(delete_node);
			delete_node = NULL;
		}
		curr = curr->next;
		if (curr == NULL)
			break ;
	}
}

int	ft_handle_argument_in_unset(t_all *all, t_lexer_node *node)
{
	if (ft_envp_key_is_valid(node->value) == 1)
	{
		if (ft_find_env_key(all, node->value) == 1)
		{
			ft_delete_envp_node(all, node->value);
			return (0);
		}
	}
	else
	{
		printf("seha_bash: unset \'%s\': not a vaild identifier\n", node->value);
		return (-1);
	}
	return (0);
}

int	ft_unset_in_parent_process(t_all *all, t_parser_node *node)
{
	t_lexer_node	*lexer_curr;

	g_global.exit_status = 0;
	if (all->num_of_pipe != 0)
		return (0);
	lexer_curr = node->start;
	while (lexer_curr != NULL)
	{
		if ((lexer_curr->type == ARGUMENT) || (lexer_curr->type == OPTION))
		{
			if (ft_handle_argument_in_unset(all, lexer_curr) < 0)
				g_global.exit_status = 256;
		}
		lexer_curr = lexer_curr->next;
	}
	return (-1);
}

int	ft_handle_argument_in_child_unset(t_lexer_node *node)
{
	if (ft_envp_key_is_valid(node->value) == 1)
		return (0);
	else
	{
		printf("seha_bash: unset \'%s\': not a vaild identifier\n", node->value);
		return (-1);
	}
	return (0);
}

int	ft_unset_in_child_process(t_all *all, t_parser_node *node)
{
	t_lexer_node	*lexer_curr;
	int				flag;

	flag = 0;
	lexer_curr = node->start;
	while (lexer_curr != NULL)
	{
		if ((lexer_curr->type == ARGUMENT) || (lexer_curr->type == OPTION))
		{
			if (ft_handle_argument_in_unset(all, lexer_curr) < 0)
				flag = 1;
		}
		lexer_curr = lexer_curr->next;
	}
	if (flag == 1)
		exit(1);
	exit(0);
}
