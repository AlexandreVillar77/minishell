/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:14:08 by alewalla          #+#    #+#             */
/*   Updated: 2020/01/11 17:06:06 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	unsigned char	*src_copy;
	unsigned char	*dst_copy;
	unsigned int	i;

	src_copy = (unsigned char *)src;
	dst_copy = (unsigned char *)dst;
	if (dst == NULL && src == NULL && len > 0)
		return (dst);
	i = 0;
	if (src_copy > dst_copy)
	{
		while (i < len)
		{
			dst_copy[i] = src_copy[i];
			i++;
		}
	}
	else
	{
		while (len-- > 0)
			dst_copy[len] = src_copy[len];
	}
	return (dst);
}
