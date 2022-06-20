/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/17 13:58:42 by alewalla          #+#    #+#             */
/*   Updated: 2022/04/08 11:27:22 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(char *s, char (*f)(int, char))
{
	char	*map;
	int		i;

	if (s == NULL || f == NULL)
		return (NULL);
	map = (char *)malloc(sizeof(char) * ft_strlen(s) + 1);
	if (!map)
		return (NULL);
	i = -1;
	while (s[++i])
		map[i] = f(i, s[i]);
	map[i] = '\0';
	return (map);
}
