/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/06 15:13:37 by thbierne          #+#    #+#             */
/*   Updated: 2022/06/13 13:56:30 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft/libft.h"

t_llist	*alloc_str(t_llist *list, char *read_line)
{
	char	*str;
	int		y;

	str = NULL;
	y = list->index;
	str = find_str(list, read_line, str, y);
	list = check_cmd(list, read_line, str);
	return (list);
}

char	*alloc_find_str(char *read_line, int y, int *index, char *str)
{
	char	*tmp;
	char	*cpy;
	int		z;

	cpy = (char *)malloc(sizeof(char) * (y - *index + 1));
	z = 0;
	while (*index < y)
	{
		cpy[z] = read_line[*index];
		z++;
		*index = *index + 1;
	}
	cpy[z] = '\0';
	if (!str)
		str = ft_strdup(cpy);
	else
	{
		tmp = ft_strjoin(str, cpy);
		free(str);
		str = ft_strdup(tmp);
		free(tmp);
	}
	free(cpy);
	return (str);
}

char	*alloc_find_str2(char *str, char *cpy)
{
	char	*tmp;

	if (!str)
		str = ft_strdup(cpy);
	else if (cpy && cpy[0])
	{
		tmp = ft_strjoin(str, cpy);
		free(str);
		str = ft_strdup(tmp);
		free(tmp);
	}
	free(cpy);
	return (str);
}

t_llist	*moove_index(t_llist *list, char *read_line, int *y, char c)
{
	*y = *y + 1;
	while (read_line[*y] != c)
		*y = *y + 1;
	*y = *y + 1;
	list->index = *y;
	return (list);
}

char	*find_str(t_llist *list, char *read_line, char *str, int y)
{
	char	*cpy;
	char	c;

	while (read_line[y] != '|' && read_line[y] != '<'
		&& read_line[y] != '>' && read_line[y] != ' ' && read_line[y])
	{
		if (read_line[y] == '\'' || read_line[y] == '\"')
		{
			c = read_line[y];
			if (list->index != y)
				str = alloc_find_str(read_line, y, &list->index, str);
			cpy = remove_quote(list, read_line);
			list = moove_index(list, read_line, &y, c);
			str = alloc_find_str2(str, cpy);
			if (!read_line[y] || read_line[y] == '|' || read_line[y] == '<'
				|| read_line[y] == '>' || read_line[y] == ' ')
				return (str);
		}
		else
			y++;
	}
	str = alloc_find_str(read_line, y, &list->index, str);
	return (str);
}
