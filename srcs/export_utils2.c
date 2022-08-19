/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:17:32 by avillar           #+#    #+#             */
/*   Updated: 2022/08/19 10:46:08 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*recup_name(t_arg *arg)
{
	int		size;
	char	*rtn;

	size = 0;
	while (arg->arg[size] && arg->arg[size] != '=')
		size++;
	rtn = malloc(sizeof(char) * (size + 1));
	if (!rtn)
		exit (EXIT_FAILURE);
	size = 0;
	while (arg->arg[size] && arg->arg[size] != '=' && arg->arg[size] != '+')
	{
		rtn[size] = arg->arg[size];
		size++;
	}
	rtn[size] = '\0';
	return (rtn);
}

char	*delete_equal(t_arg *arg, int i, int x)
{
	char	*rtn;

	rtn = malloc(sizeof(char) * (ft_strlen(arg->arg) - 1));
	if (!rtn)
		exit (EXIT_FAILURE);
	while (arg->arg[i] && arg->arg[i] != '=' && arg->arg[i] != '+')
	{
		rtn[x] = arg->arg[i];
		i++;
		x++;
	}
	if (i == '+')
		i++;
	i++;
	while (arg->arg[i])
	{
		rtn[x] = arg->arg[i];
		i++;
		x++;
	}
	rtn[x] = '\0';
	return (rtn);
}

int	check_ifeq(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (1);
		i++;
	}
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
			print_experror(tmp, 1);
			LOL = 1;
			return (-1);
		}
	}
	else if (tmp->arg[i] == '=')
		return (1);
	return (0);
}

int	export_redir_check(t_cmd *cmd)
{
	t_arg	*tmp;

	tmp = cmd->next_arg;
	if (get_nbarg(tmp) != 2)
		return (1);
	if (ft_strncmp(tmp->arg, ">>", ft_strlen(tmp->arg)) != 0)
		return (1);
	return (0);
}
