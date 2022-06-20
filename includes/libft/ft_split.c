/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 13:57:13 by alewalla          #+#    #+#             */
/*   Updated: 2022/06/13 14:19:53 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	**ft_malloc_error(char **tabs)
{
	unsigned int	i;

	i = 0;
	while (tabs[i])
	{
		if (tabs[i])
		{
			free(tabs[i]);
			i++;
		}
	}
	free(tabs);
	return (NULL);
}

static unsigned int	ft_get_nb_strs(char *s, char c)
{
	unsigned int	i;
	unsigned int	nb_strs;

	if (s == NULL || !c || s[0] == '\0' || c == '\0')
		return (0);
	if (!s[0])
		return (0);
	i = 0;
	nb_strs = 0;
	while (s[i] && s[i] == c)
		i++;
	while (s[i])
	{
		if (s[i] == c)
		{
			nb_strs++;
			while (s[i] && s[i] == c)
				i++;
			continue ;
		}
		i++;
	}
	if (s[i - 1] != c)
		nb_strs++;
	return (nb_strs);
}

static void	ft_get_next_str(char **next_str, unsigned int *next_str_len,
				char c)
{
	unsigned int	i;

	*next_str += *next_str_len;
	*next_str_len = 0;
	i = 0;
	while (**next_str && **next_str == c)
		(*next_str)++;
	while ((*next_str)[i])
	{
		if ((*next_str)[i] == c)
			return ;
		(*next_str_len)++;
		i++;
	}
}

char	**ft_split(char *s, char c)
{
	char			**tabs;
	char			*next_str;
	unsigned int	next_str_len;
	unsigned int	nb_strs;
	unsigned int	i;

	nb_strs = ft_get_nb_strs(s, c);
	tabs = malloc(sizeof(char *) * (nb_strs + 1));
	if (!tabs)
		return (NULL);
	i = 0;
	next_str = (char *)s;
	next_str_len = 0;
	while (i < nb_strs)
	{
		ft_get_next_str(&next_str, &next_str_len, c);
		tabs[i] = malloc(sizeof(char) * (next_str_len + 1));
		if (!(tabs[i]))
			return (ft_malloc_error(tabs));
		ft_strlcpy(tabs[i], next_str, next_str_len + 1);
		i++;
	}
	tabs[i] = NULL;
	return (tabs);
}
