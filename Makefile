# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hayelee <hayelee@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/23 20:53:49 by seoyoung          #+#    #+#              #
#    Updated: 2023/03/14 13:04:20 by seshin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

LDFLAGS="-L/usr/local/opt/readline/lib"
CPPFLAGS="-I/usr/local/opt/readline/include"
# LDFLAGS="-L/opt/homebrew/opt/readline/lib"
# CPPFLAGS="-I/opt/homebrew/opt/readline/include"

#LDFLAGS="-L/Users/$(USER)/.brew/opt/readline/lib"
#CPPFLAGS="-I/Users/$(USER)/.brew/opt/readline/include"

#LDFLAGS="-L./readline/lib"
#CPPFLAGS="-I./readline/include"

FILES= etc/minishell.c\
	   etc/ft_handle_signal.c\
	   etc/ft_handle_signal_utils1.c\
	   etc/ft_free.c\
	   etc/ft_free_utils.c\
	   etc/parser.c\
	   etc/ft_handle_input_exception.c\
	   etc/ft_handle_input_exception_utils.c\
	   etc/ft_save.c\
	   etc/ft_save_utils1.c\
	   etc/init.c\
	   etc/make_envp_list.c\
	   etc/ft_open.c\
	   etc/ft_open_utils.c\
	   etc/ft_change_wave_sign.c\
	   lexer/lexer.c\
	   lexer/lexer_utils.c\
	   lexer/lexer_utils2.c\
	   libft/libft_utils.c\
	   libft/libft_utils1.c\
	   libft/libft_utils2.c\
	   libft/libft_utils3.c\
	   check/ft_check_input.c\
	   check/ft_check_type.c\
	   check/ft_check_is_char1.c\
	   check/ft_check_is_char2.c\
	   check/ft_check.c\
	   check/ft_check_utils.c\
	   check/ft_check_utils2.c\
	   check/ft_check_utils3.c\
	   check/ft_check_utils4.c\
	   make_token/ft_make_token.c\
	   make_token/ft_make_token_utils1.c\
	   make_token/ft_make_token_utils2.c\
	   dollar/handle_dollar_sign.c\
	   dollar/ft_make_dollar_token.c\
	   dollar/ft_make_dollar_token_utils.c\
	   dollar/ft_get_dollar_word_count.c\
	   process/ft_process.c\
	   process/ft_process_utils1.c\
	   process/ft_process_utils2.c\
	   process/ft_process_utils3.c\
	   process/ft_process_utils4.c\
	   heredoc/ft_handle_heredoc.c\
	   heredoc/ft_handle_heredoc_utils1.c\
	   heredoc/ft_handle_heredoc_utils2.c\
	   builtin/ft_exit.c\
	   builtin/ft_echo.c\
	   builtin/ft_pwd.c\
	   builtin/ft_cd.c\
	   builtin/ft_cd_utils.c\
	   builtin/ft_env.c\
	   builtin/ft_export.c\
	   builtin/ft_export_utils1.c\
	   builtin/ft_export_utils2.c\
	   builtin/ft_unset.c\

SRCS_DIR = ./srcs/
SRCS = $(addprefix $(SRCS_DIR), $(FILES))
OBJS = $(SRCS:.c=.o)

CC = gcc
CFLAGS = -g -I. -Wall -Wextra -Werror #-fsanitize=address

$(NAME) : $(OBJS)
	$(CC) $(CFLAGS) -lreadline $(LDFLAGS) $(CPPFLAGS) -o $@ $^

.PHONY : all fclean clean re

all : $(NAME)

clean :
	rm -rf $(OBJS)

fclean : clean
	rm -rf $(NAME)

re : fclean all
