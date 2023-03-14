/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_token_utils2.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: seoyoung <seoyoung@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/10 16:43:12 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/27 15:39:15 by seoyoung         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**ft_free_2d_array(char **array, int index)
{
	while (--index >= 0)
	{	
		free(array[index]);
		array[index] = NULL;
	}
	free(array);
	array = NULL;
	return (NULL);
}

int	ft_malloc_split(char ***split, int word_num)
{
	*split = (char **)ft_calloc(sizeof(char *), (word_num + 1));
	if (*split == NULL)
		return (-1);
	return (0);
}

int	ft_malloc_split_line(char ***split, int word_len, int i)
{
	(*split)[i] = (char *)ft_calloc(sizeof(char), (word_len + 1));
	if ((*split)[i] == NULL)
	{	
		ft_free_2d_array((*split), i);
		return (-1);
	}
	return (0);
}
