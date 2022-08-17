/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:59:46 by avillar           #+#    #+#             */
/*   Updated: 2022/08/17 12:41:36 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

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

void	err_exit(void)
{
	perror("error");
	exit(EXIT_FAILURE);
}

void	free_arg_tab(char **arg_tab)
{
	int	i;

	i = 0;
	if (ft_tablen(arg_tab) == 0)
	{
		free (arg_tab[0]);
		free (arg_tab);
		return ;
	}
	while (arg_tab[i])
	{
		free (arg_tab[i]);
		i++;
	}
	free (arg_tab);
}
