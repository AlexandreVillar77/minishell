/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 10:43:21 by avillar           #+#    #+#             */
/*   Updated: 2022/08/17 10:09:28 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_llist	*del_arg(t_llist *list)
{
	t_arg	*tmp;

	if (!list->first_cmd->next_arg)
		return (list);
	tmp = list->first_cmd->next_arg;
	if (tmp->next_arg)
		list->first_cmd->next_arg = list->first_cmd->next_arg->next_arg;
	free(tmp);
	return (list);
}

t_llist	*delete_larg(int x, t_llist *list)
{
	t_arg	*tmp;
	t_arg	*todel;

	if (!list->first_cmd->next_arg)
		return (list);
	tmp = list->first_cmd->next_arg;
	while (x > 1)
	{
		tmp = tmp->next_arg;
		x--;
	}
	todel = tmp->next_arg;
	tmp->next_arg = todel->next_arg;
	free(todel);
	return (list);
}
