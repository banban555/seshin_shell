/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:25:17 by hayelee           #+#    #+#             */
/*   Updated: 2021/10/01 21:15:57 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_parent_process(t_all *all, t_parser_node *curr)
{
	int	fd[2];

	if (curr == NULL || ft_builtin_cmd_in_parent_process(all, curr) < 0)
		return (0);
	if (curr->next != NULL)
		pipe(fd);
	tcsetattr(STDIN_FILENO, TCSASOFT, &(all->child_term));
	ft_handle_signal_in_child();
	g_global.pid = fork();
	if (g_global.pid == 0)
		ft_child_process(all, curr, fd);
	else
	{
		if (curr->next != NULL)
			ft_handle_pipe_fd(all, fd[0], fd[1]);
		ft_parent_process(all, curr->next);
	}
	return (0);
}

void	ft_child_process(t_all *all, t_parser_node *node, int *fd)
{
	char	*file_path;
	char	**param_argv;
	char	**param_envp;

	ft_handle_heredoc(all, node);
	ft_connect_pipe(all, node, fd);
	ft_infile_redirect(node);
	if (ft_outfile_redirect(node) < 0)
		exit(1);
	if (ft_check_cmd_type(all, node) < 0)
	{
		file_path = ft_find_cmd_file_path(all, node);
		param_argv = ft_make_param_argv(node);
		param_envp = ft_make_param_envp(all);
		execve(file_path, param_argv, param_envp);
		free(file_path);
		ft_free_2d_array_except_index(param_argv);
		ft_free_2d_array_except_index(param_envp);
	}
	if (ft_find_node_by_type(node->start, CMD) == NULL)
		exit(0);
	ft_check_cmd_error_type(node);
}

void	ft_infile_redirect(t_parser_node *node)
{
	int	infile_fd;

	ft_check_infile_fd(node, &infile_fd);
	if (infile_fd > 0)
	{
		dup2(infile_fd, 0);
		close(infile_fd);
	}
	return ;
}

int	ft_outfile_redirect(t_parser_node *node)
{
	int	outfile_fd;

	ft_check_outfile_fd(node, &outfile_fd);
	if (outfile_fd > 0)
	{
		dup2(outfile_fd, 1);
		close(outfile_fd);
	}
	if (outfile_fd == -1)
		return (-1);
	return (0);
}

void	ft_connect_pipe(t_all *all, t_parser_node *node, int *fd)
{
	t_parser_node	*curr;

	curr = node;
	if (all->num_of_pipe == 0)
		return ;
	if (all->num_of_heredoc_type != 0)
	{
		ft_heredoc_piping(fd, node);
		return ;
	}
	if (curr->next != NULL)
	{
		dup2(fd[1], 1);
		close(fd[0]);
	}
	if (curr != all->head_of_parser_list)
	{
		dup2(all->prev_read_fd, 0);
		close(all->prev_write_fd);
	}
	return ;
}
