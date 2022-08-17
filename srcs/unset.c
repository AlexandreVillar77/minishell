/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 10:24:43 by avillar           #+#    #+#             */
/*   Updated: 2022/08/17 11:35:54 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_llist	*del_env(t_llist *list, int m)
{
	t_env	*tmp;
	char	*name;

	if (!list->first_env)
		return (list);
	tmp = list->first_env;
	if (tmp->next_env)
	name = list->first_env->name;
		list->first_env = list->first_env->next_env;
	if (ft_strncmp(name, "OLDPWD=", 7) == 0 && m == 0)
		list->lastpos = NULL;
	if (ft_strncmp(name, "PATH=", ft_strlen(name)) == 0)
		list = free_llist_tab(list, 0);
	free (tmp->name);
	free (tmp->var);
	free (tmp);
	return (list);
}

t_llist	*delete_lenv(int x, t_llist *list, int m)
{
	t_env	*tmp;
	t_env	*todel;

	if (!list->first_env)
		return (list);
	tmp = list->first_env;
	while (x > 1)
	{
		tmp = tmp->next_env;
		x--;
	}
	todel = tmp->next_env;
	tmp->next_env = todel->next_env;
	if (ft_strncmp(todel->name, "OLDPWD=", 7) == 0 && m == 0)
		list->lastpos = NULL;
	if (ft_strncmp(todel->name, "PATH=", ft_strlen(todel->name)) == 0)
		list = free_llist_tab(list, 0);
	free (todel->name);
	free (todel->var);
	free (todel);
	return (list);
}

int	ft_unset(t_llist *list)
{
	t_env	*tmp;
	int		x;
	t_arg	*arg;

	if (!list->first_cmd->next_arg)
		return (0);
	arg = list->first_cmd->next_arg;
	while (arg)
	{
		x = 0;
		on_export(list, arg);
		tmp = list->first_env;
		while (tmp)
		{
			if (is_target(tmp, &list, arg, x) == 1)
				break ;
			x++;
			tmp = tmp->next_env;
		}
		arg = arg->next_arg;
	}
	return (0);
}
