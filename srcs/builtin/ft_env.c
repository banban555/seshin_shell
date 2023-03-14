/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:31:09 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/23 18:58:26 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_env(t_all *all)
{
	t_envp_node	*curr;

	curr = all->head_of_envp_list;
	while (curr != NULL)
	{
		if (curr->value != NULL)
		{
			printf("%s", curr->key);
			printf("=");
			printf("%s\n", curr->value);
		}
		curr = curr->next;
	}
	exit(0);
}
