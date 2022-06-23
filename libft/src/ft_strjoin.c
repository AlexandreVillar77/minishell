/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/07 10:52:23 by avillar           #+#    #+#             */
/*   Updated: 2022/06/21 16:28:01 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char		*rtn;
	size_t		s1s;
	size_t		s2s;

	if (s1 == 0 || s2 == 0)
		return (0);
	s1s = ft_strlen((char *)s1);
	s2s = ft_strlen((char *)s2);
	rtn = malloc(sizeof(char) * s1s + s2s + 1);
	if (!rtn)
		return (0);
	ft_strlcpy(rtn, s1, s1s + 1);
	ft_strlcat(rtn, s2, s1s + s2s + 1);
	return (rtn);
}
