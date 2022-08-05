/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_heredoc.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/03 12:51:57 by thbierne          #+#    #+#             */
/*   Updated: 2022/08/05 09:48:46 by thbierne         ###   ########.fr       */
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
		x++;
	cpy = cmd->next_arg;
	while (cpy)
	{
		if (cpy->nbr == -4)
			x++;
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
	list = del_heredoc(list);
	return (list);
}

t_llist	*del_heredoc(t_llist *list)
{
	t_cmd	*cmd_cpy;
	t_arg	*arg_cpy;
	int 	i;

	cmd_cpy = list->first_cmd;
	while (cmd_cpy)
	{
		i = count_heredoc(cmd_cpy);
		if (cmd_cpy && cmd_cpy->next_arg)
		{
			if (cmd_cpy->next_arg && cmd_cpy->next_arg->nbr == -4)
			{
				while (cmd_cpy->next_arg && cmd_cpy->next_arg->nbr == -4 && i > 0)
				{
					cmd_cpy = larg_del_f(cmd_cpy);
					cmd_cpy = larg_del_f(cmd_cpy);
					i--;
				}
			}
			else if (i > 0)
			{
				arg_cpy = cmd_cpy->next_arg;
				while (arg_cpy->next_arg && i > 0)
				{
					if (arg_cpy->next_arg->nbr == -4 && i > 0)
					{
						arg_cpy = larg_del_n(arg_cpy);
						arg_cpy = larg_del_n(arg_cpy);
						i--;
					}
					else
						arg_cpy = arg_cpy->next_arg;
				}
			}
		}
		list = found_cat(cmd_cpy, list);
		cmd_cpy = cmd_cpy->next_cmd;
	}
	return (list);
}

t_llist	*found_cat(t_cmd *cpy_cmd, t_llist *list)
{
	if (ft_strncmp(cpy_cmd->cmd, "/usr/bin/cat", 12) == 0)
	{
		if (!cpy_cmd->next_arg)
			cpy_cmd->next_arg = add_first_t_arg(".tmp", -6);
	}
	return (list);
}