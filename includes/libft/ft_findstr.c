/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_findstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/07 15:41:21 by alewalla          #+#    #+#             */
/*   Updated: 2022/04/07 16:26:24 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_findstr(char *haystack, char *needle)
{
	int	x;
	int	y;

	x = 0;
	if (needle[0] == '\0')
		return (ft_strlen(haystack));
	if (haystack == needle)
		return (x);
	while (haystack[x] != '\0')
	{
		y = 0;
		while (haystack[x + y] == needle[y]
			&& haystack[x + y] && needle[y])
			y++;
		if (needle[y] == '\0')
			return (x);
		x++;
	}
	return (-1);
}
