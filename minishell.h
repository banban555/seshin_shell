/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42seoul.kr>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:07:07 by hayelee           #+#    #+#             */
/*   Updated: 2021/10/01 21:16:55 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h> 
# include <errno.h>
# include <sys/stat.h>
# include <termios.h>
# include <signal.h>
# include <readline/readline.h>
# include <readline/history.h>

typedef struct s_lexer_node
{
	int					type;
	int					fd;
	char				*value;
	struct s_lexer_node	*next;
}	t_lexer_node;

typedef struct s_parser_node
{
	int						num;
	t_lexer_node			*start;
	t_lexer_node			*end;
	struct s_parser_node	*next;
}	t_parser_node;

typedef struct s_envp_node
{
	char					*key;
	char					*value;
	struct s_envp_node		*next;
}	t_envp_node;

typedef struct s_lexer_info
{
	int	sign_flag;
	int	alpha_flag;
	int	pipe_flag;
	int	word_count;
	int	start_index;
	int	end_index;
}	t_lexer_info;

typedef struct s_token_info
{
	int	cmd;
	int	re;
	int	*in_temp;
	int	*out_temp;
	int	*pipe_temp;
}				t_token_info;

typedef struct s_all
{
	t_lexer_node	*head_of_lexer_list;
	t_parser_node	*head_of_parser_list;
	t_envp_node		*head_of_envp_list;
	int				num_of_pipe;
	int				*dollar_sign;
	int				*pipe_sign;
	int				*out_redirect_sign;
	int				*in_redirect_sign;
	int				*tilde_sign;
	int				prev_read_fd;
	int				prev_write_fd;
	int				num_of_heredoc_type;
	char			**heredoc_text;
	int				*heredoc_flag;
	struct termios	main_term;
	struct termios	child_term;
}	t_all;

typedef struct s_global
{
	pid_t			pid;
	int				exit_status;
	int				signal_status;
}	t_global;

/*
** DEFINE_TYPE
*/

# define REDIRECTION 0
# define PIPE 1
# define CMD 2
# define OPTION 3
# define ARGUMENT 4 
# define INFILE 5
# define OUTFILE1 6
# define OUTFILE2 7
# define HEREDOC 8
# define MAX_PATH 260
# define OPEN_MAX 256

/*
** ft_check_input.c
*/
int				ft_check_readline_input(t_all *all, char *input);

/*
** libft_utils.c
*/
int				ft_aredigits(char *s);
int				ft_atoi(const char *nptr);
char			*ft_itoa(int n);
char			*ft_strjoin(char const *s1, char const *s2);

/*
** libft_utils1.c
*/
int				ft_strcmp(const char *s1, const char *s2);
char			*ft_strdup(const char *str);
void			ft_bzero(void *b, size_t n);
void			*ft_calloc(size_t count, size_t size);
size_t			ft_strlen(const char *s);

/*
** libft_utils2.c
*/
char			**ft_split(char const *s, char c);

/*
** libft_utils3.c
*/
void			ft_putchar_fd(char c, int fd);
void			ft_putstr_fd(char *s, int fd);
int				ft_tolower(int c);
int				ft_isdigit(int c);

/*
** ft_check_is_char1.c
*/
int				ft_is_alpha(char c);
int				ft_is_underbar(char c);
int				ft_is_number(char c);
int				ft_is_equal_sign(char c);
int				ft_is_quote(char c);

/*
** ft_check_is_char2.c
*/
int				ft_is_space(char c);
int				ft_is_dollar_sign(char c);
int				ft_is_sign(char c);
int				ft_is_pipe(char c);
int				ft_is_slash(char c);

/*		
** init.c
*/		
void			ft_init_all(t_all *all);
void			ft_init_before_loop(t_all *all, char *envp[]);

/*		
** envp_list.c
*/		
int				ft_find_index_of_word(char *envp, char c);
char			*ft_cut_string(char *envp, int start, int end);
void			ft_init_envp(t_all *all, char **envp);
void			ft_add_envp_node(t_all *all, t_envp_node *node);
void			ft_free_envp(t_all *all);

/*		
** ft_make_token.c
*/		
char			**ft_make_token(char const *str, char delim);
int				ft_count_word_num(char const *str, char delim, int *word_num);
char			**ft_do_split(const char *str, char delim, int word_num,
					char ***split);
void			ft_count_word_len(const char *str, char delim, int *j,
					int *word_len);
void			ft_save_word(char *word, char const *str, int j, int word_len);

