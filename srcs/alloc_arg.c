/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_arg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/22 11:35:31 by thbierne          #+#    #+#             */
/*   Updated: 2022/06/13 14:20:07 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"


t_llist	*alloc_arg(t_llist *list, char *read_line)
{
	char	*str;
	t_cmd	*cmd;
	int		y;

	str = NULL;
	y = list->index;
	str = find_str(list, read_line, str, y);
	cmd = list->first_cmd;
	while (cmd->next_cmd)
		cmd = cmd->next_cmd;
	if (!cmd->next_arg)
		cmd->next_arg = add_first_t_arg(str, 0);
	else
		cmd->next_arg = add_last_t_arg(cmd->next_arg, str, 0);
	free(str);
	return (list);
}

