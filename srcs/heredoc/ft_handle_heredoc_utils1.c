/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_heredoc_utils1.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoyoung <seoyoung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:56:23 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/27 15:22:12 by seoyoung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_save_heredoc_text(t_parser_node *node, t_all *all)
{
	t_lexer_node	*curr;
	char			**heredoc_text;
	int				i;

	i = 0;
	curr = node->start;
	heredoc_text = (char **)ft_calloc(all->num_of_heredoc_type + 1,
			sizeof(char *));
	heredoc_text[all->num_of_heredoc_type] = NULL;
	while (curr != NULL || i < all->num_of_heredoc_type)
	{
		if (curr->type == HEREDOC)
		{
			heredoc_text[i] = ft_strdup(curr->value);
			i++;
		}
		curr = curr->next;
	}
	return (heredoc_text);
}

int	ft_writing_input_is_done(t_all *all)
{
	int	i;
	int	last_index;
	int	count;

	i = 0;
	last_index = all->num_of_heredoc_type;
	count = 0;
	while (i < last_index)
	{
		if (all->heredoc_flag[i] == 1)
			count++;
		i++;
	}
	if (count == i)
		return (1);
	return (0);
}

int	ft_check_is_input_in_heredoc(t_all *all, char *input)
{
	int	i;

	i = 0;
	while (i < all->num_of_heredoc_type)
	{
		if (ft_strcmp(input, all->heredoc_text[i]) == 0)
			break ;
		i++;
	}
	if (i == all->num_of_heredoc_type)
		i--;
	return (i);
}

void	ft_count_j(int **heredoc_flag, int *j, int *i, int *j_cnt)
{
	if (*i != 0)
	{
		while (*j <= *i - 1)
		{
			if ((*heredoc_flag)[*j] == 1)
				(*j_cnt)++;
			(*j)++;
		}
	}
}

void	ft_count_k(t_all *all, int **heredoc_flag, int *k, int *k_cnt)
{
	while (*k < all->num_of_heredoc_type)
	{
		if ((*heredoc_flag)[*k] == 0)
			(*k_cnt)++;
		(*k)++;
	}
}
