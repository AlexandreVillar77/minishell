/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 11:03:36 by avillar           #+#    #+#             */
/*   Updated: 2022/06/21 16:28:01 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memcpy(void *restrict dst, const void *restrict src, size_t n)
{
	int		i;
	int		id;

	id = 0;
	i = sizeof(char);
	if (!(src || dst))
		return (0);
	while (n > 0)
	{
		((char *)dst)[id] = *(char *)src;
		id++;
		src++;
		n -= i;
	}
	return (dst);
}
