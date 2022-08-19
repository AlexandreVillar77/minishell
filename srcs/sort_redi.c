/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_redi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:23:43 by thbierne          #+#    #+#             */
/*   Updated: 2022/08/19 10:40:33 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*change_cmd(t_llist *list, char *cmd)
{
	t_exe	*cpy_exe;

	cpy_exe = list->first_exe;
	while (cpy_exe)
	{
		if (strncmp(cmd, cpy_exe->name_exe, ft_strlen(cpy_exe->name_exe)))
			return (cmd);
		cpy_exe = cpy_exe->next_exe;
	}
	return (test_cmd(list, cmd));
}

t_llist	*sort_redi(t_llist *list)
{
	t_cmd	*cmd_cpy;
	t_arg	*arg_cpy;

	cmd_cpy = list->first_cmd;
	while (cmd_cpy)
	{
		arg_cpy = cmd_cpy->next_arg;
		while (arg_cpy)
			arg_cpy = arg_cpy->next_arg;
		cmd_cpy = cmd_cpy->next_cmd;
	}
	list = delete_pipe(list);
	list = create_redi(list);
	return (list);
}

t_llist	*delete_pipe(t_llist *list)
{
	t_cmd	*cmd_cpy;
	t_arg	*arg_cpy;

	cmd_cpy = list->first_cmd;
	while (cmd_cpy->next_cmd)
	{
		if (cmd_cpy->next_arg->nbr == -5 && cmd_cpy->next_arg)
			cmd_cpy->next_arg = delete_first_t_arg(cmd_cpy->next_arg);
		arg_cpy = cmd_cpy->next_arg;
		while (arg_cpy)
		{
			if (arg_cpy->next_arg->nbr == -5)
			{
				free(arg_cpy->next_arg->arg);
				free(arg_cpy->next_arg);
				arg_cpy->next_arg = NULL;
			}
			arg_cpy = arg_cpy->next_arg;
		}
		cmd_cpy = cmd_cpy->next_cmd;
	}
	return (list);
}
