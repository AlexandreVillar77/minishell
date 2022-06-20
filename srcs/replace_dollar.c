/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   replace_dollar.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 13:54:59 by thbierne          #+#    #+#             */
/*   Updated: 2022/06/13 14:04:38 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft/libft.h"

char	*join_line_read1(char *line_read, t_env *tmp, int i)
{
	char	*cpy;
	int		y;
	int		nbr_n;

	y = 0;
	while (line_read[y])
		y++;
	if (tmp)
		cpy = malloc(sizeof(char) * ((y - len(tmp->name)) + len(tmp->var) + 1));
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

char	*join_line_read2(t_env *tmp, char *cpy, int *i, int *y)
{
	int		nbr_n;

	nbr_n = 0;
	while (tmp->var[nbr_n])
	{
		cpy[*y] = tmp->var[nbr_n];
		*y = *y + 1;
		nbr_n++;
	}
	*i = *i + len(tmp->name);
	return (cpy);
}

char	*join_line_read(char *line_read, t_env *tmp, int i)
{
	char	*cpy;
	int		y;

	cpy = join_line_read1(line_read, tmp, i);
	y = -1;
	while (++y < i)
		cpy[y] = line_read[y];
	if (tmp)
		cpy = join_line_read2(tmp, cpy, &i, &y);
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

t_env	*check_dollar_t_env(char *line_read, t_env *first_env, int i)
{
	int		y;
	int		z;
	t_env	*tmp;

	tmp = first_env;
	while (tmp)
	{
		y = i;
		y++;
		z = 0;
		while (line_read[y] == tmp->name[z] && line_read[y] && tmp->name[z])
		{
			y++;
			z++;
		}
		if (tmp->name[z] == '=' || tmp->name[z] == '\0')
		{
			if (line_read[y] == ' ' || line_read[y] == '='
				|| !line_read[y] || !tmp->name[z] || line_read[y] == '\''
				|| line_read[y] == '\"')
				return (tmp);
		}
		tmp = tmp->next_env;
	}
	return (NULL);
}

char	*replace_dollar(char *line_read, t_env *first_env, int mode)
{
	int		i;
	int		check;
	t_env	*tmp;
	char	c;

	i = -1;
	check = 0;
	while (line_read[++i])
	{
		if ((line_read[i] == '\'' || line_read[i] == '\"') && mode == 0)
		{
			c = line_read[i++];
			while (line_read[i] != c)
				i++;
		}
		else if (line_read[i] == '$')
		{
			tmp = check_dollar_t_env(line_read, first_env, i);
			line_read = join_line_read(line_read, tmp, i);
			if (tmp != NULL)
				i = i + len(tmp->var);
			i--;
		}
	}
	return (line_read);
}
