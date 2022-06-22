/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:19:50 by avillar           #+#    #+#             */
/*   Updated: 2022/06/22 15:16:14 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_pwd(t_llist *list)
{
	char	*path;
	t_arg	*tmp;

	if (list->first_cmd->next_arg)
		tmp = list->first_cmd->next_arg;
	else
		tmp = NULL;
	path = NULL;
	path = getcwd(path, 0);
	if (tmp)
	{
		if (check_redir(tmp) == -1)
			ft_redirection(path, tmp->next_arg->arg);
		if (check_redir(tmp) == -2)
			ft_redirection_appen(path, tmp->next_arg->arg);
	}
	else
		printf("%s\n", path);
	return (0);
}