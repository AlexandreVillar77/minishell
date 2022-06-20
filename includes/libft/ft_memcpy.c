/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:14:08 by alewalla          #+#    #+#             */
/*   Updated: 2020/01/11 17:04:05 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	unsigned int	i;
	unsigned char	*first;
	unsigned char	*second;

	i = 0;
	first = (unsigned char *)dst;
	second = (unsigned char *)src;
	if (dst == NULL && src == NULL && n > 0)
		return (dst);
	while (i < n)
	{
		first[i] = second[i];
		i++;
	}
	return (dst);
}
