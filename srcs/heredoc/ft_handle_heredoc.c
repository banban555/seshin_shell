/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_heredoc.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:56:11 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/30 10:28:43 by seshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_heredoc(t_all *all, t_parser_node *node)
{
	t_lexer_node	*curr;

	curr = node->start;
	all->num_of_heredoc_type = ft_count_specific_type(node, HEREDOC);
	if (all->num_of_heredoc_type == 0)
		return ;
	else
	{
		all->heredoc_text = ft_save_heredoc_text(node, all);
		if (all->num_of_heredoc_type == 1)
			ft_handle_one_heredoc(all);
		else
		{
			all->heredoc_flag = (int *)ft_calloc(all->num_of_heredoc_type,
					sizeof(int));
			ft_handle_heredocs(all);
		}
		ft_free_heredoc(all);
	}
}

void	ft_handle_one_heredoc(t_all *all)
{
	int		fd;
	char	*input;
	char	**cmd;

	cmd = NULL;
	cmd = ft_make_rm_cmd(cmd);
	fd = open("./temp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		input = readline("> ");
		if (ft_strcmp(input, all->heredoc_text[0]) == 0)
			break ;
		write(fd, input, ft_strlen(input));
		write(fd, "\n", 1);
		free(input);
	}
	ft_close_heredoc(&fd, cmd);
}

void	ft_handle_heredocs(t_all *all)
{
	int		fd;
	char	*input;
	char	**cmd;
	int		i;

	i = 0;
	cmd = NULL;
	cmd = ft_make_rm_cmd(cmd);
	fd = open("./temp", O_CREAT | O_RDWR | O_TRUNC, 0644);
	while (1)
	{
		input = readline("> ");
		ft_check_is_heredoc_text(all, &(all->heredoc_flag), input);
		if (ft_writing_input_is_done(all) == 1)
			break ;
		ft_write_input_in_file(all, &i, fd, input);
		free(input);
	}
	free(input);
	ft_close_heredoc(&fd, cmd);
}

void	ft_close_heredoc(int *fd, char **cmd)
{
	close(*fd);
	*fd = open("./temp", O_RDONLY);
	dup2(*fd, 0);
	close(*fd);
	if (fork() == 0)
		execve("/bin/rm", cmd, NULL);
}

char	**ft_make_rm_cmd(char **cmd)
{
	cmd = (char **)ft_calloc(sizeof(char *), 4);
	cmd[0] = ft_strdup("rm");
	cmd[1] = ft_strdup("-rf");
	cmd[2] = ft_strdup("./temp");
	cmd[3] = NULL;
	return (cmd);
}