/*		
** ft_make_token_utils1.c
*/	
int				ft_check_closed_quote(char const *str, int *i);
int				ft_check_closed_single_quote(char const *str, int *i);
int				ft_check_closed_double_quote(char const *str, int *i);
void			ft_count_during_no_delim(const char *str, int *j,
					int *word_len);
void			ft_count_two_variable(int *a, int *b);

/*		
** ft_make_token_utils2.c
*/	
char			**ft_free_2d_array(char **array, int index);
int				ft_malloc_split(char ***split, int word_num);
int				ft_malloc_split_line(char ***split, int word_len, int i);

/*		
** handle_dollar_sign.c
*/		
int				ft_is_valid_dollar_sign(int **dollar_sign);
void			ft_save_value(char **token, t_envp_node *head, char *key);
int				ft_handle_question_mark(char **token);
char			*ft_change_dollar_to_envp(char **token, int **dollar_sign,
					t_envp_node *head);

/*		
** ft_make_dollar_token.c
*/	
void			ft_make_dollar_token(char **token, char *str);
int				ft_seperate_token1(char *str, int *start_index,
					int *end_index, int *i);
int				ft_seperate_token2(char *str, int *start_index,
					int *end_index, int *i);
int				ft_seperate_token3(char *str, int *start_index,
					int *end_index, int *i);	

/*		
** ft_make_dollar_token.c
*/
char			*ft_join_token(char **token);
int				ft_is_dollar_token_sign(char c);

/*		
** ft_get_dollar_word_count.c
*/
int				ft_get_dollar_word_count(char *str);
void			ft_word_count_in_dollar1(int *word_count, int *i, char *str);
void			ft_word_count_in_dollar2(int *word_count, int *i, char *str);

/*		
** lexer.c
*/		
void			ft_save(t_lexer_node **node,
					char *str, t_token_info *info, t_all *all);
int				is_file(int type);
int				ft_make_lexer(char *input, t_all *all);
void			ft_print_lexer(t_all *all);
void			ft_print_lexer_value(t_lexer_node *curr);

/*		
** lexer_utils.c
*/
int				ft_check_type_of_file(t_token_info *info);
int				ft_check_type_of_sign(t_token_info *info,
					char *str, t_all *all);
int				ft_check_type_of_token(char *str,
					t_token_info *info, t_all *all);
void			ft_add_lexer_node(t_all *all, t_lexer_node *node);

/*		
** lexer_utils2.c
*/
void			ft_make_list(t_all *all, t_lexer_node *node);
void			ft_init_info(t_token_info **info, t_all *all);
void			ft_print_lexer(t_all *all);
void			ft_print_lexer_value(t_lexer_node *curr);

/*		
** handle_input_exception.c
*/
void			ft_handle_exception(char *str, t_all *all, t_token_info *info);
void			ft_make_lexer_token(char **token, char *str, int word_count);
int				ft_get_lexer_word_count(char *str);

/*		
** handle_input_exception_utils.c
*/
int				ft_is_only_one_token(char *str);
void			ft_check_lexer_info(char *str, t_lexer_info *info, int i);
void			ft_move_index(char *str, t_lexer_info *info, int *i);
void			ft_save_start_end_index(t_lexer_info *info, int *i, char *str);

/*	
** ft_check_type.c
*/		
int				ft_str_is_pipe(char *str, int **pipe_sign);
int				ft_is_option(char *str);
int				ft_str_is_redirection(char *str, int **in, int **out);

/*		
** parser.c
*/		
void			ft_make_parser(t_all *all);
void			ft_print_parser(t_all *all);
void			ft_add_parser_node(t_all *all, t_parser_node *node);
void			ft_print_parser_value(t_lexer_node *curr);

/*		
** ft_check.c
*/		
int				ft_check_syntax_error(char *input);
int				ft_check_cmd_type(t_all *all, t_parser_node *node);
int				ft_is_builtin_cmd(t_all *all, t_parser_node *node, char *cmd);
void			ft_check_infile_fd(t_parser_node *node, int *infile_fd);
void			ft_check_outfile_fd(t_parser_node *node, int *outfile_fd);

/*		
** ft_check_utils.c
*/		
int				ft_check_pipe_sign(char *str, int *i);
int				ft_check_redirection_sign(char *str, int *i);
int				ft_check_out_redirection_sign(char *str, int *i);
int				ft_check_in_redirection_sign(char *str, int *i);

