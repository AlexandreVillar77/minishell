/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_other.C                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/30 13:26:31 by avillar           #+#    #+#             */
/*   Updated: 2022/06/30 17:29:58 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	get_fd(t_arg *arg)
{
	t_arg	*tmp;
	int		fd;

	tmp = arg;
	while (tmp->next_arg)
	{
		if (tmp->nbr == -1)
		{
			fd = open(get_fd_name(arg), O_RDWR | O_TRUNC);
			return (fd);
		}
		else if (tmp->nbr == -2)
		{
			fd = open(get_fd_name(arg), O_RDWR | O_APPEND);
			return (fd);
		}
		tmp = tmp->next_arg;
	}
	return (0);
}

int		get_nbarg(t_arg *arg)
{
	t_arg	*tmp;
	int		rtn;

	rtn = 0;
	tmp = arg;
	while (tmp)
	{
		rtn++;
		tmp = tmp->next_arg;
	}
	return (rtn);
}

char	*ft_cpy(char *src)
{
	int		i;
	char	*rtn;

	i = 0;
	rtn = malloc(sizeof(char) * (ft_strlen(src) + 1));
	if (!rtn)
		exit(EXIT_FAILURE);
	while (src[i])
	{
		rtn[i] = src[i];
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}

char	**make_arg_tab(t_arg *arg, char *cmd)
{
	t_arg	*tmp;
	int		i;
	char 	**rtn;

	i = 1;
	tmp = arg;
	rtn = malloc(sizeof(char*) * (get_nbarg(arg) + 2));
	if (!rtn)
		exit (EXIT_FAILURE);
	rtn[0] = ft_cpy(cmd);
	while (i - 1 < get_nbarg(arg) && tmp->arg)
	{
		rtn[i] = ft_cpy(tmp->arg);
		i++;
		if (tmp->next_arg)
			tmp = tmp->next_arg;
		else
			break ;
	}
	rtn[i] = NULL;
	return (rtn);
}

char	*get_cmd_name(char *str)
{
	char	*rtn;
	int		i;
	int		x;

	x = ft_strlen(str) - 1;
	i = 0;
	while (str[x] != '/')
		x--;
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

void		process01(t_llist *list, int fd, char *cmd, t_arg *tmp_arg)
{
	char	**arg_tab;
	int		i;

	i = 0;
	arg_tab = make_arg_tab(tmp_arg, cmd);
	if (fd != 0)
		if (dup2(fd, STDOUT_FILENO) < 0)
			exit (EXIT_FAILURE);
	if (fd != 0)
		close (fd);
	if (access(list->first_cmd->cmd, X_OK) == 0)
		execve(list->first_cmd->cmd, arg_tab,list->env);
	else
	{
		while (list->path[++i][0] && list->path != NULL)
		{
			cmd = ft_strjoin(list->path[i], get_cmd_name(list->first_cmd->cmd));
			if (!cmd)
				break ;
			if (access(cmd, X_OK) == 0)
				execve(cmd, arg_tab, list->env);
			free(cmd);
		}
	}
	printf("command not found: %s\n", list->first_cmd->cmd);
	free (arg_tab);
	exit (EXIT_FAILURE);
}

int	ft_exec_others(t_llist *list)
{
	int		fd;
	int		i;
	int		status;
	pid_t	child;
	t_arg	*tmp;

	tmp = list->first_cmd->next_arg;
	i = -1;
	fd = 0;
	if (check_redir(tmp) == -1 || check_redir(tmp) == -2)
		fd = get_fd(tmp);
	child = fork();
	if (child < 0)
		exit (EXIT_FAILURE);
	else if (child == 0)
		process01(list, fd, get_cmd_name(list->first_cmd->cmd), tmp);
	if (fd != 0)
		close (fd);
	waitpid(child, &status, 0);
	return (0);
}
