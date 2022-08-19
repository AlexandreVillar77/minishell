/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_cmd_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:09:52 by thbierne          #+#    #+#             */
/*   Updated: 2022/08/19 10:33:03 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_llist	*test_cmd_utils(t_env *tmp, t_llist *list)
{
	char	*str;
	char	*cpy;

	if (!tmp)
	{
		str = ft_strdup("/mnt/nfs/homes/thbierne/bin:/usr/local/sbin:");
		cpy = ft_strjoin(str, "/usr/local/bin:/usr/sbin:/usr/bin:/sbin:");
		free (str);
		str = ft_strjoin(cpy, "/bin:/usr/games:/usr/local/games:/snap/bin");
		free (cpy);
		list = split_path(str, ':', list);
		free (str);
		return (list);
	}
	list = split_path(tmp->var, ':', list);
	return (list);
}

t_env	*ft_set_base_env(t_env *envl)
{
	char	*str;

	str = NULL;
	str = getcwd(str, 0);
	envl = add_t_env(envl, ft_strjoin("PWD=", str));
	envl = add_t_env(envl, "SHLVL=1");
	envl = add_t_env(envl, "_=usr/bin/env");
	free (str);
	return (envl);
}

char	*replace_dollar2(char *line_read, t_env *first_env, int *i)
{
	int		y;
	t_env	*tmp;

	y = *i;
	if (line_read[y] == '$' && line_read[y + 1] == '?')
		line_read = return_question(line_read, y);
	else
	{
		tmp = check_dollar_t_env(line_read, first_env, y);
		line_read = join_line_read(line_read, tmp, y);
		if (tmp != NULL)
			y = y + len(tmp->var);
		y--;
	}
	*i = y;
	return (line_read);
}

char	*return_question(char *line_read, int i)
{
	char	*str;
	char	*tmp;
	t_env	*dollar;

	str = ft_itoa(LOL);
	tmp = ft_strjoin("?=", str);
	dollar = NULL;
	free(str);
	dollar = add_t_env(dollar, tmp);
	free(tmp);
	line_read = join_line_read(line_read, dollar, i);
	dollar = delete_first_t_env(dollar);
	return (line_read);
}
