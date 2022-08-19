/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_other.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 13:26:31 by avillar           #+#    #+#             */
/*   Updated: 2022/08/18 13:19:20 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	**make_arg_tab(t_arg *arg, char *cmd, int i, int x)
{
	t_arg	*tmp;
	char	**rtn;

	tmp = arg;
	rtn = malloc(sizeof(char *) * (get_nbarg(arg) + 2));
	if (!rtn)
		exit (EXIT_FAILURE);
	rtn[0] = ft_cpy(cmd);
	while (i - 1 < get_nbarg(arg) && tmp->arg)
	{
		if (tmp->nbr > -1 || tmp->nbr == -3)
		{
			rtn[x] = ft_cpy(tmp->arg);
			x++;
		}
		else if (tmp->nbr < 0)
			i++;
		i++;
		if (tmp->next_arg)
			tmp = tmp->next_arg;
		else
			break ;
	}
	rtn[x] = NULL;
	return (rtn);
}

char	*get_cmd_name(char *str)
{
	char	*rtn;
	int		i;
	int		x;

	x = ft_strlen(str) - 1;
	i = 0;
	while (x >= 0 && str[x] != '/')
		x--;
	if (str[0] != '/')
		return (str);
	rtn = malloc(sizeof(char) * (ft_strlen(str) - x + 1));
	if (!rtn)
		exit (EXIT_FAILURE);
	x++;
	while (x < ft_strlen(str))
	{
		rtn[i] = str[x];
		i++;
		x++;
	}
	rtn[i] = '\0';
	return (rtn);
}

void	process01(t_llist *list, int fd, char *cmd, t_arg *tmp_arg)
{
	char	**arg_tab;

	arg_tab = make_arg_tab(tmp_arg, cmd, 1, 1);
	if (fd != 0)
		if (dup2(fd, STDOUT_FILENO) < 0)
			exit (EXIT_FAILURE);
	if (fd != 0)
		close (fd);
	if (!list->path || ft_strncmp(list->first_cmd->cmd, "./", 2) == 0
		|| ft_strncmp(list->first_cmd->cmd, "/", 1) == 0)
		if (access(list->first_cmd->cmd, X_OK) == 0)
			execve(list->first_cmd->cmd, arg_tab, list->env);
	exec_path_p1(list, arg_tab, cmd);
}

int	ft_exec_others(t_llist *list)
{
	int		fd;
	int		status;
	pid_t	child;
	t_arg	*tmp;
	char	*cmd;

	tmp = list->first_cmd->next_arg;
	fd = 0;
	if (check_redir(tmp) == -1 || check_redir(tmp) == -2)
		fd = get_fd(tmp);
	child = fork();
	if (child < 0)
		exit (EXIT_FAILURE);
	if (child == 0)
	{
		cmd = get_cmd_name(list->first_cmd->cmd);
		process01(list, fd, cmd, tmp);
		free (cmd);
	}
	if (fd != 0)
		close (fd);
	waitpid(child, &status, 0);
	if (status == 256)
		return (127);
	return (0);
}
