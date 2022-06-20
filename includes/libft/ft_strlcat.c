/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 18:38:09 by alewalla          #+#    #+#             */
/*   Updated: 2022/04/07 15:31:32 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strlcat(char *dst, char *src, int dstsize)
{
	int	src_size;
	int	dst_size;
	int	i;

	i = 0;
	src_size = 0;
	dst_size = 0;
	while (src[src_size])
		src_size++;
	if (dstsize == 0)
		return (src_size);
	while (dst[dst_size] && dst_size < dstsize)
		dst_size++;
	if (dstsize <= dst_size)
		return (dstsize + src_size);
	i = 0;
	while (src[i] != '\0' && dst_size + i < dstsize - 1)
	{
		dst[dst_size + i] = src[i];
		i++;
	}
	dst[dst_size + i] = '\0';
	return (src_size + dst_size);
}
