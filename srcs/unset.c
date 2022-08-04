/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 10:24:43 by avillar           #+#    #+#             */
/*   Updated: 2022/08/02 11:06:37 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	del_env(t_env **env, t_llist *list, int m)
{
	t_env	*tmp;

	tmp = *env;
	if (!env)
		return ;
	if ((*env)->next_env)
		*env = (*env)->next_env;
	if (ft_strncmp((*env)->name, "OLDPWD=", 7) == 0 && m == 0)
		list->lastpos = NULL;
	if (ft_strncmp((*env)->name, "PWD=", 4) == 0)
		del_OLDPWD(env, list);
	free(tmp);
}

void	delete_lenv(t_env **env, int x, t_llist *list, int m)
{
	t_env	*tmp;
	t_env	*todel;

	if (!env)
		return ;
	tmp = *env;
	while (x > 1)
	{
		tmp = tmp->next_env;
		x--;
	}
	todel = tmp->next_env;
	tmp->next_env = todel->next_env;
	if (ft_strncmp(todel->name, "OLDPWD=", 7) == 0 && m == 0)
		list->lastpos = NULL;
	if (ft_strncmp(todel->name, "PWD=", 4) == 0)
		del_OLDPWD(env, list);
	free(todel);
}

void	del_OLDPWD(t_env **env, t_llist *list)
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
}

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
		while (tmp->next_env)
		{
			if (ft_strncmp(arg->arg, tmp->name, ft_strlen(arg->arg)) == 0)
			{
				if (x == 0)
					del_env(&list->first_env, list, 0);
				else
					delete_lenv(&list->first_env, x, list, 0);
				break ;
			}
			x++;
			tmp = tmp->next_env;
		}
		arg = arg->next_arg;
	}
	return (0);
}