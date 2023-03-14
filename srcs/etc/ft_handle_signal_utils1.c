/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_signal_utils1.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoyoung <seoyoung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/16 22:56:35 by hayelee           #+#    #+#             */
/*   Updated: 2023/03/14 12:21:49 by seshin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_handle_signal_in_child(void)
{
	signal(SIGINT, &ft_sigint_in_child);
	signal(SIGQUIT, &ft_sigquit_in_child);
}

void	ft_sigint_in_child(int code)
{
	code = 0;
	//rl_replace_line("", 0);
	write(2, "\n", 1);
	rl_redisplay();
	g_global.signal_status = SIGINT;
	g_global.exit_status = 130 * 256;
}

void	ft_sigquit_in_child(int code)
{
	code = 0;
	//rl_replace_line("", 0);
	ft_putstr_fd("Quit: 3\n", 2);
	rl_redisplay();
	g_global.signal_status = SIGQUIT;
	g_global.exit_status = 131 * 256;
}
