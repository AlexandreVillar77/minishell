/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 10:28:33 by avillar           #+#    #+#             */
/*   Updated: 2022/06/21 16:28:01 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char		*rtn;
	size_t		i;

	i = 0;
	if (s == 0)
		return (0);
	rtn = malloc(sizeof(char) * len + 1);
	if (!rtn)
		return (0);
	while (i < len && (int)start <= ft_strlen((char *)s))
	{
		rtn[i] = s[start];
		i++;
		start++;
	}
	rtn[i] = 0;
	return (rtn);
}
