/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 18:58:52 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/23 16:49:12 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd_in_parent_process(t_all *all, t_parser_node *curr)
{
	t_lexer_node	*input;
	char			*cmd;

	if (all->num_of_pipe != 0)
		return (0);
	input = ft_find_node_by_type(curr->start, ARGUMENT);
	cmd = ft_find_node_by_type(curr->start, CMD)->value;
	if (input == NULL || input->value[0] == '\0'
		|| ft_strcmp("~", input->value) == 0)
		ft_cd_home(all);
	else if (ft_strcmp(".", input->value) == 0 )
		ft_cd_current_path(all);
	else if (ft_strcmp("..", input->value) == 0)
		ft_cd_old_path(all);
	else
	{
		if (ft_cd_somewhere(all, cmd, input->value) < 0)
			return (-1);
	}
	return (-1);
}

void	ft_cd_in_child_process(t_parser_node *curr)
{
	t_lexer_node	*input;
	char			*cmd;

	input = ft_find_node_by_type(curr->start, ARGUMENT);
	cmd = ft_find_node_by_type(curr->start, CMD)->value;
	if (input == NULL || input->value[0] == '\0'
		|| ft_strcmp("~", input->value) == 0
		|| ft_strcmp(".", input->value) == 0
		|| ft_strcmp("..", input->value) == 0)
		exit(0);
	else
	{
		if (chdir(input->value) < 0)
		{
			ft_putstr_fd("seha_bash: ", 2);
			ft_putstr_fd(cmd, 2);
			ft_putstr_fd(": ", 2);
			ft_putstr_fd(input->value, 2);
			ft_putstr_fd(": No such file or directory\n", 2);
			exit(1);
		}
		exit(0);
	}
	return ;
}

void	ft_cd_home(t_all *all)
{
	char			*path;
	char			*pwd;

	path = ft_find_env_value(all->head_of_envp_list, "HOME");
	pwd = ft_find_env_value(all->head_of_envp_list, "PWD");
	ft_change_env_value(all->head_of_envp_list, "OLDPWD", pwd);
	ft_change_env_value(all->head_of_envp_list, "PWD", path);
	chdir(path);
	g_global.exit_status = 0;
	return ;
}

void	ft_cd_current_path(t_all *all)
{	
	char			*pwd;

	pwd = ft_find_env_value(all->head_of_envp_list, "PWD");
	ft_change_env_value(all->head_of_envp_list, "OLDPWD", pwd);
	g_global.exit_status = 0;
	return ;
}

void	ft_cd_old_path(t_all *all)
{
	char			*path;
	char			*pwd;

	pwd = ft_find_env_value(all->head_of_envp_list, "PWD");
	ft_change_env_value(all->head_of_envp_list, "OLDPWD", pwd);
	path = ft_cut_string_before_last_character(pwd, '/');
	ft_change_env_value(all->head_of_envp_list, "PWD", path);
	chdir(path);
	free(path);
	g_global.exit_status = 0;
	return ;
}
