/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:47:43 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/10 14:47:56 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_pwd(t_all *all)
{
	t_envp_node	*curr;

	curr = all->head_of_envp_list;
	while (curr)
	{
		if (ft_strcmp("PWD", curr->key) == 0)
		{
			printf("%s\n", curr->value);
			exit(0);
		}
		curr = curr->next;
	}
	return ;
}
