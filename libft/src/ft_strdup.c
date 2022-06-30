/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/06 15:38:49 by avillar           #+#    #+#             */
/*   Updated: 2022/06/24 15:45:00 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strdup(const char *s1)
{
	char	*rtn;
	int		i;

	if (!s1)
		return (NULL);
	i = 0;
	rtn = malloc(sizeof(char) * ft_strlen((char *)s1) + 1);
	if (!rtn)
		return (0);
	while (((char *)s1)[i])
	{
		rtn[i] = ((char *)s1)[i];
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}
