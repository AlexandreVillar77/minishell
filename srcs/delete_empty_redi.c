/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_empty_redi.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/12 10:32:55 by thbierne          #+#    #+#             */
/*   Updated: 2022/08/19 10:44:50 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_llist	*delete_empty_redi(t_llist *list)
{
	t_cmd	*cpy_cmd;
	t_cmd	*old;

	old = NULL;
	cpy_cmd = list->first_cmd;
	while (cpy_cmd)
	{
		if (check_full_redi(cpy_cmd) == 1)
		{
			if (old == NULL)
				list->first_cmd = clear_cmd(list->first_cmd);
			else
				old->next_cmd = clear_cmd(old->next_cmd);
			if (old == NULL)
				cpy_cmd = list->first_cmd;
			else
				cpy_cmd = old->next_cmd;
		}
		else
		{
			old = cpy_cmd;
			cpy_cmd = cpy_cmd->next_cmd;
		}
	}
	return (list);
}

int	check_full_redi(t_cmd *cmd)
{
	t_arg	*cpy_arg;

	if (cmd->nbr >= 0)
		return (0);
	if (cmd->next_arg)
	{
		cpy_arg = cmd->next_arg->next_arg;
		while (cpy_arg)
		{
			if (cpy_arg->nbr >= 0)
				return (0);
			cpy_arg = cpy_arg->next_arg->next_arg;
		}
		return (1);
	}
	return (0);
}

t_cmd	*clear_cmd(t_cmd *cmd)
{
	while (cmd->next_arg)
	{
		while (cmd->next_arg)
			cmd->next_arg = delete_first_t_arg(cmd->next_arg);
	}
	cmd = delete_first_t_cmd(cmd);
	return (cmd);
}
