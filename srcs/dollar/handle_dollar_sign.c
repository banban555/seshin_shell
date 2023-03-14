/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_dollar_sign.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:57:33 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/23 18:57:34 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_valid_dollar_sign(int **dollar_sign)
{
	int	is_valid_dollar_sign;

	is_valid_dollar_sign = 0;
	if (*dollar_sign != NULL)
	{
		if (*(*dollar_sign) > 0)
			is_valid_dollar_sign = 1;
	}
	(*dollar_sign)++;
	return (is_valid_dollar_sign);
}

void	ft_save_value(char **token, t_envp_node *head, char *key)
{
	t_envp_node	*curr;

	curr = head;
	free(*token);
	(*token) = NULL;
	while (curr != NULL)
	{
		if (ft_strcmp(key, curr->key) == 0)
			*token = ft_strdup(curr->value);
		curr = curr->next;
	}
	if (*token == NULL)
		*token = ft_strdup("");
}

int	ft_handle_question_mark(char **token)
{
	if (ft_strcmp(*token, "$?") == 0)
	{
		free(*token);
		*token = NULL;
		*token = ft_itoa(g_global.exit_status);
		return (0);
	}
	else
		return (1);
}

char	*ft_change_dollar_to_envp(char **token, int **dollar_sign,
			t_envp_node *head)
{
	int		i;
	char	*key;

	i = -1;
	while (token[++i] != NULL)
	{
		if (ft_count_specific_char(token[i], '$'))
		{
			if (ft_strcmp(token[i], "$") == 0 || ft_strcmp(token[i], "$~") == 0)
				continue ;
			if (ft_handle_question_mark(&token[i]) == 0)
				continue ;
			if (ft_is_valid_dollar_sign(dollar_sign) > 0)
			{
				key = ft_cut_string(token[i], 1, (ft_strlen(token[i]) - 1));
				ft_save_value(&token[i], head, key);
				free(key);
			}
		}
	}
	return (ft_join_token(token));
}