/*
** ft_check_utils2.c
*/
void			ft_is_echo(t_parser_node *node, char *lower_cmd);
void			ft_is_cd(t_parser_node *node, char *lower_cmd);
void			ft_is_pwd(t_all *all, char *lower_cmd);
void			ft_is_export(t_all *all, t_parser_node *node, char *lower_cmd);
void			ft_is_unset(t_all *all, t_parser_node *node, char *lower_cmd);

/*
** ft_check_utils3.c
*/
void			ft_is_env(t_all *all, char *lower_cmd);
void			ft_is_exit(t_parser_node *node, char *lower_cmd);
int				ft_check_syntax_error_about_sign(char *input, int *i);
int				ft_check_syntax_error_without_quote(char *input, int *i);

/*
** ft_check_utils3.c
*/
int				ft_check_out_redirection_sign_error(char *str, int *i);
int				ft_check_in_redirection_sign_error(char *str, int *i);
void			ft_count_pipe_number(t_all *all);
int				ft_check_lexer_error(char *input, char *new_input, t_all *all);

/*		
** ft_save.c
*/		
int				ft_save_sign_data(char *input, t_all *all);
int				*ft_init_data(int num_of_data);
int				*ft_check_signs_data(char *s, int num_of_sign, char c);
void			ft_make_sign_data(int **data, int flag,
					int dollar_sign_count);
int				ft_save_specific_sign_data(char *input, int **sign_data,
					char c);

/*		
** ft_save_utils1.c
*/
int				ft_count_specific_char(char *str, char character);

/*		
** ft_process.c
*/		
int				ft_parent_process(t_all *all, t_parser_node *curr);
void			ft_child_process(t_all *all, t_parser_node *node, int *fd);
void			ft_connect_pipe(t_all *all, t_parser_node *node, int *fd);
void			ft_infile_redirect(t_parser_node *node);
int				ft_outfile_redirect(t_parser_node *node);

/*		
** ft_process_utils1.c
*/		
int				ft_builtin_cmd_in_parent_process(t_all *all,
					t_parser_node *curr);
int				ft_check_infile_fd_in_parent_process(t_parser_node *curr);
char			*ft_tolower_cmd(char *cmd);
void			ft_handle_pipe_fd(t_all *all, int read_fd, int write_fd);
t_lexer_node	*ft_find_node_by_type(t_lexer_node *node, int type);

/*		
** ft_process_utils2.c
*/		
char			*ft_find_cmd_file_path(t_all *all, t_parser_node *node);
char			*ft_find_cmd(t_lexer_node *head);
char			**ft_find_path(t_envp_node *head);
char			*ft_make_cmd_file_path(char **path, char *cmd_file);
void			ft_free_2d_array_except_index(char **array);

/*		
** ft_process_utils3.c
*/	
char			**ft_make_param_envp(t_all *all);
char			**ft_make_param_argv(t_parser_node *node);
int				ft_count_envp_list_len(t_envp_node *first_node);
int				ft_count_specific_type(t_parser_node *node, int type);
void			ft_heredoc_piping(int *fd, t_parser_node *node);

/*		
** ft_process_utils4.c
*/	
int				ft_is_builtin_cmd_in_parent(char *cmd);
int				ft_is_valid_builtin_cmd(char *lower_cmd, t_parser_node *curr,
					t_all *all);
void			ft_check_cmd_error_type(t_parser_node *node);

/*		
** ft_open.c
*/		
int				ft_is_out(t_lexer_node *curr);
int				ft_is_outfile(t_lexer_node *curr);
int				ft_is_outredirection(t_lexer_node *curr);
void			ft_open(t_all *all);
int				ft_handle_outfile(t_lexer_node *curr);

/*		
** ft_open_utils.c
*/		
void			ft_delete_lexer_node(t_lexer_node *curr);
void			ft_remove_outfile(t_parser_node *parser_curr,
					int num_of_outredirection);

/*		
** ft_exit.c
*/		
int				ft_exit_in_parent_process(t_all *all, t_parser_node *node);
void			ft_numeric_argument_required(t_all *all, char *str);
void			ft_exit_in_child_process(t_parser_node *node);
t_lexer_node	*ft_find_node_by_two_type(t_lexer_node *node,
					int type_one, int type_two);

/*		
** ft_echo.c
*/		
int				ft_is_all_n(char *str);
int				ft_is_n_option(t_lexer_node **node);
void			ft_print_value(t_lexer_node *curr);
void			ft_echo(t_parser_node *node);

