/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_last_redirection.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/11 09:05:29 by thbierne          #+#    #+#             */
/*   Updated: 2022/08/12 13:21:32 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_redi(t_cmd *cmd, int count)
{
	int check;
	t_arg	*arg_cpy;

	check = 0;
	if (cmd->nbr == -1 || cmd->nbr == -2)
		check++;
	arg_cpy = cmd->next_arg;
	while (arg_cpy != NULL)
	{
		if (arg_cpy->nbr == -1 || arg_cpy->nbr == -2)
			check++;
		arg_cpy = arg_cpy->next_arg;
	}
	if ((check - count) == count)
		return (1);
	return (0);
}

t_llist	*add_cmd_to_last_arg(t_llist *list, t_cmd *cmd_cpy, int *count)
{
	cmd_cpy->next_arg = add_last_t_arg(cmd_cpy->next_arg, cmd_cpy->cmd, cmd_cpy->nbr);
	cmd_cpy->next_arg = add_last_t_arg(cmd_cpy->next_arg, cmd_cpy->next_arg->arg, 0);
	*count = *count + 1;
	return (list);
}

t_llist	*check_and_add_last_redi(t_llist *list)
{
	t_cmd	*cmd_cpy;
	t_arg	*arg_cpy;
	int		count;

	cmd_cpy = list->first_cmd;
	while (cmd_cpy != NULL)
	{
		if (cmd_cpy->next_arg)
		{
			count = 0;
			if (cmd_cpy->nbr == -1 || cmd_cpy->nbr == -2)
				list = add_cmd_to_last_arg(list, cmd_cpy, &count);
			arg_cpy = cmd_cpy->next_arg;
			while (arg_cpy != NULL && count_redi(cmd_cpy, count) != 1)
			{
				if (arg_cpy->nbr == -1 || arg_cpy->nbr == -2)
				{
					cmd_cpy->next_arg = add_last_t_arg(cmd_cpy->next_arg, arg_cpy->arg, arg_cpy->nbr);
					cmd_cpy->next_arg = add_last_t_arg(cmd_cpy->next_arg, arg_cpy->next_arg->arg, 0);
					count++;
				}
				arg_cpy = arg_cpy->next_arg;
			}
		}
		cmd_cpy = cmd_cpy->next_cmd;
	}
	return (list);
}