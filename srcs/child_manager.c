/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:54:46 by avillar           #+#    #+#             */
/*   Updated: 2022/08/19 11:30:53 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_bypath(t_llist *list, t_pipe *pip, char **arg_tab)
{
	char	*cmd;
	int		i;

	i = -1;
	while (list->path != NULL && list->path[++i])
	{
		cmd = ft_strjoin(list->path[i], pip->cmd);
		if (!cmd)
			break ;
		if (access(cmd, X_OK) == 0)
			execve(cmd, arg_tab, list->env);
		free(cmd);
	}
	//free (pip->cmd);
	//crash_freed(&list, pip, arg_tab);
	exit (EXIT_FAILURE);
}

void	childpro1_bonus(t_llist *list, t_pipe *pip, char **arg_tab)
{
	t_cmd	*cmd;

	cmd = list->first_cmd;
	if (check_redir_pipe(list, pip) == 1)
	{
		if (dup2(pip->fd, STDOUT_FILENO) < 0)
			return (perror("Dup2: "));
	}
	else
		if (dup2(pip->end[1], STDOUT_FILENO) < 0)
			return (perror("Dup2: "));
	ft_closing_end(pip);
	if (our_built(list, pip, cmd) == 0)
		crash_freed2(&list, pip, arg_tab);
	if (!list->path && (ft_strncmp(cmd->cmd, "./", 2) == 0
			|| ft_strncmp(cmd->cmd, "/", 1) == 0))
		if (access(cmd->cmd, X_OK) == 0)
			execve(cmd->cmd, arg_tab, list->env);
	if (list->path)
		exec_bypath(list, pip, arg_tab);
	ft_cmdnotf2(cmd->cmd, " : No such file or directory\n");
	crash_freed(&list, pip, arg_tab);
	exit (EXIT_FAILURE);
}

void	childpro2_bonus(t_llist *list, t_pipe *pip, char **arg_tab, int j)
{
	t_cmd	*cmd;

	cmd = list->first_cmd;
	if (check_redir_pipe(list, pip) == 1)
	{
		if (dup2(pip->end[(j - 2)], STDIN_FILENO) < 0
			|| dup2(pip->fd, STDOUT_FILENO) < 0)
			return (perror("Dup2: "));
	}
	else
		if (dup2(pip->end[(j - 2)], STDIN_FILENO) < 0)
			return (perror("Dup2: "));
	ft_closing_end(pip);
	if (our_built(list, pip, cmd) == 0)
		crash_freed2(&list, pip, arg_tab);
	if (!list->path && (ft_strncmp(cmd->cmd, "./", 2) == 0
			||ft_strncmp(cmd->cmd, "/", 1) == 0))
		if (access(cmd->cmd, X_OK) == 0)
			execve(cmd->cmd, arg_tab, list->env);
	if (list->path)
		exec_bypath(list, pip, arg_tab);
	ft_cmdnotf2(cmd->cmd, " : No such file or directory\n");
	crash_freed(&list, pip, arg_tab);
	exit (EXIT_FAILURE);
}

void	childpro_bonus(t_llist *list, t_pipe *pip, char **arg_tab, int j)
{
	t_cmd	*cmd;

	cmd = list->first_cmd;
	if (check_redir_pipe(list, pip) == 1)
	{
		if ((dup2(pip->fd, 1) < 0) || (dup2(pip->end[j - 2], 0) < 0))
			return (perror("Dup2: "));
	}
	else
		if ((dup2(pip->end[j + 1], 1) < 0) || (dup2(pip->end[j - 2], 0) < 0))
			return (perror("Dup2: "));
	ft_closing_end(pip);
	if (our_built(list, pip, cmd) == 0)
		crash_freed2(&list, pip, arg_tab);
	if (!list->path && (ft_strncmp(cmd->cmd, "./", 2) == 0
			|| ft_strncmp(cmd->cmd, "/", 1) == 0))
		if (access(cmd->cmd, X_OK) == 0)
			execve(cmd->cmd, arg_tab, list->env);
	if (list->path)
		exec_bypath(list, pip, arg_tab);
	ft_cmdnotf2(cmd->cmd, " : No such file or directory\n");
	crash_freed(&list, pip, arg_tab);
	exit (EXIT_FAILURE);
}

void	child_manager(t_llist *list, int j, t_pipe *pip, char **arg_tab)
{
	if (j == 0)
	{
		childpro1_bonus(list, pip, arg_tab);
		exit(EXIT_SUCCESS);
	}
	else if (pip->x < count_cmds(list))
	{
		childpro_bonus(list, pip, arg_tab, j);
		exit(EXIT_SUCCESS);
	}
	else
	{
		childpro2_bonus(list, pip, arg_tab, j);
		exit(EXIT_SUCCESS);
	}
}
