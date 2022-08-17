/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:10:25 by avillar           #+#    #+#             */
/*   Updated: 2022/08/17 10:18:04 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	len_ofarg(t_arg *arg)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (arg->arg[i] && arg->arg[i] != '+' && arg->arg[i] != '=')
		i++;
	i++;
	if (arg->arg[i] == '=')
		i++;
	while (arg->arg[i])
	{
		i++;
		x++;
	}
	return (x);
}

char	*get_var(t_arg *arg)
{
	int		i;
	char	*rtn;
	int		x;

	i = 0;
	x = 0;
	while (arg->arg[i] && arg->arg[i] != '=')
		i++;
	i++;
	rtn = malloc(sizeof(char) * (ft_strlen(arg->arg) - i + 1));
	if (!rtn)
		exit (EXIT_FAILURE);
	while (arg->arg[i])
	{
		rtn[x] = arg->arg[i];
		x++;
		i++;
	}
	rtn[x] = '\0';
	return (rtn);
}

char	*upd_var(t_env *tmpenv, t_arg *tmp)
{
	char	*rtn;
	char	*tmpc;

	tmpc = get_var(tmp);
	rtn = ft_strjoin(tmpenv->var, tmpc);
	free(tmpc);
	return (rtn);
}

int	ft_export(t_llist **list, t_arg **arg, char *name)
{
	t_env	*tmpenv;
	t_arg	*tmp;
	char	*j;

	tmp = *arg;
	tmpenv = (*list)->first_env;
	while (tmpenv->next_env
		&& ft_strncmp(name, tmpenv->name, ft_strlen(name)) != 0)
		tmpenv = tmpenv->next_env;
	if (ft_strncmp(name, tmpenv->name, ft_strlen(name)) != 0)
		tmpenv = add_t_env(tmpenv, tmp->arg);
	else if (ft_strncmp(name, tmpenv->name, ft_strlen(name)) == 0)
	{
		if (export_checker(tmp) == 1)
			tmpenv = add_var(tmpenv, tmp->arg, ft_strchr2(tmp->arg, '='));
		else if (export_checker(tmp) == 2)
		{
			j = upd_var(tmpenv, tmp);
			free (tmpenv->var);
			tmpenv->var = ft_strdup(j);
			free (j);
		}
	}
	return (0);
}
