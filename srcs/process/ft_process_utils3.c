/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_utils3.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoyoung <seoyoung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 17:06:30 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/27 15:38:50 by seoyoung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_make_param_argv(t_parser_node *node)
{
	char			**param_argv;
	int				i;
	int				arg_cnt;
	int				opt_cnt;
	t_lexer_node	*curr;

	arg_cnt = ft_count_specific_type(node, ARGUMENT);
	opt_cnt = ft_count_specific_type(node, OPTION);
	param_argv = (char **)ft_calloc(sizeof(char *), (arg_cnt + opt_cnt + 2));
	if (param_argv == NULL)
		return (NULL);
	curr = node->start;
	i = 0;
	while (curr && i < arg_cnt + opt_cnt + 1)
	{
		if (curr->type == CMD || curr->type == ARGUMENT || curr->type == OPTION)
			param_argv[i++] = ft_strdup(curr->value);
		curr = curr->next;
	}
	param_argv[i] = NULL;
	return (param_argv);
}

char	**ft_make_param_envp(t_all *all)
{
	char		**param_envp;
	int			envp_list_len;
	t_envp_node	*curr;
	int			i;
	char		*tmp;

	envp_list_len = ft_count_envp_list_len(all->head_of_envp_list);
	param_envp = (char **)ft_calloc(sizeof(char *), (envp_list_len + 1));
	if (param_envp == NULL)
		return (NULL);
	curr = all->head_of_envp_list;
	i = 0;
	while (curr)
	{
		tmp = ft_strjoin(curr->key, "=");
		param_envp[i++] = ft_strjoin(tmp, curr->value);
		free(tmp);
		curr = curr->next;
	}
	param_envp[i] = NULL;
	return (param_envp);
}

int	ft_count_specific_type(t_parser_node *node, int type)
{
	int				count;
	t_lexer_node	*curr;

	count = 0;
	curr = node->start;
	while (curr)
	{
		if (curr->type == type)
			++count;
		curr = curr->next;
	}
	return (count);
}

int	ft_count_envp_list_len(t_envp_node *first_node)
{
	int			count;
	t_envp_node	*curr;

	count = 0;
	curr = first_node;
	while (curr)
	{
		++count;
		curr = curr->next;
	}
	return (count);
}

void	ft_heredoc_piping(int *fd, t_parser_node *node)
{
	if (node->next != NULL)
	{
		dup2(fd[1], 1);
		close(fd[0]);
	}
	else
	{
		return ;
	}
}
