/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 11:03:25 by avillar           #+#    #+#             */
/*   Updated: 2022/06/21 16:28:01 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	char	cr;

	cr = c;
	while (n > 0 && *(char *)s != cr)
	{
		s++;
		n -= sizeof(char);
	}
	if (n > 0)
		return ((void *)s);
	else
		return (0);
}
