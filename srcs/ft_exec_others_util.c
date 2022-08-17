/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_others_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:36:44 by avillar           #+#    #+#             */
/*   Updated: 2022/08/17 12:29:04 by avillar          ###   ########.fr       */
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

int	get_nbarg(t_arg *arg)
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

void	exec_path_p1(t_llist *list, char **arg_tab, char *cmd)
{
	int		i;
	char	*tmp;

	i = -1;
	while (list->path && list->path[++i])
	{
		tmp = get_cmd_name(list->first_cmd->cmd);
		cmd = ft_strjoin(list->path[i], tmp);
		free (tmp);
		if (!cmd)
			break ;
		if (access(cmd, X_OK) == 0)
			execve(cmd, arg_tab, list->env);
		free (cmd);
	}
	if (list->path)
		ft_cmdnotf("command not found: ", list->first_cmd->cmd);
	else
		ft_cmdnotf2(list->first_cmd->cmd, " : No such file or directory\n");
	LOL = 127;
	free (arg_tab);
	exit (EXIT_FAILURE);
}
