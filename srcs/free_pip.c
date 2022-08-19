/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_pip.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 15:34:54 by avillar           #+#    #+#             */
/*   Updated: 2022/08/19 11:30:35 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		not_builtins(t_pipe *pip)
{
	if (ft_strncmp(pip->cmd, "echo", 4) == 0)
		return (1);
	else if (ft_strncmp(pip->cmd, "env", 4) == 0)
		return (1);
	else if (ft_strncmp(pip->cmd, "pwd", 4) == 0)
		return (1);
	else if (ft_strncmp(pip->cmd, "cd", 3) == 0)
		return (1);
	else if (ft_strncmp(pip->cmd, "export", 7) == 0)
		return (1);
	else if (ft_strncmp(pip->cmd, "unset", 6) == 0)
		return (1);
	else if (ft_strncmp(pip->cmd, "exit", 5) == 0)
		return (1);
	else
		return (0);
}

void	crash_freed(t_llist **list, t_pipe *pip, char **arg_tab)
{
	free_arg_tab(arg_tab);
	free_llist(*list, NULL);
	free (pip->end);
	free (pip);
}

void	crash_freed2(t_llist **list, t_pipe *pip, char **arg_tab)
{
	free_arg_tab(arg_tab);
	*list = free_llist_cmd(*list);
	free_llist(*list, NULL);
	free (pip->end);
	free (pip);
	exit (EXIT_SUCCESS);
}