/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 12:31:32 by thbierne          #+#    #+#             */
/*   Updated: 2022/06/21 16:22:59 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_llist	*alloc_pipe(t_llist *list)
{
	t_cmd	*cmd;

	cmd = list->first_cmd;
	while (cmd->next_cmd)
		cmd = cmd->next_cmd;
	if (!cmd ->next_arg)
		cmd->next_arg = add_first_t_arg("|", -5);
	else
		cmd->next_arg = add_last_t_arg(cmd->next_arg, "|", -5);
	list->new_cmd = 1;
	list->index++;
	return (list);
}
