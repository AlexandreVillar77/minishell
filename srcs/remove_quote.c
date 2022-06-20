/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quote.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 10:38:21 by thbierne          #+#    #+#             */
/*   Updated: 2022/06/13 14:04:39 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft/libft.h"

char	*remove_quote(t_llist *list, char *read_line)
{
	int		y;
	int		z;
	char	c;
	char	*tmp;

	y = list->index;
	c = read_line[list->index];
	y++;
	while (read_line[y] != c)
		y++;
	tmp = (char *)malloc(sizeof(char) * (++y - list->index + 1));
	z = 0;
	while (list->index < y)
	{
		tmp[z] = read_line[list->index];
		z++;
		list->index++;
	}
	tmp[z] = '\0';
	tmp = delete_quote(tmp);
	if (c == '\"')
		tmp = replace_dollar(tmp, list->first_env, 1);
	return (tmp);
}

char	*delete_quote(char *str)
{
	int		i;
	int		y;
	char	*cpy;

	cpy = malloc(sizeof(char) * (len(str) - 1));
	i = 1;
	y = 0;
	while (str[i] && str[i + 1] != '\0')
	{
		cpy[y] = str[i];
		i++;
		y++;
	}
	cpy[y] = '\0';
	free (str);
	return (cpy);
}
