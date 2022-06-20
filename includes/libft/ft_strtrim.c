/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: alewalla <alewalla@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 19:12:55 by alewalla          #+#    #+#             */
/*   Updated: 2022/04/08 11:40:18 by alewalla         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_checktrim(char c, char const *set)
{
	int		y;

	y = 0;
	while (set[y])
	{
		if (set[y] == c)
			return (1);
		y++;
	}
	return (0);
}

static char	*ft_xy_strtrim(void)
{
	char	*dest;

	dest = malloc(sizeof(char));
	if (!dest)
		return (NULL);
	dest[0] = '\0';
	return (dest);
}

static int	ft_strlen_strtrim(char const *s1)
{
	unsigned int	i;

	i = 0;
	while (s1[i] != '\0')
		i++;
	return (i);
}

char	*ft_strtrim(char *s1, char *set)
{
	int		x;
	int		y;
	int		i;
	char	*dest;

	if (s1 == NULL || set == NULL)
		return (NULL);
	y = (ft_strlen_strtrim(s1) - 1);
	x = 0;
	while (ft_checktrim(s1[x], set) == 1)
		x++;
	if (x == (y + 1))
		return ((char *)ft_xy_strtrim());
	if (x > y)
		return ((char *)ft_xy_strtrim());
	while (ft_checktrim(s1[y], set) == 1)
		y--;
	dest = malloc(sizeof(char) * (y - x + 2));
	if (!dest)
		return (NULL);
	i = 0;
	while (x <= y)
		dest[i++] = s1[x++];
	dest[i] = '\0';
	return (dest);
}
