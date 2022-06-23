/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 11:07:14 by avillar           #+#    #+#             */
/*   Updated: 2022/06/21 16:28:01 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	triminatorstart(char const *s1, char const *set)
{
	int		i;
	int		j;
	int		same;

	same = 1;
	i = 0;
	while (s1[i] && same == 1)
	{
		j = 0;
		while (set[j])
		{
			if (set[j] == s1[i])
			{
				break ;
			}
			j++;
		}
		i++;
		if (j == ft_strlen((char *)set))
			break ;
	}
	return (i);
}

int	triminatorend(char const *s1, char const *set, int len)
{
	int		i;
	int		j;
	int		same;

	same = 1;
	i = 0;
	while (s1[len] && same == 1)
	{
		j = 0;
		while (set[j])
		{
			if (set[j] == s1[len])
			{
				break ;
			}
			j++;
		}
		len--;
		i++;
		if (j == ft_strlen((char *)set))
			break ;
	}
	return (i);
}

char	*rtnnull(char *ret)
{
	ret = malloc(sizeof(char) * 1);
	if (!ret)
		return (0);
	ret[0] = '\0';
	return (ret);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	char	*ret;
	int		i;
	int		len;
	int		j;
	int		end;

	if (s1 == 0)
		return (0);
	len = ft_strlen((char *)s1);
	i = triminatorstart(s1, set) - 1;
	j = 0;
	end = triminatorend(s1, set, len - 1) - 1;
	ret = 0;
	if (i + end > len)
		return (rtnnull(ret));
	ret = malloc(sizeof(char) * (len - (end + i) + 1));
	if (!ret)
		return (0);
	while (i < len - end)
	{
		ret[j++] = s1[i];
		i++;
	}
	ret[j] = '\0';
	return (ret);
}
