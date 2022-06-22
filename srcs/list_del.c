/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_del.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:55:19 by avillar           #+#    #+#             */
/*   Updated: 2022/06/22 16:09:41 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	larg_del_first(t_arg *arg)
{
	t_arg	*tmp;

	if (!arg)
		return ;
	tmp = arg;
	arg = arg->next_arg;
	if (tmp->arg)
		free(tmp->arg);
	if (tmp)
		free(tmp);
}

void	larg_del_one(t_arg *arg, int id)
{
	t_arg *tmp;
	t_arg *todel;

	if (!arg)
		return ;
	tmp = arg;
	while (id > 1 && tmp->next_arg)
	{
		tmp = tmp->next_arg;
		id--;
	}
	todel = tmp->next_arg;
	if (todel->next_arg)
		tmp->next_arg = todel->next_arg;
	if (todel->arg)
		free(todel->arg);
	if (todel)
		free(todel);
}