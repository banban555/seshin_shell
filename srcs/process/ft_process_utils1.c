/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_utils1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoyoung <seoyoung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:52:20 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/27 15:38:37 by seoyoung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_builtin_cmd_in_parent_process(t_all *all, t_parser_node *curr)
{
	char			*lower_cmd;
	t_lexer_node	*node;
	int				res;
	int				ret;

	node = ft_find_node_by_type(curr->start, CMD);
	if (node == NULL)
		return (0);
	lower_cmd = ft_tolower_cmd(node->value);
	ret = ft_is_valid_builtin_cmd(lower_cmd, curr, all);
	if (ret <= 0)
		return (ret);
	res = 0;
	if (ft_strcmp("cd", lower_cmd) == 0)
		res = ft_cd_in_parent_process(all, curr);
	else if (ft_strcmp("export", lower_cmd) == 0)
		res = ft_export_in_parent_process(all, curr);
	else if (ft_strcmp("unset", lower_cmd) == 0)
		res = ft_unset_in_parent_process(all, curr);
	else if (ft_strcmp("exit", lower_cmd) == 0)
		res = ft_exit_in_parent_process(all, curr);
	free(lower_cmd);
	return (res);
}

int	ft_check_infile_fd_in_parent_process(t_parser_node *curr)
{
	t_lexer_node	*node;
	int				fd;

	node = curr->start;
	while (node != NULL)
	{
		if (node->type == INFILE)
		{
			fd = open(node->value, O_RDWR);
			if (fd < 0)
			{
				printf("seha_bash: %s: No such file or directory\n",
					node->value);
				g_global.exit_status = 256;
				close(fd);
				return (-1);
			}
			else
				close(fd);
		}
		node = node->next;
	}
	return (0);
}

t_lexer_node	*ft_find_node_by_type(t_lexer_node *node, int type)
{
	t_lexer_node	*curr;

	curr = node;
	while (curr != NULL)
	{
		if (curr->type == type)
			return (curr);
		curr = curr->next;
	}
	return (NULL);
}

char	*ft_tolower_cmd(char *cmd)
{
	char	*lower_cmd;
	int		cmd_len;
	int		i;

	i = -1;
	cmd_len = ft_strlen(cmd);
	lower_cmd = (char *)ft_calloc(sizeof(char), (cmd_len + 1));
	while (++i <= cmd_len)
		lower_cmd[i] = ft_tolower(cmd[i]);
	return (lower_cmd);
}

void	ft_handle_pipe_fd(t_all *all, int read_fd, int write_fd)
{
	all->prev_read_fd = read_fd;
	all->prev_write_fd = write_fd;
	close(write_fd);
}
