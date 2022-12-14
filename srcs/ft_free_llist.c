/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_llist.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/19 12:31:46 by thbierne          #+#    #+#             */
/*   Updated: 2022/08/18 11:56:31 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_llist	*free_llist_exe(t_llist *list)
{
	int	i;

	i = -1;
	while (++i < 7)
		list->first_exe = delete_first_t_exe(list->first_exe);
	return (list);
}

t_llist	*free_llist_env(t_llist *list)
{
	while (list->first_env)
		list->first_env = delete_first_t_env(list->first_env);
	return (list);
}

t_llist	*free_llist_tab(t_llist *list, int i)
{
	int	y;

	if ((i == 0 || i == 2) && (list->path))
	{
		y = 0;
		while (list->path[y])
			free(list->path[y++]);
		free(list->path[y++]);
		free(list->path);
		list->path = NULL;
	}
	if ((i == 1 || i == 2) && (list->env))
	{
		y = 0;
		while (list->env[y])
			free(list->env[y++]);
		free(list->env[y++]);
		free(list->env);
		list->env = NULL;
	}
	return (list);
}

t_llist	*free_llist_cmd(t_llist *list)
{
	if (!list)
		return (NULL);
	while (list->first_cmd)
	{
		while (list->first_cmd->next_arg)
			list->first_cmd->next_arg = delete_first_t_arg
				(list->first_cmd->next_arg);
		list->first_cmd = delete_first_t_cmd(list->first_cmd);
	}
	return (list);
}

void	free_llist(t_llist *list, char *line_read)
{
	list = free_llist_exe(list);
	list = free_llist_env(list);
	list = free_llist_tab(list, 2);
	if (list->lastpos)
		free (list->lastpos);
	free(list);
	if (line_read)
		free(line_read);
}
