/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:53:05 by alewalla          #+#    #+#             */
/*   Updated: 2022/04/08 11:27:33 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(char *haystack, char *needle, int len)
{
	int	x;
	int	y;

	x = 0;
	if (needle[0] == '\0')
		return ((char *)&haystack[x]);
	if (haystack == needle)
		return ((char *)haystack);
	while (haystack[x] != '\0' && x < len)
	{
		y = 0;
		while (haystack[x + y] == needle[y] && x + y < len
			&& haystack[x + y] && needle[y])
			y++;
		if (needle[y] == '\0')
			return ((char *)(haystack + x));
		x++;
	}
	return (NULL);
}
