/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_save.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoyoung <seoyoung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:48:38 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/27 14:11:25 by seoyoung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	*ft_init_data(int num_of_data)
{
	int	*data;

	data = (int *)ft_calloc(sizeof(int), num_of_data);
	if (data == NULL)
		return (NULL);
	return (data);
}

void	ft_make_sign_data(int **data, int flag, int num_of_sign)
{
	int	j;

	j = 0;
	while ((*data)[j] != 0 && j < num_of_sign)
	{
		++j;
	}
	(*data)[j] = flag;
	return ;
}

int	*ft_check_signs_data(char *s, int num_of_sign, char c)
{
	int	i;
	int	flag;
	int	*data;

	data = ft_init_data(num_of_sign);
	i = -1;
	flag = 2;
	while (s[++i])
	{
		if (s[i] == '\'' && flag == 2)
			flag = -1;
		else if (s[i] == '\"' && flag == 2)
			flag = 1;
		else if ((s[i] == '\'' && flag == -1) || (s[i] == '\"' && flag == 1))
			flag = 2;
		else if (s[i] == c)
			ft_make_sign_data(&data, flag, num_of_sign);
	}
	return (data);
}

int	ft_save_sign_data(char *input, t_all *all)
{
	if (ft_save_specific_sign_data(input, &all->dollar_sign, '$') < 0)
		return (-1);
	if (ft_save_specific_sign_data(input, &all->tilde_sign, '~') < 0)
		return (-1);
	if (ft_save_specific_sign_data(input, &all->pipe_sign, '|') < 0)
		return (-1);
	if (ft_save_specific_sign_data(input, &all->out_redirect_sign, '>') < 0)
		return (-1);
	if (ft_save_specific_sign_data(input, &all->in_redirect_sign, '<') < 0)
		return (-1);
	return (0);
}

int	ft_save_specific_sign_data(char *input, int **sign_data, char c)
{
	int	num_of_sign;

	num_of_sign = ft_count_specific_char(input, c);
	if (num_of_sign == 0)
		return (0);
	*sign_data = ft_check_signs_data(input, num_of_sign, c);
	if (*sign_data == NULL)
		return (-1);
	return (0);
}
