/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:56:47 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/29 13:36:44 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_before_loop(t_all *all, char *envp[])
{
	g_global.exit_status = 0;
	tcgetattr(STDIN_FILENO, &(all->main_term));
	tcgetattr(STDIN_FILENO, &(all->child_term));
	all->main_term.c_lflag &= ~ECHOCTL;
	all->head_of_envp_list = NULL;
	ft_init_envp(all, envp);
}

void	ft_init_all(t_all *all)
{
	all->head_of_lexer_list = NULL;
	all->head_of_parser_list = NULL;
	all->num_of_pipe = 0;
	all->dollar_sign = NULL;
	all->pipe_sign = NULL;
	all->out_redirect_sign = NULL;
	all->in_redirect_sign = NULL;
	all->tilde_sign = NULL;
	all->prev_read_fd = 0;
	all->prev_write_fd = 0;
	all->num_of_heredoc_type = 0;
	all->heredoc_text = NULL;
	all->heredoc_flag = NULL;
	g_global.pid = -2;
	g_global.signal_status = 0;
	g_global.exit_status = g_global.exit_status / 256;
	tcsetattr(STDIN_FILENO, TCSANOW, &(all->main_term));
}
