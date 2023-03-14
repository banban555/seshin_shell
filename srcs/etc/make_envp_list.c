/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_envp_list.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:56:39 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/29 16:46:02 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_find_index_of_word(char *str, char c)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	return (0);
}

char	*ft_cut_string(char *str, int start, int end)
{
	char	*result;
	int		str_len;
	int		i;

	result = NULL;
	str_len = end - start + 1;
	i = 0;
	result = (char *)ft_calloc(sizeof(char), (str_len) + 1);
	while (start <= end)
		result[i++] = str[start++];
	result[i] = '\0';
	return (result);
}

void	ft_add_envp_node(t_all *all, t_envp_node *node)
{
	t_envp_node	*curr;

	curr = all->head_of_envp_list;
	while (curr->next != NULL)
		curr = curr->next;
	curr->next = node;
}

void	ft_init_envp(t_all *all, char **envp)
{
	t_envp_node	*node;
	int			index_of_equal_mark;
	int			i;

	i = 0;
	while (envp[i] != NULL)
	{
		node = (t_envp_node *)ft_calloc(sizeof(t_envp_node), 1);
		index_of_equal_mark = ft_find_index_of_word(envp[i], '=');
		if (index_of_equal_mark != 0)
		{
			node->key = ft_cut_string(envp[i], 0, index_of_equal_mark - 1);
			node->value = ft_cut_string(envp[i], index_of_equal_mark + 1,
					(ft_strlen(envp[i]) - 1));
		}
		if (all->head_of_envp_list == NULL)
			all->head_of_envp_list = node;
		else if (all->head_of_envp_list != NULL)
			ft_add_envp_node(all, node);
		i++;
	}
}

void	ft_free_envp(t_all *all)
{
	t_envp_node	*curr;
	t_envp_node	*temp;

	curr = all->head_of_envp_list;
	while (curr != NULL)
	{
		temp = curr->next;
		if (curr->key != NULL)
			free(curr->key);
		if (curr->value != NULL)
			free(curr->value);
		if (curr != NULL)
		{
			free(curr);
			curr = NULL;
		}
		curr = temp;
	}
}
