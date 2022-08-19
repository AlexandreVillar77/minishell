/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cmd.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/04 13:41:37 by thbierne          #+#    #+#             */
/*   Updated: 2022/08/19 10:14:45 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*split_path_into_tab2(char *str, char *split, int *i, int *y)
{
	int	z;

	z = 0;
	while (*y < *i)
	{
		split[z] = str[*y];
		*y = *y + 1;
		z++;
	}
	split[z++] = '/';
	split[z++] = '\0';
	return (split);
}

char	**split_path_into_tab(char **split, char *str, int i, int count)
{
	int	y;

	while (str[i])
	{
		y = i;
		while (str[i] != ':' && str[i])
			i++;
		split[count] = (char *)malloc(sizeof(char) * ((i - y) + 2));
		if (!split[count])
			break ;
		split[count] = split_path_into_tab2(str, split[count], &i, &y);
		count++;
		if (!str[i])
		{
			split[count] = NULL;
			return (split);
		}
		i++;
	}
	return (NULL);
}

t_llist	*split_path(char *str, char c, t_llist *list)
{
	int	i;
	int	y;
	int	count;

	i = 0;
	y = 1;
	while (str[i])
	{
		if (str[i] == c)
			y++;
		i++;
	}
	list->path = (char **)malloc(sizeof(char *) * (y + 1));
	i = 0;
	count = 0;
	list->path = split_path_into_tab(list->path, str, i, count);
	return (list);
}

t_llist	*alloc_path(t_llist *list)
{
	int		i;
	t_env	*tmp;
	char	*str;

	if (list->path)
		free(list->path);
	tmp = list->first_env;
	str = ft_strdup("PATH=");
	while (tmp)
	{
		i = 0;
		while (str[i] == tmp->name[i] && str[i])
			i++;
		if (!str[i])
		{
			break ;
		}
		tmp = tmp->next_env;
	}
	free (str);
	return (test_cmd_utils(tmp, list));
}

char	*test_cmd(t_llist *list, char *read)
{
	char	*join;
	int		i;
	int		z;

	i = 0;
	z = -1;
	while (list->path && list->path[i])
	{
		join = ft_strjoin(list->path[i], read);
		z = access(join, X_OK);
		if (z == 0)
		{
			free(read);
			return (join);
		}
		free(join);
		i++;
	}
	free(read);
	return (NULL);
}
