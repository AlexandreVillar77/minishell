/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strstr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 14:57:57 by alewalla          #+#    #+#             */
/*   Updated: 2022/04/07 14:59:12 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strstr(char *haystack, char *needle)
{
	unsigned long int	x;
	unsigned long int	y;

	x = 0;
	if (needle[0] == '\0')
		return ((char *)&haystack[x]);
	if (haystack == needle)
		return ((char *)haystack);
	while (haystack[x] != '\0')
	{
		y = 0;
		while (haystack[x + y] == needle[y]
			&& haystack[x + y] && needle[y])
			y++;
		if (needle[y] == '\0')
			return ((char *)(haystack + x));
		x++;
	}
	return (NULL);
}
