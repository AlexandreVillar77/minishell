/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 10:24:43 by avillar           #+#    #+#             */
/*   Updated: 2022/08/08 11:23:20 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_llist	*del_env(t_llist *list, int m)
{
	t_env	*tmp;

	if (!list->first_env)
		return (list);
	tmp = list->first_env;
	if (tmp->next_env)
		list->first_env = list->first_env->next_env;
	if (ft_strncmp(list->first_env->name, "OLDPWD=", 7) == 0 && m == 0)
		list->lastpos = NULL;
	if (ft_strncmp(list->first_env->name, "PATH=", ft_strlen(list->first_env->name)) == 0)
		list = free_llist_tab(list, 0);
	free(tmp);
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
		list= free_llist_tab(list, 0);
	free(todel);
	return (list);
}

/*void	del_OLDPWD(t_env **env, t_llist *list)
{
	t_env	*tmp;
	int		x;

	x = 0;
	tmp = *env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "OLDPWD=", ft_strlen(tmp->name)) == 0)
			break ;
		tmp = tmp->next_env;
		x++;
	}
	if (x == 0)
		del_env(env, list, 1);
	else
		delete_lenv(env, x, list, 1);
}*/

int		ft_unset(t_llist *list)
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
		tmp = list->first_env;
		while (tmp)
		{
			if (ft_strncmp(tmp->name, arg->arg, ft_strlen(tmp->name) - 1) == 0)
			{
				if (x == 0)
					list = del_env(list, 0);
				else
					list = delete_lenv(x, list, 0);
				break ;
			}
			x++;
			tmp = tmp->next_env;
		}
		arg = arg->next_arg;
	}
	return (0);
}