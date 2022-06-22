/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_llist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/07 11:14:51 by thbierne          #+#    #+#             */
/*   Updated: 2022/06/21 16:23:06 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	count_ac(t_cmd *cmd)
{
	t_arg	*arg_cpy;
	int		ac;

	ac = 1;
	arg_cpy = cmd->next_arg;
	if (!arg_cpy || (arg_cpy->nbr < 0))
		return (1);
	while (arg_cpy && arg_cpy->nbr > 0)
	{
		arg_cpy = arg_cpy->next_arg;
		ac++;
	}
	return (ac);
}

char	**conv_llist_cmd_tab(t_cmd *cmd, int *ac)
{
	t_arg	*arg_cpy;
	char	**arg;
	int		i;

	*ac = count_ac(cmd);
	arg = (char **)malloc(sizeof(char *) * (*ac + 1));
	if (!arg)
		return (NULL);
	arg[0] = ft_strdup(cmd->cmd);
	arg_cpy = cmd->next_arg;
	i = 1;
	while (i < *ac)
	{
		arg[i] = ft_strdup(arg_cpy->arg);
		i++;
		arg_cpy = arg_cpy->next_arg;
	}
	arg[i] = NULL;
	return (arg);
}

void	exec_llist(t_llist *list)
{
	t_cmd	*cmd_cpy;
	char	**arg;
	int		ac;
	int		i;
	
	cmd_cpy = list->first_cmd;
	while (cmd_cpy != NULL)
	{
		arg = conv_llist_cmd_tab(cmd_cpy, &ac);
		i = 0;
		while (i < ac)
			printf("%s ", arg[i++]);
		printf("\n");
		cmd_cpy = cmd_cpy->next_cmd;
	}
}