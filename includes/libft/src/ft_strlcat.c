/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 13:28:41 by avillar           #+#    #+#             */
/*   Updated: 2022/06/21 16:28:01 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

size_t	ft_strlcat(char *restrict dst,
		const char *restrict src, size_t dstsize)
{
	int		i;
	int		di;
	int		si;

	i = 0;
	si = ft_strlen((char *)src);
	di = ft_strlen(dst);
	if (dstsize > 0)
	{
		while (((char *)src)[i] && ((di + i) < ((int)dstsize - 1)))
		{
			dst[di + i] = ((char *)src)[i];
			i++;
		}
		dst[di + i] = '\0';
	}
	if ((int)dstsize >= di)
		return (si + di);
	return (dstsize + si);
}
