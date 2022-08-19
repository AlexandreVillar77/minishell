/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:51:57 by thbierne          #+#    #+#             */
/*   Updated: 2022/08/16 15:01:15 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		count_heredoc(t_cmd *cmd)
{
	int		x;
	t_cmd	*tmp;
	t_arg	*cpy;

	x = 0;
	tmp = cmd;
	if (tmp->nbr == -4)
		x = 2;
	cpy = cmd->next_arg;
	while (cpy)
	{
		if (cpy->nbr == -4)
		{
			if (x == 0)
				x++;
			x++;
		}
		cpy = cpy->next_arg;
	}
	return (x);
}

t_llist	*alloc_heredoc(t_llist *list, char *line_read)
{
	t_cmd	*cmd_cpy;
	t_arg	*arg_cpy;
	char	*here;
	int		file;
	
	cmd_cpy = list->first_cmd;
	arg_cpy = NULL;
	while (cmd_cpy)
	{
		if (cmd_cpy->nbr == -4)
		{
			if (access(".tmp", R_OK | W_OK) != 0)
				file = open(".tmp", O_CREAT | O_RDWR);
			else
				file = open(".tmp", O_RDWR | O_TRUNC);
			here = heredoc(cmd_cpy->next_arg->arg, list, line_read);
			write(file, here, len(here));
			if (cmd_cpy->next_arg->next_arg)
				arg_cpy = cmd_cpy->next_arg->next_arg;
			else
				arg_cpy = NULL;
		}
		if (cmd_cpy->next_arg && arg_cpy == NULL)
			arg_cpy = cmd_cpy->next_arg;
		while (arg_cpy)
		{
			if (arg_cpy->nbr == -4)
			{
				if (access(".tmp", R_OK | W_OK) != 0)
					file = open(".tmp", O_CREAT | O_RDWR);
				else
					file = open(".tmp", O_RDWR | O_TRUNC);
				here = heredoc(arg_cpy->next_arg->arg, list, line_read);
				write(file, here, len(here));
				free(here);
				arg_cpy = arg_cpy->next_arg;
			}
			arg_cpy = arg_cpy->next_arg;
		}
		cmd_cpy = cmd_cpy->next_cmd;
	}
	return (list);
}