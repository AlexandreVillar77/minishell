/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   manage_redi.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/16 09:38:25 by thbierne          #+#    #+#             */
/*   Updated: 2022/08/18 11:10:30 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int		count_redir(t_cmd *cmd)
{
	int		x;
	t_arg	*tmp;

	x = 0;
	tmp = cmd->next_arg;
	if (cmd->nbr == -1 || cmd->nbr == -2)
		x++;
	while (tmp)
	{
		if (tmp->nbr == -1 || tmp->nbr == -2)
			x++;
		tmp = tmp->next_arg;
	}
	return (x);
}

t_llist	*del_redirection(t_llist *list)
{
	t_cmd	*cmd_cpy;
	t_arg	*arg_cpy;
	int 	i;

	cmd_cpy = list->first_cmd;
	while (cmd_cpy)
	{
		if (cmd_cpy->next_arg)
		{
			//i = count_redir(cmd_cpy->next_arg);
			if (cmd_cpy->next_arg && (cmd_cpy->next_arg->nbr == -1 || cmd_cpy->next_arg->nbr == -2))
			{
				while ((cmd_cpy->next_arg->nbr == -1 || cmd_cpy->next_arg->nbr == -2) && i > 1)
				{
					cmd_cpy = larg_del_f(cmd_cpy);
					cmd_cpy = larg_del_f(cmd_cpy);
					i--;
				}
			}
			else if (i > 1)
			{
				arg_cpy = cmd_cpy->next_arg;
				while (arg_cpy->next_arg && i > 1)
				{
					if ((arg_cpy->next_arg->nbr == -1 || arg_cpy->next_arg->nbr == -2) && i > 1)
					{
						//arg_cpy = larg_del_n(arg_cpy);
						//arg_cpy = larg_del_n(arg_cpy);
						i--;
					}
					else
						arg_cpy = arg_cpy->next_arg;
				}
			}
		}
		cmd_cpy = cmd_cpy->next_cmd;
	}
	return (list);
}

/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */
/* ************************************************************************** */

t_cmd	*del_cmd_for_redi(t_cmd *cmd, char **output)
{
	t_arg	*cpy;

	if (cmd)
	{
		if (*output)
		{
			free(*output);
			*output = NULL;
		}
		*output = ft_strdup(cmd->cmd);
		cpy = cmd->next_arg;
		cmd->next_arg = cmd->next_arg->next_arg;
		cmd->nbr = cpy->nbr;
		free(cmd->cmd);
		cmd->cmd = ft_strdup(cpy->arg);
		free(cpy->arg);
		free(cpy);
		return (cmd);
	}
	return (NULL);
}

t_arg	*del_arg_for_redi(t_arg *arg, char **output)
{
	t_arg	*cpy;

	if (arg)
	{
		if (*output)
		{
			free(*output);
			*output = NULL;
		}
		*output = ft_strdup(arg->arg);
		free(arg->arg);
		cpy = arg->next_arg;
		arg->next_arg = arg->next_arg->next_arg;
		arg->nbr = cpy->nbr;
		arg->arg = ft_strdup(cpy->arg);
		free(cpy->arg);
		free(cpy);
		return (arg);
	}
	return (NULL);
}

t_llist	*manage_redi(t_llist *list)
{
	t_cmd	*cmd_cpy;
	char	*input;
	char	*output;
	int		i;

	input = NULL;
	output = NULL;
	i = 0;
	cmd_cpy = list->first_cmd;
	while (cmd_cpy)
	{
		cmd_cpy = alloc_output(cmd_cpy, &output, &i);
		cmd_cpy = alloc_input(cmd_cpy, &input);
		cmd_cpy = put_redi_for_cmd(cmd_cpy, &input, &output);
		cmd_cpy = cmd_cpy->next_cmd;
	}
	return (list);
}

t_cmd	*alloc_output(t_cmd *cmd, char **output, int *i)
{
	t_arg	*arg_cpy;
	int		y;

	y = 0;
	while (cmd->nbr == -3 || cmd->nbr == -4)
	{
		if (cmd->nbr == -4)
			y = 1;
		else
			y = 0;
		cmd = del_cmd_for_redi(cmd, output);
		cmd = del_cmd_for_redi(cmd, output);
	}
	while (cmd->next_arg && (cmd->next_arg->nbr == -3 || cmd->next_arg->nbr == -4))
	{
		if (*output)
			free(*output);
		if (cmd->next_arg->nbr == -4)
			y = 1;
		else
			y = 0;
		*output = ft_strdup(cmd->next_arg->next_arg->arg);
		cmd->next_arg = delete_first_t_arg(cmd->next_arg);
		cmd->next_arg = delete_first_t_arg(cmd->next_arg);
	}
	arg_cpy = cmd->next_arg;
	while (arg_cpy)
	{
		if (arg_cpy->next_arg && (arg_cpy->next_arg->nbr == -3 || arg_cpy->next_arg->nbr == -4))
		{
			if (arg_cpy->next_arg->nbr == -4)
				y = 1;
			else
				y = 0;
			if (*output)
				free(*output);
			*output = ft_strdup(arg_cpy->next_arg->next_arg->arg);
			arg_cpy->next_arg = delete_first_t_arg(arg_cpy->next_arg);
			arg_cpy->next_arg = delete_first_t_arg(arg_cpy->next_arg);
		}
		else
			arg_cpy = arg_cpy->next_arg;
	}
	if (y == 1)
	{
		free(*output);
		*output = ft_strdup(".tmp");
		*i = *i + 1;
	}
	return (cmd);
}

t_cmd	*alloc_input(t_cmd *cmd, char **input)
{
	t_arg	*arg_cpy;
	int		i;

	i = count_redir(cmd);
	if (*input)
	{
		free(*input);
		*input = NULL;
	}
	while (cmd->nbr == -1 || cmd->nbr == -2)
	{
		cmd = del_cmd_for_redi(cmd, input);
		cmd = del_cmd_for_redi(cmd, input);
		i--;
	}
	arg_cpy = cmd->next_arg;
	while (arg_cpy)
	{
		while ((arg_cpy->nbr == -1 || arg_cpy->nbr == -2) && i > 1)
		{
			arg_cpy = del_arg_for_redi(arg_cpy, input);
			arg_cpy = del_arg_for_redi(arg_cpy, input);
			i--;
		}
		arg_cpy = arg_cpy->next_arg;
	}
	return (cmd);
}

t_cmd	*put_redi_for_cmd(t_cmd *cmd, char **input, char **output)
{
	if (*output)
	{
		if (cmd->next_arg && (cmd->next_arg->nbr == -1 || cmd->next_arg->nbr == -2))
		{
			
			cmd->next_arg = add_last_t_arg(cmd->next_arg, cmd->next_arg->next_arg->arg , 0);
			free(cmd->next_arg->arg);
			cmd->next_arg->arg = ft_strdup(*output);
			cmd->next_arg->next_arg->nbr = cmd->next_arg->nbr;
			cmd->next_arg->nbr = -3;
		}
		else if (!cmd->next_arg)
			cmd->next_arg = add_first_t_arg(*output, -3);
		free(*output);
		*output = NULL;
	}
	if (*input)
	{
		free(*input);
		*input = NULL;
	}
	return (cmd);
}