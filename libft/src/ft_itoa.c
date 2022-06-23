/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:50:10 by avillar           #+#    #+#             */
/*   Updated: 2022/06/21 16:28:01 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

int	mallocsize(unsigned int nb, int s, int n)
{
	if (n < 0)
	{
		n = 0;
		s++;
	}
	if (nb < 10)
		return (s + 1);
	return (mallocsize((nb / 10), s += 1, n));
}

int	neg(int n)
{
	unsigned int	neg;

	if (n < 0)
		neg = n * -1;
	else
		neg = n;
	return (neg);
}

char	*ft_itoa(int n)
{
	char			*rtn;
	int				i;
	int				len;
	unsigned int	nb;

	i = 0;
	if (n < 0)
		i++;
	nb = neg(n);
	len = mallocsize(nb, 0, n);
	rtn = malloc(sizeof(char) * len + 1);
	if (!rtn)
		return (0);
	if (i > 0)
		rtn[0] = '-';
	rtn[len] = '\0';
	while (len > i)
	{
		rtn[len - 1] = (nb % 10) + 48;
		nb = nb / 10;
		len--;
	}
	return (rtn);
}
