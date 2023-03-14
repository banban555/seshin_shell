/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:07:07 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/29 13:44:32 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_handle_dollar_sign_input(char **input, t_all *all)
{
	int		word_count;
	char	**token;
	char	*result;
	int		*tmp;

	if (ft_count_specific_char(*input, '$') == 0)
	{
		result = ft_strdup(*input);
		return (result);
	}
	tmp = all->dollar_sign;
	word_count = ft_get_dollar_word_count(*input);
	token = (char **)ft_calloc((word_count + 1), sizeof(char *));
	ft_make_dollar_token(token, *input);
	result = ft_change_dollar_to_envp(token, &all->dollar_sign,
			all->head_of_envp_list);
	ft_free_2d_array_except_index(token);
	all->dollar_sign = tmp;
	return (result);
}

int	ft_run_command(t_all *all, char *input)
{
	int		status;
	int		ret;
	char	*new_input;

	ret = 0;
	ft_save_sign_data(input, all);
	new_input = ft_handle_dollar_sign_input(&input, all);
	if (ft_check_lexer_error(input, new_input, all) == -1)
		return (-1);
	ft_free_strings(new_input, input);
	ft_change_wave_sign(all, &(all->tilde_sign));
	ft_count_pipe_number(all);
	ft_make_parser(all);
	ft_open(all);
	ft_parent_process(all, all->head_of_parser_list);
	while (ret != -1)
	{
		ret = wait(&status);
		if ((ret == g_global.pid) && (g_global.signal_status == 0))
			g_global.exit_status = status;
	}
	return (0);
}

int	ft_check_argc(int argc, char *argv[])
{
	if (argc != 1)
		return (-1);
	argv = NULL;
	return (0);
}

int	main(int argc, char *argv[], char *envp[])
{
	char	*input;
	t_all	all;

	ft_check_argc(argc, argv);
	ft_init_before_loop(&all, envp);
	while (1)
	{
		ft_init_all(&all);
		ft_handle_signal_in_parent();
		input = readline("seha_bash-3.2$ ");
		if (ft_check_readline_input(&all, input) == 1)
			continue ;
		if (ft_check_syntax_error(input) < 0)
			continue ;
		if (ft_run_command(&all, input) < 0)
			continue ;
		ft_free_all(&all);
	}
}
