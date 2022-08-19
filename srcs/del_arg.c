/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   del_arg.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 10:43:21 by avillar           #+#    #+#             */
/*   Updated: 2022/08/19 10:56:18 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*del_arg(t_cmd *cmd)
{
	t_arg	*tmp;

	if (!cmd->next_arg)
		return (cmd);
	tmp = cmd->next_arg;
	if (tmp->next_arg)
		cmd->next_arg = cmd->next_arg->next_arg;
	free(tmp);
	return (cmd);
}

t_cmd	*delete_larg(int x, t_cmd *cmd)
{
	t_arg	*tmp;
	t_arg	*todel;

	if (!cmd->next_arg)
		return (cmd);
	tmp = cmd->next_arg;
	while (x > 1)
	{
		tmp = tmp->next_arg;
		x--;
	}
	todel = tmp->next_arg;
	tmp->next_arg = todel->next_arg;
	free(todel);
	return (cmd);
}
