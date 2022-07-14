/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_redi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 09:41:42 by thbierne          #+#    #+#             */
/*   Updated: 2022/07/14 17:03:59 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

t_llist	*create_redi(t_llist *list)
{
	t_cmd	*cmd;
	t_arg	*arg;

	cmd = list->first_cmd;
	while (cmd)
	{
		if (cmd->nbr == -1 || cmd->nbr == -2)
			check_files(cmd->next_arg->arg, cmd->nbr);
		arg = cmd->next_arg;
		while (arg)
		{
			if (arg->nbr == -1 || arg->nbr == -2)
				check_files(arg->next_arg->arg, arg->nbr);
			arg = arg->next_arg;
		}
		cmd = cmd->next_cmd;
	}
	return (list);
}

void	check_files(char *filename, int mode)
{
	if (mode == -1)
		ft_redirection(NULL, filename);
	else if (mode == -2)
	{
		if (access(filename, R_OK | W_OK) != 0)
			ft_redirection(NULL, filename);
	}
}