/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:42:08 by avillar           #+#    #+#             */
/*   Updated: 2022/06/27 16:05:07 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_experror(t_arg *arg, int er)
{
	t_arg	*tmp;

	tmp = arg;
	if (ft_isdigit(tmp->arg[0]) == 1 || er == 1
		|| ft_isalpha(tmp->arg[0]) == 1)
	{
		write(2, "export: `", 9);
		write(2, tmp->arg, ft_strlen(tmp->arg));
		write(2, ": not a valid identifier", 24);
		write(2,"\n", 1);
	}
}

int	export_fullchecker(t_arg *arg)
{
		print_experror(arg, 0);
		if (arg->next_arg)
			return (export_fullchecker(arg->next_arg));
		else
			return (0);
}

int	export_checker(t_arg *arg)
{
	t_arg	*tmp;
	int		i;

	tmp = arg;
	i = 0;
	while (tmp->arg[i] && (tmp->arg[i] != '=' && tmp->arg[i] != '+'))
		i++;
	if (tmp->arg[i] == '\0')
		return (-1);
	else if (tmp->arg[i] == '+')
	{
		if (tmp->arg[i] == '+' && tmp->arg[i + 1] == '=')
			return (2);
		else if (tmp->arg[i] == '+' && tmp->arg[i + 1] != '=')
		{
			//print_experror(tmp, 1);
			return (-1);
		}
	}
	else if (tmp->arg[i] == '=')
		return (1);
	return (0);
}

int		ft_fullexport(t_llist **list)
{
	t_arg	*tmp;

	if ((*list)->first_cmd->next_arg)
		tmp = (*list)->first_cmd->next_arg;
	else
		return (0);
	export_fullchecker(tmp);
	while (tmp)
	{
		ft_export(list, &tmp);
		tmp = tmp->next_arg;
	}
	return (0);
}