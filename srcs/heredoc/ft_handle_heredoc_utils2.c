/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_heredoc_utils2.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoyoung <seoyoung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:56:18 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/27 15:22:12 by seoyoung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_check_is_heredoc_text(t_all *all, int **heredoc_flag, char *input)
{
	int	i;
	int	j;
	int	k;
	int	j_cnt;
	int	k_cnt;

	i = ft_check_is_input_in_heredoc(all, input);
	if (i == all->num_of_heredoc_type - 1
		&& ft_strcmp(input, all->heredoc_text[i]) != 0)
		return ;
	k = i;
	k_cnt = i;
	j = 0;
	j_cnt = 0;
	ft_count_j(heredoc_flag, &j, &i, &j_cnt);
	ft_count_k(all, heredoc_flag, &k, &k_cnt);
	if (j_cnt == j && k_cnt == k)
		(*heredoc_flag)[i] = 1;
}

void	ft_write_input_in_file(t_all *all, int *i, int fd, char *input)
{
	int	last_index;

	last_index = all->num_of_heredoc_type - 1;
	if (all->heredoc_flag[last_index] == 0
		&& all->heredoc_flag[last_index - 1] == 1)
	{
		if (*i != 0)
		{
			write(fd, input, ft_strlen(input));
			write(fd, "\n", 1);
		}
		(*i)++;
	}
}

void	ft_free_heredoc(t_all *all)
{
	int	i;

	i = -1;
	while (all->heredoc_text[++i] != NULL)
	{
		if (all->heredoc_text[i] != NULL)
		{
			free(all->heredoc_text[i]);
			all->heredoc_text[i] = NULL;
		}
	}
	if (all->heredoc_text != NULL)
	{
		free(all->heredoc_text);
		all->heredoc_text = NULL;
	}
	if (all->heredoc_flag != NULL)
	{
		free(all->heredoc_flag);
		all->heredoc_flag = NULL;
	}
}
