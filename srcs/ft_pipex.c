/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:17:23 by avillar           #+#    #+#             */
/*   Updated: 2022/08/22 09:32:26 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	make_fd(t_arg *tmp)
{
	int		x;
	int		rtn;
	char	*filename;

	rtn = 0;
	x = check_redir(tmp);
	while (tmp && (tmp->nbr != -1 && tmp->nbr != -2))
		tmp = tmp->next_arg;
	filename = ft_strdup(tmp->next_arg->arg);
	if (access(filename, R_OK | W_OK) != 0)
		rtn = open(filename, O_CREAT | O_RDWR);
	else if (x == -1)
		rtn = open(filename, O_RDWR | O_TRUNC);
	else if (x == -2)
		rtn = open(filename, O_RDWR | O_APPEND);
	return (rtn);
}

int	check_redir_pipe(t_llist *list, t_pipe *pip)
{
	t_arg	*tmp;
	t_cmd	*ctmp;
	int		i;

	i = 0;
	ctmp = list->first_cmd;
	while (++i < pip->x && ctmp)
		ctmp = ctmp->next_cmd;
	if (!ctmp->next_arg)
		return (-1);
	tmp = ctmp->next_arg;
	if (check_redir(tmp) == -1 || check_redir(tmp) == -2)
	{
		pip->fd = make_fd(tmp);
		if (pip->fd == -1)
			return (-1);
		else
			return (1);
	}
	else
		return (0);
}

void	pipex(t_llist *list, t_pipe *pip, int j, pid_t pid)
{
	int		status;
	t_cmd	*tmp;
	char	**arg_tab;

	tmp = list->first_cmd;
	while (tmp)
	{
		pip->cmd = get_cmd_name(tmp->cmd);
		arg_tab = make_arg_tab(tmp->next_arg, pip->cmd, 1, 1);
		pid = fork();
		if (pid == 0)
			child_manager(list, j, pip, arg_tab);
		else if (pid < 0)
			err_exit();
		tmp = tmp->next_cmd;
		pip->x++;
		j += 2;
		if (pip->cmd && not_builtins(pip) == 0 && ((cec(list, pip->cmd)) == 1))
			free (pip->cmd);
		if (arg_tab)
			free_arg_tab(arg_tab);
	}
	j = -1;
	while (++j < pip->npip + 1)
		wait(&status);
}

int	pipex_redir(t_cmd *cmd)
{
	int		fd;
	t_arg	*tmpa;
	int		x;

	x = 0;
	tmpa = cmd->next_arg;
	fd = check_redir(tmpa);
	if (fd < 0)
		return (x);
	else
		return (0);
}

int	main_pip(t_llist *list)
{
	t_pipe	*pip;
	pid_t	pid;

	pip = pip_init(list);
	if (!pip)
		exit (EXIT_FAILURE);
	pid = 0;
	init_pipe(pip);
	pipex(list, pip, 0, pid);
	ft_closing_end(pip);
	if (pip->end)
		free (pip->end);
	if (pip)
		free (pip);
	return (0);
}
