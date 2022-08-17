/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:10:31 by avillar           #+#    #+#             */
/*   Updated: 2022/08/17 10:13:05 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	echo_noarg(t_cmd *cmd)
{
	if (!cmd->next_arg)
	{
		write(1, "\n", 1);
		return (0);
	}
	else if (cmd->next_arg)
	{
		if (cmd->next_arg->arg)
		{
			if (ft_strncmp(cmd->next_arg->arg, "-n", 2) == 0)
			{
				return (0);
			}
		}		
	}
	return (1);
}

int	check_echo_args(t_cmd *cmd)
{
	int		x;
	t_arg	*tmp;

	x = 0;
	if (!cmd->next_arg)
		return (0);
	tmp = cmd->next_arg;
	if (ft_strncmp(tmp->arg, "-n", ft_strlen(tmp->arg)) == 0)
		tmp = tmp->next_arg;
	while (tmp)
	{
		if (tmp->nbr > -1)
			x++;
		tmp = tmp->next_arg;
	}
	return (x);
}

int	ft_echo(t_cmd *cmd, int fd, int n)
{
	t_arg	*arg;
	t_arg	*filename;

	if (check_echo_args(cmd) == 0)
		if (echo_noarg(cmd) == 0)
			return (0);
	arg = cmd->next_arg;
	if (ft_strncmp(arg->arg, "-n", 2) == 0)
	{
		arg = arg->next_arg;
		n = 1;
	}
	fd = check_redir(arg);
	filename = arg;
	if (fd < 0)
	{
		while (filename->nbr > 0 && filename->next_arg)
			filename = filename->next_arg;
		if (filename->next_arg)
			filename = filename->next_arg;
	}
	echo_manage(arg, filename->arg, n, fd);
	return (0);
}
