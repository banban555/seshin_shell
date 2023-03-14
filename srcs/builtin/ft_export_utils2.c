/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils2.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:31:09 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/23 18:59:03 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_seperate_key_value(t_lexer_node *curr, char **key, char **value)
{
	int	index_of_equal_mark;

	index_of_equal_mark = 0;
	index_of_equal_mark = ft_find_index_of_word(curr->value, '=');
	if (index_of_equal_mark != 0)
	{
		*key = ft_cut_string(curr->value, 0, index_of_equal_mark - 1);
		*value = ft_cut_string(curr->value, index_of_equal_mark + 1,
				(ft_strlen(curr->value) - 1));
	}
	else
	{
		*key = ft_cut_string(curr->value, 0, (ft_strlen(curr->value) - 1));
		*value = NULL;
	}
}

void	ft_save_envp_value(t_envp_node **add, char *key, char *value)
{
	*add = (t_envp_node *)ft_calloc(sizeof(t_envp_node), 1);
	(*add)->key = ft_strdup(key);
	if (value != NULL)
		(*add)->value = ft_strdup(value);
	if (key != NULL)
		free(key);
	if (value != NULL)
		free(value);
}

int	ft_find_env_key(t_all *all, char *key)
{
	t_envp_node	*curr;

	curr = all->head_of_envp_list;
	while (curr != NULL)
	{
		if (ft_strcmp(curr->key, key) == 0)
			return (1);
		curr = curr->next;
	}
	return (0);
}

int	ft_envp_key_is_valid(char *key)
{
	int	i;

	i = 0;
	if (ft_is_alpha(key[i]) == 1 || ft_is_underbar(key[i]) == 1)
	{
		i++;
		while (key[i] != '\0')
		{
			if (ft_is_alpha(key[i]) || ft_is_underbar(key[i])
				|| ft_is_number(key[i]))
				i++;
			else
				return (0);
		}
		return (1);
	}
	return (0);
}

void	ft_save_fd_in_parent_export(t_lexer_node *lexer_curr, int *fd)
{
	while (lexer_curr != NULL)
	{
		if (lexer_curr->type == OUTFILE2 || lexer_curr->type == OUTFILE1)
			*fd = lexer_curr->fd;
		lexer_curr = lexer_curr->next;
	}
	if (*fd == 0)
		*fd = 1;
}