/*		
** ft_handle_heredoc.c
*/
void			ft_handle_heredoc(t_all *all, t_parser_node *node);
void			ft_handle_one_heredoc(t_all *all);
void			ft_handle_heredocs(t_all *all);
void			ft_close_heredoc(int *fd, char **cmd);
char			**ft_make_rm_cmd(char **cmd);

/*
** ft_handle_heredoc_utils1.c
*/
char			**ft_save_heredoc_text(t_parser_node *node, t_all *all);
int				ft_writing_input_is_done(t_all *all);
int				ft_check_is_input_in_heredoc(t_all *all, char *input);
void			ft_count_j(int **heredoc_flag, int *j, int *i, int *j_cnt);
void			ft_count_k(t_all *all, int **heredoc_flag, int *k, int *k_cnt);

/*		
** ft_handle_heredoc_utils2.c
*/
void			ft_check_is_heredoc_text(t_all *all, int **heredoc_flag,
					char *input);
void			ft_write_input_in_file(t_all *all, int *i, int fd, char *input);
void			ft_free_heredoc(t_all *all);

/*		
** ft_pwd.c
*/		
void			ft_pwd(t_all *all);

/*		
** ft_cd.c
*/		
int				ft_cd_in_parent_process(t_all *all, t_parser_node *curr);
void			ft_cd_in_child_process(t_parser_node *curr);
void			ft_cd_home(t_all *all);
void			ft_cd_old_path(t_all *all);
void			ft_cd_current_path(t_all *all);

/*		
** ft_cd.c
*/
int				ft_cd_somewhere(t_all *all, char *cmd, char *arg);
int				ft_change_env_value(t_envp_node *start, char *env_key,
					char *new_value);
char			*ft_find_env_value(t_envp_node *start, char *env_key);
char			*ft_cut_string_before_last_character(char *str, char character);
void			ft_update_env_value(t_all *all);

/*		
** ft_env.c
*/		
int				ft_env(t_all *all);

/*		
** ft_check_is_char.c
*/
int				ft_is_alpha(char c);
int				ft_is_number(char c);
int				ft_is_underbar(char c);
int				ft_is_question_mark(char c);

/*		
** ft_export.c
*/		
int				ft_export_in_parent_process(t_all *all, t_parser_node *node);
int				ft_handle_argument_in_parent_export(t_all *all,
					t_lexer_node *curr);
int				ft_handle_argument_in_child_export(t_lexer_node *curr);
void			ft_export_in_child_process(t_all *all, t_parser_node *node);
int				ft_handle_only_export(t_all *all, t_parser_node *node, int fd);

/*		
** ft_export_utils1.c
*/	
void			ft_print_envp_list_in_export(char *arr, int fd);
void			ft_print_error_in_parent_export(char *key, char *value);
void			ft_print_error_in_child_export(char *key, char *value);
void			ft_sort_envp(char **envp);

/*		
** ft_export_utils2.c
*/
void			ft_seperate_key_value(t_lexer_node *curr, char **key,
					char **value);
void			ft_save_envp_value(t_envp_node **add, char *key, char *value);
int				ft_envp_key_is_valid(char *key);
int				ft_find_env_key(t_all *all, char *key);
void			ft_save_fd_in_parent_export(t_lexer_node *lexer_curr, int *fd);

/*		
** ft_unset.c
*/		
int				ft_unset_in_child_process(t_all *all, t_parser_node *node);
int				ft_handle_argument_in_unset(t_all *all, t_lexer_node *node);
int				ft_unset_in_parent_process(t_all *all, t_parser_node *node);
int				ft_handle_argument_in_child_unset(t_lexer_node *node);
void			ft_delete_envp_node(t_all *all, char *key);

/*		
** ft_handle_signal.c
*/		
void			ft_handle_signal_in_parent(void);
void			ft_sigint_in_parent(int code);

/*		
** ft_handle_signal_utils1.c
*/		
void			ft_handle_signal_in_child(void);
void			ft_sigint_in_child(int code);
void			ft_sigquit_in_child(int code);

/*
** ft_free.c
*/
void			free_lexer_node(t_parser_node *node);
void			free_parser_node(t_all *all);
void			ft_free_all(t_all *all);
void			ft_free_signs1(t_all *all);
void			ft_free_signs2(t_all *all);
void			ft_free_strings(char *first_str, char *second_str);

/*
** ft_change_wave_sign.c
*/
void			ft_change_wave_sign(t_all *all, int **tilde_sign);
char			*ft_change_wave_sign2(t_envp_node *head, char *str);

t_global	g_global;

#endif
