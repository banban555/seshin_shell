/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_signal.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/09 19:51:59 by hayelee           #+#    #+#             */
/*   Updated: 2023/03/14 12:20:54 by seshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_signal_in_parent(void)
{
	signal(SIGINT, &ft_sigint_in_parent);
	signal(SIGQUIT, SIG_IGN);
}

void	ft_sigint_in_parent(int code)
{
	if (code == SIGINT)
	{
		ft_putstr_fd("\n", 1);
		//rl_replace_line("", 0);
		rl_on_new_line();
		rl_redisplay();
		g_global.exit_status = 1;
	}
}
