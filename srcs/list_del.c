/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_del.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:55:19 by avillar           #+#    #+#             */
/*   Updated: 2022/08/02 10:02:12 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	larg_del_first(t_arg **arg)
{
	t_arg	*tmp;

	tmp = *arg;
	if (!arg)
		return ;
	if ((*arg)->next_arg)
		*arg = (*arg)->next_arg;
	if (tmp->arg)
		free(tmp->arg);
	free(tmp);
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
	if (todel->arg)
		free(todel->arg);
	free(todel);
}

t_cmd	*larg_del_f(t_cmd *cmd)
{
	t_arg	*tmp;

	if (!cmd)
		return (NULL);
	tmp = cmd->next_arg;
	cmd->next_arg = tmp->next_arg;
	free(tmp->arg);
	free(tmp);
	return (cmd);
}

t_arg	*larg_del_n(t_arg *arg)
{
	t_arg *tmp;

	if (!arg)
		return (NULL);
	tmp = arg->next_arg;
	arg->next_arg = tmp->next_arg;
	free(tmp->arg);
	free(tmp);
	return (arg);
}