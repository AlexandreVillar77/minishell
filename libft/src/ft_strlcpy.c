/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 13:05:25 by avillar           #+#    #+#             */
/*   Updated: 2022/08/12 11:07:10 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcpy(char *restrict dst,
		const char *restrict src, size_t dstsize)
{
	int		i;

	i = 0;
	if (!(src))
		return (0);
	if (dstsize > 0)
	{
		while (((char *)src)[i] && (i < ((int)dstsize - 1)))
		{
			dst[i] = ((char *)src)[i];
			i++;
		}
		dst[i] = '\0';
	}
	return (ft_strlen((char *)src));
}

char	*ft_strcpy(const char *restrict src)
{
	int		i;
	char	*dst;

	i = 0;
	if (!(src))
		return (0);
	dst = malloc(sizeof(char) * (ft_strlen(((char *)src)) + 1));
	if (!dst)
		return (0);
	while (((char *)src)[i])
	{
		dst[i] = ((char *)src)[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}
