/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:31:09 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/23 18:59:37 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_export_in_parent_process(t_all *all, t_parser_node *node)
{
	t_lexer_node	*lexer_curr;
	int				fd;

	fd = 0;
	lexer_curr = node->start;
	g_global.exit_status = 0;
	if (all->num_of_pipe != 0)
		return (0);
	ft_save_fd_in_parent_export(lexer_curr, &fd);
	if (ft_handle_only_export(all, node, fd) == 0)
		return (-1);
	while (lexer_curr != NULL)
	{
		if ((lexer_curr->type == ARGUMENT) || (lexer_curr->type == OPTION))
			ft_handle_argument_in_parent_export(all, lexer_curr);
		lexer_curr = lexer_curr->next;
	}
	return (-1);
}

int	ft_handle_argument_in_parent_export(t_all *all, t_lexer_node *curr)
{
	char		*key;
	char		*value;
	t_envp_node	*add;

	ft_seperate_key_value(curr, &key, &value);
	if (ft_find_env_key(all, key) == 1)
	{
		if (value != NULL)
		{
			ft_change_env_value(all->head_of_envp_list, key, value);
			free(value);
		}
		free(key);
		return (0);
	}
	if (ft_envp_key_is_valid(key) == 0)
	{
		ft_print_error_in_parent_export(key, value);
		g_global.exit_status = 256;
		return (-1);
	}
	ft_save_envp_value(&add, key, value);
	ft_add_envp_node(all, add);
	return (0);
}

void	ft_export_in_child_process(t_all *all, t_parser_node *node)
{
	t_lexer_node	*lexer_curr;
	int				flag;

	flag = 0;
	lexer_curr = node->start;
	if (ft_handle_only_export(all, node, 1) == 0)
		exit(0);
	while (lexer_curr != NULL)
	{
		if ((lexer_curr->type == ARGUMENT) || (lexer_curr->type == OPTION))
		{
			if (ft_handle_argument_in_child_export(lexer_curr) < 0)
				flag = 1;
		}
		lexer_curr = lexer_curr->next;
	}
	if (flag == 1)
		exit(256);
	exit(0);
}

int	ft_handle_argument_in_child_export(t_lexer_node *curr)
{
	char	*key;
	char	*value;

	key = NULL;
	value = NULL;
	ft_seperate_key_value(curr, &key, &value);
	if (ft_envp_key_is_valid(key) == 0)
	{
		ft_print_error_in_child_export(key, value);
		return (-1);
	}
	if (value != NULL)
		free(value);
	if (key != NULL)
		free(key);
	return (0);
}

int	ft_handle_only_export(t_all *all, t_parser_node *node, int fd)
{
	char	**sorted_envp;
	int		i;

	i = -1;
	if (ft_count_specific_type(node, ARGUMENT) == 0
		&& ft_count_specific_type(node, OPTION) == 0)
	{
		sorted_envp = ft_make_param_envp(all);
		ft_sort_envp(sorted_envp);
		while (sorted_envp[++i] != NULL)
		{
			ft_putstr_fd("declare -x ", fd);
			ft_print_envp_list_in_export(sorted_envp[i], fd);
		}
		ft_free_2d_array_except_index(sorted_envp);
	}
	return (-1);
}
