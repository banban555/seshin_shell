/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_change_wave_sign.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoyoung <seoyoung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:57:26 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/27 14:47:37 by seoyoung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_change_wave_sign(t_all *all, int **tilde_sign)
{
	t_lexer_node	*node;
	int				*tmp;
	t_envp_node		*head;

	tmp = *tilde_sign;
	head = all->head_of_envp_list;
	node = all->head_of_lexer_list;
	while (node != NULL)
	{
		if (ft_strcmp(node->value, "~") == 0 && *(*tilde_sign) == 2)
		{
			free(node->value);
			node->value = ft_strdup(ft_find_env_value(head, "HOME"));
			(*tilde_sign)++;
		}
		if (node->value[0] == '~' && node->value[1] == '/'
			&& *(*tilde_sign) == 2)
		{
			node->value = ft_change_wave_sign2(head, node->value);
			(*tilde_sign)++;
		}
		node = node->next;
	}
	*tilde_sign = tmp;
}

char	*ft_change_wave_sign2(t_envp_node *head, char *str)
{
	char	*tmp;

	tmp = ft_strjoin(ft_find_env_value(head, "HOME"), (str + 1));
	free(str);
	return (tmp);
}
