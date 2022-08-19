/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 12:05:32 by thbierne          #+#    #+#             */
/*   Updated: 2022/08/19 12:09:00 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_cmd	*alloc_output2(t_cmd *cmd, char **output, int *y)
{
	if (cmd->nbr == -4)
		*y = 1;
	else
		*y = 0;
	cmd = del_cmd_for_redi(cmd, output);
	cmd = del_cmd_for_redi(cmd, output);
	return (cmd);
}

t_cmd	*alloc_output3(t_cmd *cmd, char **output, int *y)
{
	if (*output)
		free(*output);
	if (cmd->next_arg->nbr == -4)
		*y = 1;
	else
		*y = 0;
	*output = ft_strdup(cmd->next_arg->next_arg->arg);
	cmd->next_arg = delete_first_t_arg(cmd->next_arg);
	cmd->next_arg = delete_first_t_arg(cmd->next_arg);
	return (cmd);
}

t_arg	*alloc_output4(t_arg *arg_cpy, char **output, int *y)
{
	if (arg_cpy->next_arg
		&& (arg_cpy->next_arg->nbr == -3 || arg_cpy->next_arg->nbr == -4))
	{
		if (arg_cpy->next_arg->nbr == -4)
			*y = 1;
		else
			*y = 0;
		if (*output)
			free(*output);
		*output = ft_strdup(arg_cpy->next_arg->next_arg->arg);
		arg_cpy->next_arg = delete_first_t_arg(arg_cpy->next_arg);
		arg_cpy->next_arg = delete_first_t_arg(arg_cpy->next_arg);
	}
	else
		arg_cpy = arg_cpy->next_arg;
	return (arg_cpy);
}

t_cmd	*alloc_output(t_cmd *cmd, char **output, int *i)
{
	t_arg	*arg_cpy;
	int		y;

	y = 0;
	while (cmd->nbr == -3 || cmd->nbr == -4)
		cmd = alloc_output2(cmd, output, &y);
	while (cmd->next_arg
		&& (cmd->next_arg->nbr == -3 || cmd->next_arg->nbr == -4))
		cmd = alloc_output3(cmd, output, &y);
	arg_cpy = cmd->next_arg;
	while (arg_cpy)
		arg_cpy = alloc_output4(arg_cpy, output, &y);
	if (y == 1)
	{
		free(*output);
		*output = ft_strdup(".tmp");
		*i = *i + 1;
	}
	return (cmd);
}
