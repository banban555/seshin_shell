/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_process_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:57:03 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/30 09:54:32 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_find_cmd_file_path(t_all *all, t_parser_node *node)
{
	char	**path;
	char	*cmd_file;

	path = ft_find_path(all->head_of_envp_list);
	cmd_file = ft_strdup(ft_find_cmd(node->start));
	return (ft_make_cmd_file_path(path, cmd_file));
}

char	**ft_find_path(t_envp_node *head)
{
	t_envp_node	*curr;

	curr = head;
	while (curr)
	{
		if (ft_strcmp(curr->key, "PATH") == 0)
			return (ft_split(curr->value, ':'));
		curr = curr->next;
	}
	return (NULL);
}

char	*ft_find_cmd(t_lexer_node *head)
{
	t_lexer_node	*curr;

	curr = head;
	while (curr)
	{
		if (curr->type == CMD)
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}

char	*ft_make_cmd_file_path(char **path, char *cmd_file)
{
	int			i;
	char		*file_path;
	char		*tmp;
	struct stat	buf;

	i = -1;
	if (path == NULL)
		return (cmd_file);
	while (path[++i])
	{
		tmp = ft_strjoin(path[i], "/");
		file_path = ft_strjoin(tmp, cmd_file);
		free(tmp);
		stat(file_path, &buf);
		if (buf.st_mode & S_IFREG)
		{
			free(cmd_file);
			ft_free_2d_array_except_index(path);
			return (file_path);
		}
		free(file_path);
	}
	ft_free_2d_array_except_index(path);
	return (cmd_file);
}

void	ft_free_2d_array_except_index(char **array)
{
	int	i;

	i = -1;
	while (array[++i])
	{
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	return ;
}
