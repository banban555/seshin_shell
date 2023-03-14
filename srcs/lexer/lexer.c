/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:55:58 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/23 18:55:59 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_save(t_lexer_node **node, char *str, t_token_info *info, t_all *all)
{
	*node = (t_lexer_node *)ft_calloc(sizeof(t_lexer_node), 1);
	(*node)->type = ft_check_type_of_token(str, info, all);
	(*node)->value = ft_strdup(str);
}

int	is_file(int type)
{
	if (type == INFILE
		|| type == OUTFILE1
		|| type == OUTFILE2
		|| type == HEREDOC)
		return (1);
	return (0);
}

void	ft_save_temp(t_all *all, t_token_info *info, char **str)
{
	all->in_redirect_sign = info->in_temp;
	all->out_redirect_sign = info->out_temp;
	all->pipe_sign = info->pipe_temp;
	ft_free_2d_array_except_index(str);
	str = NULL;
	free(info);
	info = NULL;
}

int	ft_make_lexer(char *input, t_all *all)
{
	char			**str;
	int				i;
	t_token_info	*info;
	t_lexer_node	*node;

	i = -1;
	node = NULL;
	str = ft_make_token(input, ' ');
	if (str == NULL)
		return (-1);
	ft_init_info(&info, all);
	while (str[++i] != NULL)
	{
		if (ft_is_only_one_token(str[i]) == 0)
			ft_handle_exception(str[i], all, info);
		else
		{
			ft_save(&node, str[i], info, all);
			ft_make_list(all, node);
		}
	}
	ft_save_temp(all, info, str);
	return (0);
}
