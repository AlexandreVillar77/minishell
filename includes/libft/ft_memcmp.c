/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 19:07:56 by alewalla          #+#    #+#             */
/*   Updated: 2020/01/10 04:31:53 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	unsigned int	i;
	unsigned char	*cmpone;
	unsigned char	*cmptwo;

	i = 0;
	cmpone = (unsigned char *)s1;
	cmptwo = (unsigned char *)s2;
	while (i < n)
	{
		if ((cmpone[i] < cmptwo[i]) || (cmpone[i] > cmptwo[i]))
			return (cmpone[i] - cmptwo[i]);
		i++;
	}
	return (0);
}
