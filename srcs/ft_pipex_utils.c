/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:49:56 by avillar           #+#    #+#             */
/*   Updated: 2022/08/17 10:52:15 by avillar          ###   ########.fr       */
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
		tmp = tmp->next_cmd;
		x++;
	}
	return (tmp);
}

void	ft_cmdnotf(char *str, char *name)
{
	char	*f;

	f = ft_strjoin(str, name);
	f = ft_strjoin(f, "\n");
	write(STDERR_FILENO, f, ft_strlen(f));
	free(f);
}

void	ft_cmdnotf2(char *str, char *s2)
{
	char	*f;

	f = ft_strjoin(str, s2);
	write(STDERR_FILENO, f, ft_strlen(f));
	free(f);
}

int	our_built(t_llist *list, t_pipe *pip)
{
	t_llist		*tmp;
	static int	i;

	tmp = list;
	i = 0;
	while (++i < pip->x)
		tmp->first_cmd = tmp->first_cmd->next_cmd;
	if (ft_strncmp(pip->cmd, "echo", 4) == 0)
		return (ft_echo(tmp->first_cmd, 0, 0));
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
