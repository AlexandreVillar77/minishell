/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_home.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 09:59:01 by thbierne          #+#    #+#             */
/*   Updated: 2022/07/14 17:04:18 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*join_line_home1(char *line_read, t_env *tmp, int i)
{
	char	*cpy;
	int		y;
	int		nbr_n;

	y = 0;
	while (line_read[y])
		y++;
	if (tmp)
		cpy = malloc(sizeof(char) * ((y - 1) + len(tmp->var) + 1));
	else
	{
		y = i;
		while (line_read[y] && line_read[y] != ' ' && line_read[y] != '<'
			&& line_read[y] != '>' && line_read[y] != '|'
			&& line_read[y] != 34 && line_read[y] != 39)
			y++;
		nbr_n = y - i;
		while (line_read[y])
			y++;
		cpy = malloc(sizeof(char) * (y - nbr_n + 1));
	}
	return (cpy);
}

char	*join_line_home2(t_env *tmp, char *cpy, int *i, int *y)
{
	int		nbr_n;

	nbr_n = 0;
	while (tmp->var[nbr_n])
	{
		cpy[*y] = tmp->var[nbr_n];
		*y = *y + 1;
		nbr_n++;
	}
	*i = *i + 1;
	return (cpy);
}

char	*join_line_home(char *line_read, t_env *tmp, int i)
{
	char	*cpy;
	int		y;

	cpy = join_line_home1(line_read, tmp, i);
	y = -1;
	while (++y < i)
		cpy[y] = line_read[y];
	if (tmp)
		cpy = join_line_home2(tmp, cpy, &i, &y);
	else
	{
		while (line_read[i] && line_read[i] != ' ' && line_read[i] != '<'
			&& line_read[i] != '>' && line_read[i] != '|'
			&& line_read[i] != 34 && line_read[i] != 39)
			i++;
	}
	while (line_read[i])
	{
		cpy[y] = line_read[i];
		y++;
		i++;
	}
	cpy[y] = '\0';
	free(line_read);
	return (cpy);
}

t_env	*check_home_t_env(t_env *first_env)
{
	int		i;
	char	*home;
	t_env	*tmp;

	tmp = first_env;
	home = ft_strdup("HOME");
	while (tmp)
	{
		i = 0;
		while (home[i] == tmp->name[i] && home[i] && tmp->name[i])
			i++;
		if (tmp->name[i] == '=')
		{
			free(home);
			return (tmp);
		}
		tmp = tmp->next_env;
	}
	free(home);
	return (NULL);
}

char	*replace_home(t_env *first_env, char *line_read)
{
	int		i;
	t_env	*tmp;
	char	c;

	i = -1;
	while (line_read[++i])
	{
		if (line_read[i] == '\'' || line_read[i] == '\"')
		{
			c = line_read[i++];
			while (line_read[i] != c)
				i++;
		}
		else if (line_read[i] == '~')
		{
			tmp = check_home_t_env(first_env);
			line_read = join_line_home(line_read, tmp, i);
			if (tmp != NULL)
				i = i + len(tmp->var);
			i--;
		}
	}
	return (line_read);
}