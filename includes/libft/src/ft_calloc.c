/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:24:20 by avillar           #+#    #+#             */
/*   Updated: 2022/06/21 16:28:01 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void		*rtn;
	size_t		i;

	i = 0;
	rtn = malloc(size * count);
	if (!rtn)
		return (0);
	((char *)rtn)[0] = 0;
	while (i <= count * size)
	{
		((char *)rtn)[i] = 0;
		i++;
	}
	return (rtn);
}
