/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sort_redi.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:23:43 by thbierne          #+#    #+#             */
/*   Updated: 2022/07/27 16:03:22 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*change_cmd(t_llist *list, char* cmd)
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
		if (cmd_cpy->nbr == -1 || cmd_cpy->nbr == -2)
			list = sort_llist_redi(list, cmd_cpy);
		arg_cpy = cmd_cpy->next_arg;
		while (arg_cpy)
			arg_cpy = arg_cpy->next_arg;
		cmd_cpy = cmd_cpy->next_cmd;
	}
	list = delete_pipe(list);
	list = create_redi(list);
	return (list);
}

t_llist	*sort_llist_redi(t_llist *list, t_cmd *t_cmd)
{
	char	*cpy1;
	char	*cpy2;
	int		cpy_arg; 

	if (!t_cmd->next_arg->next_arg)
		return (list);
	if (t_cmd->next_arg->next_arg->nbr > 0)
	{
		cpy_arg = t_cmd->nbr;
		cpy1 = ft_strdup(t_cmd->next_arg->next_arg->arg);
		cpy2 = ft_strdup(t_cmd->cmd);
		free(t_cmd->next_arg->next_arg->arg);
		free(t_cmd->cmd);
		t_cmd->cmd = ft_strdup(cpy1);
		t_cmd->nbr = 0;
		free(cpy1);
		cpy1 = ft_strdup(t_cmd->next_arg->arg);
		free(t_cmd->next_arg->arg);
		t_cmd->next_arg->next_arg->arg = ft_strdup(cpy1);
		t_cmd->next_arg->arg = ft_strdup(cpy2);
		t_cmd->next_arg->nbr = cpy_arg;
		free(cpy1);
		free(cpy2);
		cpy1 = ft_strdup(t_cmd->cmd);
		t_cmd->cmd = change_cmd(list, t_cmd->cmd);
		if (!t_cmd->cmd)
			t_cmd->cmd = ft_strdup(cpy1);
		free(cpy1);
	}
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
		{
			arg_cpy = cmd_cpy->next_arg;
			free(arg_cpy->arg);
			free(arg_cpy);
			cmd_cpy->next_arg = NULL;
		}
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