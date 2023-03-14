/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   libft_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hayelee <hayelee@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/23 18:55:48 by hayelee           #+#    #+#             */
/*   Updated: 2021/09/29 16:38:21 by hayelee          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*result;
	size_t	i;
	size_t	j;

	if (!s1 && s2)
		return (ft_strdup(s2));
	else if (!s2 && s1)
		return (ft_strdup(s1));
	i = -1;
	j = 0;
	result = (char *)ft_calloc(sizeof(char),
			(ft_strlen(s1) + ft_strlen(s2) + 1));
	if (!result)
		return (NULL);
	while (++i < ft_strlen(s1))
		result[i] = s1[i];
	while (j < ft_strlen(s2))
		result[i++] = s2[j++];
	result[i] = '\0';
	return (result);
}

int	ft_aredigits(char *s)
{
	int	i;

	i = 0;
	if (s[i] == '+' || s[i] == '-')
		++i;
	while (ft_isdigit(s[i]) > 0)
		++i;
	if (s[i] != '\0')
		return (-1);
	return (0);
}

int	ft_atoi(const char *nptr)
{
	int			i;
	int			symbol;
	long long	numb;

	i = 0;
	while (nptr[i] == ' ' || nptr[i] == '\f' || nptr[i] == '\n'
		|| nptr[i] == '\r' || nptr[i] == '\t' || nptr[i] == '\v')
		i++;
	symbol = 1;
	if (nptr[i] == '-')
		symbol = -1;
	if (nptr[i] == '+' || nptr[i] == '-')
		i++;
	numb = 0;
	while (nptr[i] && nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (symbol * numb > 2147483647)
			return (-1);
		else if (symbol * numb < -2147483648)
			return (0);
		else
			numb = (numb * 10) + (nptr[i] - 48);
		i++;
	}
	return (symbol * numb);
}

static int	ft_len(int nb)
{
	int	size;

	size = 0;
	if (nb == 0)
		return (1);
	if (nb < 0)
	{
		nb = nb * -1;
		size = 1;
	}
	while (nb > 0)
	{
		nb = nb / 10;
		size++;
	}
	return (size);
}

char	*ft_itoa(int n)
{
	char	*str;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = ft_len(n);
	str = ft_calloc(sizeof(char), (len + 1));
	str[len] = '\0';
	if (n == 0)
	{
		str[0] = '0';
		return (str);
	}
	if (n < 0)
	{
		str[0] = '-';
		n = n * -1;
	}
	while (n > 0)
	{
		str[--len] = (n % 10) + '0';
		n = n / 10;
	}
	return (str);
}
