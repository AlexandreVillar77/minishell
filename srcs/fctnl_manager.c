/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fctnl_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:32:21 by avillar           #+#    #+#             */
/*   Updated: 2022/06/22 13:25:32 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"



int	check_redir(t_arg *arg)
{
	t_arg	*tmp;

	tmp = arg;
	while (tmp)
	{
		if (tmp->nbr < 0)
			return (tmp->nbr);
		tmp = tmp->next_arg;
	}
	return (0);
}

int	fctnl_manager(t_llist *list)
{
	if (strncmp(list->first_cmd->cmd, "echo", 4) == 0)
		return (ft_echo(list->first_cmd));
	if (strncmp(list->first_cmd->cmd, "cd", 2) == 0)
		return (0); // return (ft_cd(list));
	if (strncmp(list->first_cmd->cmd, "pwd", 3) == 0)
		return (0); // return (ft_pwd(list));
	if (strncmp(list->first_cmd->cmd, "export", 6) == 0)
		return (0); // return (ft_export(list));
	if (strncmp(list->first_cmd->cmd, "unset", 5) == 0)
		return (0); // return (ft_unset(list));
	if (strncmp(list->first_cmd->cmd, "env", 3) == 0)
		return (ft_penv(list));
	if (strncmp(list->first_cmd->cmd, "exit", 4) == 0)
		return (ft_exit(list));
	else
		return (0); // ft_others(list);
}