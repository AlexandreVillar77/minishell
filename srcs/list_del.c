/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_del.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:55:19 by avillar           #+#    #+#             */
/*   Updated: 2022/06/23 10:58:02 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	larg_del_first(t_arg **arg)
{
	//t_arg	*tmp;

	if (!arg)
		return ;
	//tmp = *arg;
	if ((*arg)->next_arg)
		*arg = (*arg)->next_arg;
	//free(tmp);
}

void	larg_del_one(t_arg **arg, int id)
{
	t_arg *tmp;
	t_arg *todel;

	if (!arg)
		return ;
	if (id == 0)
	{
		larg_del_first(arg);
		return ;
	}
	tmp = *arg;
	while (id > 1 && tmp->next_arg)
	{
		tmp = tmp->next_arg;
		id--;
	}
	todel = tmp->next_arg;
	if (todel->next_arg)
		tmp->next_arg = todel->next_arg;
	free(todel);
}