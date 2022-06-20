/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:00:25 by alewalla          #+#    #+#             */
/*   Updated: 2020/01/11 17:11:05 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char	*dest;
	int		i;

	dest = (char *)s;
	i = 0;
	if (c != '\0')
	{
		while (dest[i] != '\0')
		{
			if (dest[i] == c)
				return (&dest[i]);
			i++;
		}
	}
	else if (c == '\0')
	{
		while (dest[i] != '\0')
			i++;
		return (&dest[i]);
	}
	return (NULL);
}
