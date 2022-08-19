/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pipex_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:49:56 by avillar           #+#    #+#             */
/*   Updated: 2022/08/19 12:22:05 by avillar          ###   ########.fr       */
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
	char	*tmp;

	tmp = ft_strjoin(str, name);
	f = ft_strjoin(tmp, "\n");
	write(STDERR_FILENO, f, ft_strlen(f));
	free(f);
	free(tmp);
}

void	ft_cmdnotf2(char *str, char *s2)
{
	char	*f;

	f = ft_strjoin(str, s2);
	write(STDERR_FILENO, f, ft_strlen(f));
	free(f);
}

int	our_built(t_llist *list, t_pipe *pip, t_cmd *cmd)
{
	if (ft_strncmp(pip->cmd, "echo", 5) == 0)
		return (ft_echo(cmd, 0, 0));
	else if ((ft_strncmp(pip->cmd, "env\0", 4)) == 0)
		return (ft_penv(list, cmd));
	else if (ft_strncmp(pip->cmd, "pwd", 4) == 0)
		return (ft_pwd(cmd));
	else if (ft_strncmp(pip->cmd, "cd", 3) == 0)
		return (ft_cd(list, cmd));
	else if (ft_strncmp(pip->cmd, "export", 7) == 0)
		return (ft_fullexport(&list, cmd));
	else if (ft_strncmp(pip->cmd, "unset", 6) == 0)
		return (ft_unset(list, cmd));
	else if (ft_strncmp(pip->cmd, "exit", 5) == 0)
		return (ft_exit(list, cmd));
	else
		return (-3);
}