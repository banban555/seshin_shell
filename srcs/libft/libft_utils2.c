/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoyoung <seoyoung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 10:00:23 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/27 15:39:00 by seoyoung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	**ft_freeall1(char **array, size_t i)
{
	while (i--)
	{
		free(array[i]);
		array[i] = NULL;
	}
	free(array);
	array = NULL;
	return (NULL);
}

static int	ft_word_num1(char const *s, char c)
{
	int	i;
	int	cnt;

	i = 0;
	cnt = 0;
	while (s[i])
	{
		if (s[i] == c)
			i++;
		else
		{
			cnt++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (cnt);
}

static char	*ft_make_word1(char *word, char const *s, int k, int word_len)
{
	int	i;

	i = 0;
	while (word_len > 0)
		word[i++] = s[k - word_len--];
	word[i] = '\0';
	return (word);
}

static char	**ft_do_split1(char **array, char const *s, char c, int word_num)
{
	int	i;
	int	k;
	int	word_len;

	i = 0;
	k = 0;
	word_len = 0;
	while (s[k] && i < word_num)
	{
		while (s[k] && s[k] == c)
			k++;
		while (s[k] && s[k] != c)
		{
			k++;
			word_len++;
		}
		array[i] = (char *)ft_calloc(sizeof(char), (word_len + 1));
		if (!array[i])
			return (ft_freeall1(array, i));
		ft_make_word1(array[i], s, k, word_len);
		word_len = 0;
		i++;
	}
	array[i] = 0;
	return (array);
}

char	**ft_split(char const *s, char c)
{
	int		word_num;
	char	**array;

	if (s == NULL)
		return (NULL);
	word_num = ft_word_num1(s, c);
	array = (char **)ft_calloc(sizeof(char *), (word_num + 1));
	if (!array)
		return (NULL);
	ft_do_split1(array, s, c, word_num);
	return (array);
}
