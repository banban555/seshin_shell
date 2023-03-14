/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:13:30 by hayelee           #+#    #+#             */
/*   Updated: 2021/10/01 16:32:05 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_cd_somewhere(t_all *all, char *cmd, char *arg)
{
	struct stat	buf;

	if (chdir(arg) < 0)
	{
		g_global.exit_status = 256;
		stat(arg, &buf);
		if (buf.st_mode & S_IFDIR)
			printf("seha_bash: %s: %s: Permission denied\n", cmd, arg);
		else
			printf("seha_bash: %s: %s: No such file or directory\n", cmd, arg);
		return (-1);
	}
	ft_update_env_value(all);
	return (0);
}

char	*ft_find_env_value(t_envp_node *start, char *env_key)
{
	t_envp_node	*curr;

	curr = start;
	while (curr)
	{
		if (ft_strcmp(curr->key, env_key) == 0)
			return (curr->value);
		curr = curr->next;
	}
	return (NULL);
}

int	ft_change_env_value(t_envp_node *start, char *env_key, char *new_value)
{
	t_envp_node	*curr;

	curr = start;
	while (curr)
	{
		if (ft_strcmp(curr->key, env_key) == 0)
		{
			if (curr->value != NULL)
				free(curr->value);
			curr->value = ft_strdup(new_value);
			return (0);
		}
		curr = curr->next;
	}
	return (-1);
}

char	*ft_cut_string_before_last_character(char *str, char character)
{
	int	i;
	int	index;

	i = -1;
	while (str[++i])
	{
		if (str[i] == character)
			index = i;
	}
	return (ft_cut_string(str, 0, index - 1));
}

void	ft_update_env_value(t_all *all)
{
	char	strbuffer[MAX_PATH];	
	char	*path;
	char	*pwd;
	int		i;

	i = -1;
	while (++i < MAX_PATH)
		strbuffer[i] = 0;
	path = getcwd(strbuffer, MAX_PATH);
	pwd = ft_find_env_value(all->head_of_envp_list, "PWD");
	ft_change_env_value(all->head_of_envp_list, "OLDPWD", pwd);
	ft_change_env_value(all->head_of_envp_list, "PWD", path);
	g_global.exit_status = 0;
	return ;
}
