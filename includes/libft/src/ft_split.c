/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 12:02:38 by avillar           #+#    #+#             */
/*   Updated: 2022/06/21 16:28:01 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	countcase(char const *s, char c)
{
	int	res;
	int	i;

	i = 0;
	res = 0;
	while (s[i])
	{
		if (s[i] == c)
			res++;
		i++;
	}
	return (res + 1);
}

int	sizel(char const *s, int i, char c)
{
	int	len;

	len = 0;
	while (s[i] != c && s[i])
	{
		len++;
		i++;
	}
	return (len);
}

void	fill_tab(char const *s, char c, int x, char *dst)
{
	int	i;

	i = 0;
	while (s[x] != c && s[x])
	{
		dst[i] = s[x];
		i++;
		x++;
	}
	if (dst[0] == '/')
	{
		dst[i] = '/';
		i++;
	}
	dst[i] = '\0';
}

int	skipc(const char *s, char c, int i)
{
	while (s[i] == c && s[i])
		i++;
	return (i);
}

char	**ft_split(char const *s, char c)
{
	char		**rtn;
	t_split		split;

	if (s == 0)
		return (0);
	rtn = malloc(sizeof(char *) * ((countcase(s, c)) + 1));
	if (!rtn)
		return (0);
	init_split(&split, s, c);
	while (split.j <= countcase(s, c) && s[split.i])
	{
		split.len = sizel(s, split.i, c);
		rtn[split.j] = malloc(sizeof(char) * (split.len + 2));
		if (!(rtn[split.j]))
			return (0);
		fill_tab(s, c, split.i, rtn[split.j]);
		split.i += split.len;
		split.i = skipc(s, c, split.i);
		split.j++;
	}
	rtn[split.j] = NULL;
	return (rtn);
}
