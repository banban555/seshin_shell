/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:28:19 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/17 11:54:22 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_syntax_error(char *input)
{
	int	i;
	int	flag;

	i = -1;
	flag = 2;
	while (input[++i])
	{
		if (input[i] == '\'' && flag == 2)
			flag = -1;
		else if (input[i] == '\"' && flag == 2)
			flag = 1;
		else if ((input[i] == '\'' && flag == -1)
			|| (input[i] == '\"' && flag == 1))
			flag = 2;
		else if (flag == 2)
		{
			if (ft_check_syntax_error_without_quote(input, &i) < 0)
				return (-1);
		}
	}
	return (0);
}

int	ft_check_cmd_type(t_all *all, t_parser_node *node)
{
	t_lexer_node	*curr;

	curr = node->start;
	while (curr != NULL)
	{
		if (curr->type == CMD)
		{
			if (ft_is_builtin_cmd(all, node, curr->value) < 0)
				return (-1);
			return (0);
		}
		curr = curr->next;
	}
	return (0);
}

int	ft_is_builtin_cmd(t_all *all, t_parser_node *node, char *cmd)
{
	char	*lower_cmd;

	lower_cmd = ft_tolower_cmd(cmd);
	ft_is_echo(node, lower_cmd);
	ft_is_cd(node, lower_cmd);
	ft_is_pwd(all, lower_cmd);
	ft_is_export(all, node, lower_cmd);
	ft_is_unset(all, node, lower_cmd);
	ft_is_env(all, lower_cmd);
	ft_is_exit(node, lower_cmd);
	free(lower_cmd);
	return (-1);
}

void	ft_check_infile_fd(t_parser_node *node, int *infile_fd)
{
	t_lexer_node	*curr;

	*infile_fd = 0;
	curr = node->start;
	while (curr)
	{
		if (curr->type == INFILE)
		{
			*infile_fd = open(curr->value, O_RDONLY);
			if (*infile_fd == -1)
			{
				printf("Error: wrong file name\n");
				exit(-1);
			}
		}
		curr = curr->next;
	}
	if (*infile_fd == 0)
		*infile_fd = -2;
	return ;
}

void	ft_check_outfile_fd(t_parser_node *node, int *outfile_fd)
{
	t_lexer_node	*curr;

	*outfile_fd = 0;
	curr = node->start;
	while (curr)
	{
		if (curr->type == OUTFILE1 || curr->type == OUTFILE2)
			*outfile_fd = curr->fd;
		curr = curr->next;
	}
	if (*outfile_fd == 0)
		*outfile_fd = -2;
	return ;
}
