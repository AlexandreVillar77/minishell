/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 11:01:23 by avillar           #+#    #+#             */
/*   Updated: 2022/06/21 16:28:01 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memccpy(void *restrict dst,
		const void *restrict src, int c, size_t n)
{
	int		i;
	char	cr;

	cr = c;
	i = sizeof(cr);
	while (n > 0 && *(char *)src != cr)
	{
		*(char *)dst = *(char *)src;
		dst++;
		src++;
		n -= i;
	}
	if (*(char *)src == cr)
	{
		*(char *)dst = *(char *)src;
		dst++;
		src++;
		return (dst);
	}
	else
		return (0);
}
