/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 16:14:08 by alewalla          #+#    #+#             */
/*   Updated: 2020/01/10 04:29:14 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*first;
	unsigned char	*second;

	i = 0;
	first = (unsigned char *)dst;
	second = (unsigned char *)src;
	while (i < n)
	{
		first[i] = second[i];
		if (second[i] == (unsigned char)c)
			return (dst + i + 1);
		i++;
	}
	return (NULL);
}
