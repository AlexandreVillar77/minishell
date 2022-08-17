/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fctnl_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:32:21 by avillar           #+#    #+#             */
/*   Updated: 2022/08/17 10:36:18 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_cmds(t_llist *list)
{
	int		i;
	t_cmd	*tmp;

	i = 0;
	tmp = list->first_cmd;
	while (tmp)
	{
		tmp = tmp->next_cmd;
		i++;
	}
	return (i);
}

char	*get_fd_name(t_arg *arg)
{
	t_arg	*tmp;

	tmp = arg;
	while (tmp->next_arg)
	{
		if (tmp->nbr > -3 && tmp->nbr < 0)
			break ;
		tmp = tmp->next_arg;
	}
	if (tmp->next_arg)
	{
		tmp = tmp->next_arg;
		return (tmp->arg);
	}
	else
		return (0);
}

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

int	return_free(int rtn, char *str)
{
	if (str)
		free(str);
	return (rtn);
}

int	fctnl_manager(t_llist *list)
{
	char	*cmd;

	cmd = ft_strdup(list->first_cmd->cmd);
	if (count_cmds(list) == 1)
	{
		if (strncmp(list->first_cmd->cmd, "echo", 5) == 0)
			return (return_free(ft_echo(list->first_cmd, 0, 0), cmd));
		if (strncmp(list->first_cmd->cmd, "cd", 3) == 0)
			return (return_free(ft_cd(list), cmd));
		if (strncmp(list->first_cmd->cmd, "pwd", 4) == 0)
			return (return_free(ft_pwd(list), cmd));
		if (strncmp(list->first_cmd->cmd, "export", 7) == 0)
			return (return_free(ft_fullexport(&list), cmd));
		if (strncmp(list->first_cmd->cmd, "unset", 7) == 0)
			return (return_free(ft_unset(list), cmd));
		if (strncmp(list->first_cmd->cmd, "env", 4) == 0)
			return (return_free(ft_penv(list), cmd));
		if (strncmp(list->first_cmd->cmd, "exit", 5) == 0)
			return (return_free(ft_exit(list), cmd));
		else
			return (return_free(ft_exec_others(list), cmd));
	}
	return_free(0, cmd);
	return (main_pip(list));
}
