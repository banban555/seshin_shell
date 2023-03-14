/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_input_exception.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoyoung <seoyoung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:07:07 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/27 14:24:31 by seoyoung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_get_lexer_word_count(char *str)
{
	int				i;
	int				result;
	t_lexer_info	*info;

	info = (t_lexer_info *)ft_calloc(1, sizeof(t_lexer_info));
	i = 0;
	while (str[i] != '\0')
	{
		ft_check_lexer_info(str, info, i);
		ft_move_index(str, info, &i);
	}
	result = info->word_count;
	free(info);
	info = NULL;
	return (result);
}

void	ft_make_lexer_token(char **token, char *str, int word_count)
{
	int				i;
	int				j;
	t_lexer_info	*info;

	i = 0;
	j = 0;
	info = (t_lexer_info *)ft_calloc(1, sizeof(t_lexer_info));
	while (str[i] != '\0')
	{
		ft_check_lexer_info(str, info, i);
		info->start_index = i;
		ft_save_start_end_index(info, &i, str);
		if (j < word_count)
		{
			token[j] = ft_cut_string(str, info->start_index, info->end_index);
			j++;
		}
	}
	free(info);
	info = NULL;
}

void	ft_handle_exception(char *str, t_all *all, t_token_info *info)
{
	int				word_count;
	char			**token;
	t_lexer_node	*node;
	int				i;

	i = 0;
	word_count = ft_get_lexer_word_count(str);
	token = (char **)ft_calloc(sizeof(char *), (word_count + 1));
	ft_make_lexer_token(token, str, word_count);
	i = 0;
	while (token[i] != NULL)
	{
		ft_save(&node, token[i], info, all);
		ft_make_list(all, node);
		i++;
	}
	ft_free_2d_array_except_index(token);
}
