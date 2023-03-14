/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_input_exception_utils.c                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:57:12 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/23 18:57:13 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_only_one_token(char *str)
{
	int				i;
	t_lexer_info	info;

	i = -1;
	while (str[++i])
	{
		if (ft_is_space(str[i]) == 1)
			return (1);
		if (ft_is_sign(str[i]) == 1)
			info.sign_flag = 1;
		else if (ft_is_pipe(str[i]) == 1)
			info.pipe_flag = 1;
		else
			info.alpha_flag = 1;
	}
	if (info.sign_flag == 1 && info.alpha_flag == 1)
		return (0);
	else if (info.sign_flag == 1 && info.pipe_flag == 1)
		return (0);
	else if (info.pipe_flag == 1 && info.alpha_flag == 1)
		return (0);
	else
		return (1);
}

void	ft_check_lexer_info(char *str, t_lexer_info *info, int i)
{
	if (ft_is_sign(str[i]) == 1)
	{
		info->sign_flag = 1;
		info->word_count++;
	}
	else if (ft_is_pipe(str[i]) == 1)
	{
		info->pipe_flag = 1;
		info->word_count++;
	}
	else if (ft_is_sign(str[i]) == 0 || ft_is_pipe(str[i]) == 0)
	{
		info->alpha_flag = 1;
		info->word_count++;
	}
}

void	ft_move_index(char *str, t_lexer_info *info, int *i)
{
	if (info->sign_flag == 1 && info->alpha_flag == 0 && info->pipe_flag == 0)
	{
		while (ft_is_sign(str[*i]) == 1 && ft_is_pipe(str[*i]) == 0
			&& str[*i] != '\0')
			(*i)++;
		info->sign_flag = 0;
	}
	else if (info->alpha_flag == 1 && info->sign_flag == 0
		&& info->pipe_flag == 0)
	{
		while (ft_is_sign(str[*i]) == 0 && ft_is_pipe(str[*i]) == 0
			&& str[*i] != '\0')
			(*i)++;
		info->alpha_flag = 0;
	}
	else if (info->pipe_flag == 1 && info->sign_flag == 0
		&& info->alpha_flag == 0)
	{
		while (ft_is_pipe(str[*i]) == 1 && ft_is_sign(str[*i]) == 0
			&& str[*i] != '\0')
			(*i)++;
		info->pipe_flag = 0;
	}
}

void	ft_save_start_end_index(t_lexer_info *info, int *i, char *str)
{
	if (info->sign_flag == 1 && info->alpha_flag == 0 && info->pipe_flag == 0)
	{
		while (ft_is_sign(str[*i]) && !ft_is_pipe(str[*i]) && str[*i] != '\0')
			(*i)++;
		info->sign_flag = 0;
		info->end_index = (*i) - 1;
	}
	else if (info->alpha_flag && !info->sign_flag && !info->pipe_flag)
	{
		while (!ft_is_sign(str[*i]) && !ft_is_pipe(str[*i]) && str[*i] != '\0')
			(*i)++;
		info->alpha_flag = 0;
		info->end_index = (*i) - 1;
	}
	else if (info->pipe_flag && !info->sign_flag && !info->alpha_flag)
	{
		while (ft_is_pipe(str[*i]) && !ft_is_sign(str[*i]) && str[*i] != '\0')
			(*i)++;
		info->pipe_flag = 0;
		info->end_index = (*i) - 1;
	}
}
