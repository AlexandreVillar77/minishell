/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_del.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:55:19 by avillar           #+#    #+#             */
/*   Updated: 2022/06/23 15:02:16 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	larg_del_first(t_arg **arg)
{
	if (!arg)
		return ;
	if ((*arg)->next_arg)
		*arg = (*arg)->next_arg;
}

void	larg_del_next(t_arg **arg)
{
	t_arg *tmp;
	t_arg *todel;

	if (!arg)
		return ;
	tmp = *arg;
	todel = tmp->next_arg;
	if (todel->next_arg)
		tmp->next_arg = todel->next_arg;
}