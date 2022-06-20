/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 15:50:49 by alewalla          #+#    #+#             */
/*   Updated: 2020/01/11 17:11:52 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*dest;
	char	*last_found;
	int		i;

	dest = (char *)s;
	last_found = NULL;
	i = 0;
	if (c != '\0')
	{
		while (dest[i] != '\0')
		{
			if (dest[i] == c)
				last_found = &dest[i];
			i++;
		}
		return (last_found);
	}
	else if (c == '\0')
	{
		while (dest[i] != '\0')
			i++;
		return (&dest[i]);
	}
	return (NULL);
}
