/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export_utils1.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:31:09 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/23 18:59:01 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_find_index(char *s1, char *s2, int *index)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0')
	{
		if (s1[i] != s2[i])
		{
			*index = i;
			return (1);
		}
		i++;
	}
	return (0);
}

void	ft_sort_envp(char **envp)
{
	int		i;
	int		j;
	int		compare_index;
	char	*temp;

	i = -1;
	compare_index = 0;
	temp = NULL;
	while (envp[++i] != NULL)
	{
		j = i;
		while (envp[++j] != NULL)
		{
			ft_find_index(envp[i], envp[j], &compare_index);
			if (envp[i][compare_index] > envp[j][compare_index])
			{
				temp = envp[i];
				envp[i] = envp[j];
				envp[j] = temp;
			}
		}
	}
}

void	ft_print_envp_list_in_export(char *arr, int fd)
{
	int		j;

	j = -1;
	while (arr[++j] != '\0' && arr[j] != '=')
		write(fd, &arr[j], 1);
	if (arr[j] == '=')
	{
		if (arr[j + 1] == '\0')
		{
			write(fd, "\n", 1);
			return ;
		}
		write(fd, &arr[j++], 1);
		write(fd, "\"", 1);
		while (arr[j] != '\0')
		{
			write(fd, &arr[j], 1);
			j++;
		}
		write(fd, "\"", 1);
		write(fd, "\n", 1);
	}
	return ;
}

void	ft_print_error_in_parent_export(char *key, char *value)
{
	if (value != NULL)
	{	
		printf("seha_bash: export");
		printf(" \'%s=%s': not a vaild identifier\n", key, value);
	}
	else
		printf("seha_bash: export \'%s\': not a vaild identifier\n", key);
	free(key);
	if (value != NULL)
		free(value);
}

void	ft_print_error_in_child_export(char *key, char *value)
{
	ft_putstr_fd("seha_bash: export: \'", 2);
	ft_putstr_fd(key, 2);
	write(2, "\'", 1);
	if (value != NULL)
	{
		write(2, "=", 1);
		ft_putstr_fd(value, 2);
		free(value);
	}
	ft_putstr_fd(": not a valid identifier", 2);
	write(2, "\n", 1);
	free(key);
}
