/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 15:10:25 by avillar           #+#    #+#             */
/*   Updated: 2022/07/14 17:02:47 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

char	*recup_name(t_arg *arg)
{
	int		size;
	char	*rtn;

	size = 0;
	while (arg->arg[size] && arg->arg[size] != '=')
		size++;
	rtn = malloc(sizeof(char) * (size + 1));
	if (!rtn)
		exit (EXIT_FAILURE);
	size = 0;
	while (arg->arg[size] && arg->arg[size] != '=' && arg->arg[size] != '+')
	{
		rtn[size] = arg->arg[size];
		size++;
	}
	rtn[size] = '\0';
	return (rtn);
}

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

char	*delete_equal(t_arg *arg)
{
	int		i;
	char	*rtn;
	int		x;

	i = 0;
	x = 0;
	rtn = malloc(sizeof(char) * (ft_strlen(arg->arg) - 1));
	if (!rtn)
		exit (EXIT_FAILURE);
	while (arg->arg[i] && arg->arg[i] != '=' && arg->arg[i] != '+')
	{
		rtn[x] = arg->arg[i];
		i++;
		x++;
	}
	if (i == '+')
		i++;
	i++;
	while (arg->arg[i])
	{
		rtn[x] = arg->arg[i];
		i++;
		x++;
	}
	rtn[x] = '\0';
	return (rtn);
}

int	ft_export(t_llist **list, t_arg **arg)
{
	char	*name;
	t_env	*tmpenv;
	t_arg	*tmp;

	tmp = *arg;
	tmpenv = (*list)->first_env;
	name = recup_name(tmp);
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
			tmpenv->var = ft_strjoin(tmpenv->var, get_var(tmp));
	}
	return (0);
}