/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 07:57:10 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/29 13:44:29 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_signs1(t_all *all)
{
	if (all->dollar_sign != NULL)
	{
		free(all->dollar_sign);
		all->dollar_sign = NULL;
	}
	if (all->pipe_sign != NULL)
	{
		free(all->pipe_sign);
		all->pipe_sign = NULL;
	}
}

void	ft_free_signs2(t_all *all)
{
	if (all->tilde_sign != NULL)
	{
		free(all->tilde_sign);
		all->tilde_sign = NULL;
	}
	if (all->in_redirect_sign != NULL)
	{
		free(all->in_redirect_sign);
		all->in_redirect_sign = NULL;
	}
	if (all->out_redirect_sign != NULL)
	{
		free(all->out_redirect_sign);
		all->out_redirect_sign = NULL;
	}
}

void	ft_free_strings(char *first_str, char *second_str)
{
	if (first_str != NULL)
		free(first_str);
	if (second_str != NULL)
		free(second_str);
}
