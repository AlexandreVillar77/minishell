/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 10:24:43 by avillar           #+#    #+#             */
/*   Updated: 2022/07/14 17:03:22 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	del_env(t_env **env)
{
	t_env	*tmp;

	tmp = *env;
	if (!env)
		return ;
	if ((*env)->next_env)
		*env = (*env)->next_env;
	free(tmp);
}

void	delete_lenv(t_env **env, int x)
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
	free(todel);
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
					del_env(&list->first_env);
				else
					delete_lenv(&list->first_env, x);
				break ;
			}
			x++;
			tmp = tmp->next_env;
		}
		arg = arg->next_arg;
	}
	return (0);
}