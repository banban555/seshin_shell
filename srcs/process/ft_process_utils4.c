/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_utils4.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 14:49:49 by hayelee           #+#    #+#             */
/*   Updated: 2021/10/01 21:49:44 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_is_builtin_cmd_in_parent(char *cmd)
{
	if (ft_strcmp("cd", cmd) == 0
		|| ft_strcmp("export", cmd) == 0
		|| ft_strcmp("unset", cmd) != 0
		|| ft_strcmp("exit", cmd) != 0)
	{
		return (0);
	}
	return (-1);
}

int	ft_is_valid_builtin_cmd(char *lower_cmd, t_parser_node *curr, t_all *all)
{
	if (ft_is_builtin_cmd_in_parent(lower_cmd) < 0)
	{
		free(lower_cmd);
		return (0);
	}
	if (ft_check_infile_fd_in_parent_process(curr) < 0)
	{
		free(lower_cmd);
		return (-1);
	}
	if (all->num_of_pipe != 0)
	{
		free(lower_cmd);
		return (0);
	}
	return (1);
}

void	ft_check_cmd_error_type(t_parser_node *node)
{
	char		*cmd;
	struct stat	buf;
	int			res;

	cmd = ft_find_cmd(node->start);
	res = stat(cmd, &buf);
	ft_putstr_fd("seha_bash: ", 2);
	ft_putstr_fd(cmd, 2);
	if (res == -1
		|| (res == 0 && !(buf.st_mode & S_IXUSR) && cmd[0] != '.'))
	{
		if (cmd[0] == '.')
			ft_putstr_fd(": No such file or directory\n", 2);
		else
			ft_putstr_fd(": command not found\n", 2);
		exit(127);
	}
	else if (buf.st_mode & S_IFDIR)
		ft_putstr_fd(": is a directory\n", 2);
	else if (!(buf.st_mode & S_IXUSR))
		ft_putstr_fd(": Permission denied\n", 2);
	exit(126);
}
