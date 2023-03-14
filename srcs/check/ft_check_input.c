/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_check_input.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:31:09 by hayelee           #+#    #+#             */
/*   Updated: 2021/10/02 17:02:50 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_readline_input(t_all *all, char *input)
{
	if (input != NULL && input[0] == '\0')
	{
		free(input);
		input = NULL;
		return (1);
	}
	else if (input == NULL)
	{
		ft_putstr_fd("\x1b[1A", 1);
		ft_putstr_fd("\033[15C", 1);
		write(1, "exit\n", 5);
		tcsetattr(STDIN_FILENO, TCSANOW, &(all->child_term));
		exit(g_global.exit_status);
	}
	else if (input != NULL && input[0] != '\0')
	{
		add_history(input);
		return (0);
	}
	return (0);
}
