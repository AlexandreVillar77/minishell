/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/27 15:42:08 by avillar           #+#    #+#             */
/*   Updated: 2022/08/19 11:00:52 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_experror(t_arg *arg, int er)
{
	t_arg	*tmp;

	tmp = arg;
	if (er == 1 || (ft_isalpha(tmp->arg[0]) == 0))
	{
		write(2, "export: `", 9);
		write(2, tmp->arg, ft_strlen(tmp->arg));
		write(2, "': not a valid identifier\n", 26);
		return (1);
	}
	else
		return (0);
}

int	rtn_checker(t_cmd *cmd)
{
	cmd->next_arg = NULL;
	return (1);
}

int	export_fullchecker(t_llist *list, int x, t_arg *arg, t_cmd *cmd)
{
	int	n;

	n = 0;
	if (print_experror(arg, 0) == 1)
	{
		n = get_nbarg(cmd->next_arg);
		if (x == 0)
			cmd = del_arg(cmd);
		else
		{
			if (n == 2)
				arg = cmd->next_arg;
			cmd = delete_larg(x, cmd);
			if (n == 2)
				cmd->next_arg = arg;
		}
		LOL = 1;
		if (n == 1)
			return (rtn_checker(cmd));
		return (export_fullchecker(list, x, arg, cmd));
	}
	else if (arg->next_arg)
		return (export_fullchecker(list, ++x, arg->next_arg, cmd));
	else
		return (0);
}

int	ft_fullexport_part2(t_llist **list, t_arg *tmp)
{
	char	*name;

	while (tmp)
	{
		name = remove_p(recup_name(tmp));
		if (check_ifeq(tmp->arg) == 1)
		{
			if (exist_on_ex(name, (*list)->env) > -1)
				check_for_update(list, tmp, name);
			else
				(*list)->env = ft_ex_on_h((*list)->env, tmp, name);
			ft_export(list, &tmp, name);
		}
		else
			(*list)->env = ft_ex_on_h((*list)->env, tmp, name);
		tmp = tmp->next_arg;
		free (name);
	}
	return (0);
}

int	ft_fullexport(t_llist **list, t_cmd *cmd)
{
	t_arg	*tmp;

	if (cmd->next_arg)
	{
		if (export_redir_check(cmd) == 0)
		{
			print_export(*list, cmd);
			return (0);
		}
		else
			tmp = cmd->next_arg;
	}
	else
	{
		print_export(*list, cmd);
		return (0);
	}
	export_fullchecker(*list, 0, tmp, cmd);
	if (!cmd->next_arg)
		return (0);
	tmp = cmd->next_arg;
	ft_fullexport_part2(list, tmp);
	return (0);
}
