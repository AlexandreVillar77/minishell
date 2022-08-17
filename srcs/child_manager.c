/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child_manager.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:54:46 by avillar           #+#    #+#             */
/*   Updated: 2022/08/17 12:34:44 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	exec_bypath(t_llist *list, t_pipe *pip, char **arg_tab)
{
	t_cmd	*cmd;
	int		i;

	i = -1;
	cmd = list->first_cmd;
	while (list->path != NULL && list->path[++i][0])
	{
		pip->cmd = ft_strjoin(list->path[i], get_cmd_name(cmd->cmd));
		if (!pip->cmd)
			break ;
		if (access(pip->cmd, X_OK) == 0)
			execve(pip->cmd, arg_tab, list->env);
		free(pip->cmd);
	}
	ft_cmdnotf("command not found: ", list->first_cmd->cmd);
	LOL -= LOL;
	LOL += 127;
	free_arg_tab(arg_tab);
	exit (EXIT_FAILURE);
}

void	childpro1_bonus(t_llist *list, t_pipe *pip, char **arg_tab)
{
	if (check_redir_pipe(list, pip) == 1)
	{
		if (dup2(pip->fd, STDOUT_FILENO) < 0)
			return (perror("Dup2: "));
	}
	else
		if (dup2(pip->end[1], STDOUT_FILENO) < 0)
			return (perror("Dup2: "));
	ft_closing_end(pip);
	if (our_built(list, pip) == 0)
		exit (EXIT_SUCCESS);
	if (!list->path && (ft_strncmp(list->first_cmd->cmd, "./", 2) == 0
			|| ft_strncmp(list->first_cmd->cmd, "/", 1) == 0))
		if (access(list->first_cmd->cmd, X_OK) == 0)
			execve(list->first_cmd->cmd, arg_tab, list->env);
	if (list->path)
		exec_bypath(list, pip, arg_tab);
	free_arg_tab(arg_tab);
	ft_cmdnotf2(list->first_cmd->cmd, " : No such file or directory\n");
	LOL -= LOL;
	LOL += 127;
	exit (EXIT_FAILURE);
}

void	childpro2_bonus(t_llist *list, t_pipe *pip, char **arg_tab, int j)
{
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
	if (our_built(list, pip) == 0)
		exit (EXIT_SUCCESS);
	if (!list->path && (ft_strncmp(list->first_cmd->cmd, "./", 2) == 0
			||ft_strncmp(list->first_cmd->cmd, "/", 1) == 0))
		if (access(list->first_cmd->cmd, X_OK) == 0)
			execve(list->first_cmd->cmd, arg_tab, list->env);
	if (list->path)
		exec_bypath(list, pip, arg_tab);
	ft_cmdnotf2(list->first_cmd->cmd, " : No such file or directory\n");
	free_arg_tab(arg_tab);
	LOL -= LOL;
	LOL += 127;
	exit (EXIT_FAILURE);
}

void	childpro_bonus(t_llist *list, t_pipe *pip, char **arg_tab, int j)
{
	if (check_redir_pipe(list, pip) == 1)
	{
		if ((dup2(pip->fd, 1) < 0) || (dup2(pip->end[j - 2], 0) < 0))
			return (perror("Dup2: "));
	}
	else
		if ((dup2(pip->end[j + 1], 1) < 0) || (dup2(pip->end[j - 2], 0) < 0))
			return (perror("Dup2: "));
	ft_closing_end(pip);
	if (our_built(list, pip) == 0)
		exit (EXIT_SUCCESS);
	if (!list->path && (ft_strncmp(list->first_cmd->cmd, "./", 2) == 0
			|| ft_strncmp(list->first_cmd->cmd, "/", 1) == 0))
		if (access(list->first_cmd->cmd, X_OK) == 0)
			execve(list->first_cmd->cmd, arg_tab, list->env);
	if (list->path)
		exec_bypath(list, pip, arg_tab);
	ft_cmdnotf2(list->first_cmd->cmd, " : No such file or directory\n");
	free_arg_tab(arg_tab);
	LOL -= LOL;
	LOL += 127;
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
