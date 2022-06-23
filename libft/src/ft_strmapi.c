/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 15:05:04 by avillar           #+#    #+#             */
/*   Updated: 2022/06/21 16:28:01 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strmapi(char const *s, char (*f)(unsigned int, char))
{
	char	*rtn;
	int		i;

	i = 0;
	if (s == 0)
		return (0);
	rtn = malloc(sizeof(char) * ft_strlen((char *)s) + 1);
	if (!rtn)
		return (0);
	while (s[i])
	{
		rtn[i] = (*f)(i, s[i]);
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}
