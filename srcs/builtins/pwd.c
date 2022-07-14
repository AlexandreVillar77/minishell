/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:19:50 by avillar           #+#    #+#             */
/*   Updated: 2022/07/14 17:03:19 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_pwd(t_llist *list)
{
	char	*path;
	t_arg	*tmp;
	int		fd;

	if (list->first_cmd->next_arg)
		tmp = list->first_cmd->next_arg;
	else
		tmp = NULL;
	(void)tmp;
	path = NULL;
	path = getcwd(path, 0);
	if (tmp)
	{
		fd = check_redir(tmp);
		if (fd == -1)
			ft_redirection(path, recup_argx(*(del_redir(tmp))));
		if (fd == -2)
			ft_redirection_appen(path, recup_argx(*(del_redir(tmp))));
	}
	else
		printf("%s\n", path);
	return (0);
}