/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_token.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoyoung <seoyoung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 14:07:07 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/19 16:45:16 by seoyoung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_make_token(char const *str, char delim)
{
	int		word_num;
	char	**split;

	word_num = 0;
	split = 0;
	if (str == NULL)
		return (NULL);
	if (ft_count_word_num(str, delim, &word_num) < 0)
		return (NULL);
	if (ft_malloc_split(&split, word_num) < 0)
		return (NULL);
	return (ft_do_split(str, delim, word_num, &split));
}

int	ft_count_word_num(char const *str, char delim, int *word_num)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == delim)
			++i;
		else
		{
			++(*word_num);
			while (str[i] && str[i] != delim)
			{
				if (str[i] == '\'' || str[i] == '\"')
				{	
					if (ft_check_closed_quote(str, &i) < 0)
						return (-1);
				}
				++i;
			}
		}
	}
	return (*word_num);
}

char	**ft_do_split(const char *str, char delim, int word_num, char ***split)
{
	int	i;
	int	j;
	int	word_len;

	i = -1;
	j = -1;
	word_len = 0;
	while (++i < word_num)
	{
		ft_count_word_len(str, delim, &j, &word_len);
		if (ft_malloc_split_line(split, word_len, i) < 0)
			return (NULL);
		ft_save_word((*split)[i], str, j, word_len);
	}
	(*split)[i] = NULL;
	return (*split);
}

void	ft_count_word_len(const char *str, char delim, int *j, int *word_len)
{
	*word_len = 0;
	while (str[++(*j)])
	{
		while (str[*j] && str[*j] == delim)
			++(*j);
		while (str[*j] && str[(*j)] != delim)
			ft_count_during_no_delim(str, j, word_len);
		if (str[*j] == delim)
			--(*j);
		return ;
	}
	return ;
}

void	ft_save_word(char *word, char const *str, int j, int word_len)
{
	int		i;
	char	quote;

	i = 0;
	word[word_len] = '\0';
	while (word_len > 0)
	{
		if (str[j - i] == '\"' || str[j - i] == '\'')
		{	
			quote = str[(j--) - i];
			while (word_len > 0)
			{
				if (str[j - i] == quote)
				{
					--j;
					break ;
				}
				word[--word_len] = str[j - (i++)];
			}
		}	
		else if (str[j - i] == '\0')
			--j;
		else
			word[--word_len] = str[j - (i++)];
	}
}
