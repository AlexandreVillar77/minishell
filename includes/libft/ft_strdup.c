/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 16:53:59 by alewalla          #+#    #+#             */
/*   Updated: 2022/04/07 16:37:06 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(char *s1)
{
	char	*dest;
	int		i;

	dest = s1;
	i = 0;
	(dest = (char *)malloc(ft_strlen(s1) + 1));
	if (!dest)
		return (0);
	while (*s1)
		dest[i++] = *s1++;
	dest[i] = '\0';
	return ((char *)dest);
}
