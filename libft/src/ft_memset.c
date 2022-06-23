/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 11:03:59 by avillar           #+#    #+#             */
/*   Updated: 2022/06/21 16:28:01 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_memset(void *ptr, int c, size_t len)
{
	int		i;
	int		id;

	id = 0;
	i = sizeof(char);
	while (len > 0)
	{
		((char *)ptr)[id] = c;
		id++;
		len -= i;
	}
	return (ptr);
}
