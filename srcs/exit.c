/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:51:38 by avillar           #+#    #+#             */
/*   Updated: 2022/08/19 10:54:44 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	numcheck(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_isdigit(str[i]) == 0)
			return (1);
		i++;
	}
	return (0);
}

int	exit_util(t_cmd *list, int x)
{
	if (numcheck(list->next_arg->arg) == 0)
	{
		if (list->next_arg->next_arg)
		{
			printf("exit : too many arguments\n");
			LOL = 1;
			return (1);
		}
		else
			x = ft_atoi(list->next_arg->arg);
	}
	else
	{
		printf("exit : %s", list->next_arg->arg);
		printf(": numeric argument required\n");
		x = 2;
	}
	return (x);
}

int	ft_exit(t_llist *list, t_cmd *cmd)
{
	int	x;

	x = 0;
	if (cmd->next_arg)
		x = exit_util(cmd, 0);
	free_llist_cmd(list);
	free_llist(list, NULL);
	exit (x);
}
