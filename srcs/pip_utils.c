/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pip_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:59:46 by avillar           #+#    #+#             */
/*   Updated: 2022/08/18 11:34:32 by avillar          ###   ########.fr       */
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

t_pipe	*pip_init(t_llist *list)
{
	t_pipe	*pip;
	int		end[count_pipe(list) * 2];

	pip = malloc(sizeof(t_pipe) * 1);
	pip->x = 1;
	pip->cmd = NULL;
	pip->npip = count_pipe(list);
	pip->fd = 0;
	pip->end = end;
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
