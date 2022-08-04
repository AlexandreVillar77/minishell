/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/02 11:17:23 by avillar           #+#    #+#             */
/*   Updated: 2022/08/04 14:34:40 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	ft_closing_end(t_pipe *pip)
{
	int	t;

	t = pip->npip * 2;
	while (t > 0)
	{
		close(pip->end[t - 1]);
		t--;
	}
}

t_cmd	*get_t_cmd(t_llist *list, t_pipe *pip)
{
	t_cmd	*tmp;
	int		x;

	x = 1;
	tmp = list->first_cmd;
	while (tmp && x < pip->x)
	{
		//printf("tmp = %s\n", tmp->cmd);
		tmp = tmp->next_cmd;
		x++;
	}
	return (tmp);
}

int		exec_bypath(t_llist *list, t_pipe *pip, char **arg_tab)
{
	t_cmd	*cmd;
	int		i;

	i = -1;
	cmd = list->first_cmd;//get_t_cmd(list, pip);
	while (list->path[++i][0] && list->path != NULL)
	{
		pip->cmd = ft_strjoin(list->path[i], get_cmd_name(cmd->cmd));
		if (!pip->cmd)
			break ;
		if (access(pip->cmd, X_OK) == 0)
			execve(pip->cmd, arg_tab, list->env);
		free(pip->cmd);
	}
	printf("command not found: %s\n", list->first_cmd->cmd);
	free (arg_tab);
	exit (EXIT_FAILURE);
}

int	our_built(t_llist *list, t_pipe *pip)
{
	t_llist		*tmp;
	static int	i;

	tmp = list;
	i = 1;
	while (i < pip->x)
	{
		tmp->first_cmd = tmp->first_cmd->next_cmd;
		i++;
	}
	if (ft_strncmp(pip->cmd, "echo", 4) == 0)
		return (ft_echo(tmp->first_cmd));
	else if (ft_strncmp(pip->cmd, "env", 3) == 0)
		return (ft_penv(tmp));
	else if (ft_strncmp(pip->cmd, "pwd", 3) == 0)
		return (ft_pwd(tmp));
	else if (ft_strncmp(pip->cmd, "cd", 2) == 0)
		return (ft_cd(tmp));
	else if (ft_strncmp(pip->cmd, "export", 6) == 0)
		return (ft_fullexport(&tmp));
	else if (ft_strncmp(pip->cmd, "unset", 5) == 0)
		return (ft_unset(tmp));
	else if (ft_strncmp(pip->cmd, "exit", 4) == 0)
		return (ft_exit(list));
	else
		return (-3);
}

int	check_redir_pipe(t_llist *list, t_pipe *pip)
{
	t_arg	*tmp;
	char	*filename;

	if (!list->first_cmd->next_arg)
		return (-1);
	tmp = list->first_cmd->next_arg;
	if (check_redir(tmp) == -1)
	{
		while (tmp->nbr != -1)
			tmp = tmp->next_arg;
		filename = ft_strdup(tmp->next_arg->arg);
		printf("filename = %s\n", "ezrez");
		if (access(filename, R_OK | W_OK) != 0)
			pip->fd = open(filename, O_CREAT | O_RDWR);
		else
			pip->fd = open(filename, O_RDWR | O_TRUNC);
		if (pip->fd == -1)
			return (-1);
		else
			return (1);
	}
	else
		return (0);
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
	if (access(pip->cmd, X_OK) == 0)
		execve(pip->cmd, arg_tab, list->env);
	else
		exec_bypath(list, pip, arg_tab);
}

void	childpro2_bonus(t_llist *list, t_pipe *pip, char **arg_tab, int j)
{
	if (check_redir_pipe(list, pip) == 1)
	{
		if (dup2(pip->end[(j - 2)], STDIN_FILENO) < 0
			|| dup2(pip->fd, STDOUT_FILENO) < 0)
			write(2, "test\n", 5);
			return (perror("Dup2: "));
	}
	else
		if (dup2(pip->end[(j - 2)], STDIN_FILENO) < 0)
			return (perror("Dup2: "));
	ft_closing_end(pip);
	if (our_built(list, pip) == 0)
		exit (EXIT_SUCCESS);
	if (access(pip->cmd, X_OK) == 0)
		execve(pip->cmd, arg_tab, list->env);
	else
		exec_bypath(list, pip, arg_tab);
}

void    childpro_bonus(t_llist *list, t_pipe *pip, char **arg_tab, int j)
{
	if (check_redir_pipe(list, pip) == 1)
	{
		if ((dup2(pip->fd, STDOUT_FILENO) < 0) || (dup2(pip->end[j - 2], 0) < 0))
			return (perror("Dup2: "));
	}
	else
    	if ((dup2(pip->end[j + 1], 1) < 0) || (dup2(pip->end[j - 2], 0) < 0))
        	return (perror("Dup2: "));
	ft_closing_end(pip);
	if (our_built(list, pip) == 0)
		exit (EXIT_SUCCESS);
    else if (access(pip->cmd, X_OK) == 0)
        execve(pip->cmd, arg_tab, list->env);
    else
		exec_bypath(list, pip, arg_tab);
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

void	init_pipe(t_pipe *pip)
{
	int	i;

	i = -1;
	pip->end = malloc(sizeof(int) * (pip->npip * 2));
	if (!pip->end)
		return ;
	while (++i < pip->npip)
	{
		if (pipe(pip->end + i * 2) < 0)
		{
			perror ("couldn't pipe");
			exit (EXIT_FAILURE);
		}
	}
}


int	pipex(t_llist *list, t_pipe *pip)
{
	int		status;
	pid_t	pid;
	int		j;
	t_cmd	*tmp;
	char	**arg_tab;

	j = 0;
	tmp = list->first_cmd;
	init_pipe(pip);
	while (tmp)
	{
		pip->cmd = get_cmd_name(tmp->cmd);
		arg_tab = make_arg_tab(tmp->next_arg, pip->cmd);
		pid = fork();
		if (pid == 0)
			child_manager(list, j, pip, arg_tab);
		else if (pid < 0)
		{
			perror("error");
			exit(EXIT_FAILURE);
		}
		tmp = tmp->next_cmd;
		pip->x++;
		j += 2;
	}
	j = -1;
	ft_closing_end(pip);
	free(arg_tab);
	while (++j < pip->npip + 1)
		wait(&status);
	return (0);
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

int	count_pipe(t_llist *list)
{
	t_cmd	*tmp;
	int		x;

	x = 0;
	tmp = list->first_cmd;
	while (tmp)
	{
		x++;
		tmp = tmp->next_cmd;
	}
	return (x);
}

t_pipe	*pip_init(t_pipe *pip, t_llist *list)
{
	pip->x = 1;
	pip->cmd = get_cmd_name(list->first_cmd->cmd);
	pip->npip = count_pipe(list);
	pip->fd = 0;
	pip->end = malloc(sizeof(int) * (pip->npip * 2));
	return (pip);
}

int		main_pip(t_llist *list)
{
	t_pipe	*pip;

	pip = (t_pipe *)malloc(sizeof(t_pipe ));
	if (!pip)
		exit (EXIT_FAILURE);
	pip = pip_init(pip, list);
	pipex(list, pip);
	free(pip);
	return (0);
}
