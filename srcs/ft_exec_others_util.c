/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_others_util.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:36:44 by avillar           #+#    #+#             */
/*   Updated: 2022/08/22 09:15:16 by avillar          ###   ########.fr       */
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
		tmp = ft_strjoin(list->path[i], cmd);
		if (!cmd)
			break ;
		if (access(tmp, X_OK) == 0)
			execve(tmp, arg_tab, list->env);
		free (tmp);
	}
	if (list->path)
		ft_cmdnotf("command not found: ", list->first_cmd->cmd);
	else
		ft_cmdnotf2(list->first_cmd->cmd, " : No such file or directory\n");
	free_arg_tab(arg_tab);
	free (list->first_cmd);
	free_llist(list, NULL);
	free (cmd);
	exit (EXIT_FAILURE);
}
