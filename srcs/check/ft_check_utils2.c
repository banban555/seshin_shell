/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/14 16:31:37 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/16 22:55:01 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_is_echo(t_parser_node *node, char *lower_cmd)
{
	if (ft_strcmp("echo", lower_cmd) == 0)
	{
		free(lower_cmd);
		ft_echo(node);
	}
}

void	ft_is_cd(t_parser_node *node, char *lower_cmd)
{
	if (ft_strcmp("cd", lower_cmd) == 0)
	{
		free(lower_cmd);
		ft_cd_in_child_process(node);
	}
}

void	ft_is_pwd(t_all *all, char *lower_cmd)
{
	if (ft_strcmp("pwd", lower_cmd) == 0)
	{
		free(lower_cmd);
		ft_pwd(all);
	}
}

void	ft_is_export(t_all *all, t_parser_node *node, char *lower_cmd)
{
	if (ft_strcmp("export", lower_cmd) == 0)
	{
		free(lower_cmd);
		ft_export_in_child_process(all, node);
	}
}

void	ft_is_unset(t_all *all, t_parser_node *node, char *lower_cmd)
{
	if (ft_strcmp("unset", lower_cmd) == 0)
	{
		free(lower_cmd);
		ft_unset_in_child_process(all, node);
	}
}
