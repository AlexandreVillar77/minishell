/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_err_code.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/22 09:09:51 by avillar           #+#    #+#             */
/*   Updated: 2022/08/22 09:31:54 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	cec(t_llist *list, char *cmd)
{
	char	*tmp;
	int		i;

	i = -1;
	if (!list->path || ft_strncmp(cmd, "./", 2) == 0
		|| ft_strncmp(cmd, "/", 1) == 0)
		if (access(cmd, X_OK) == 0)
			return (1);
	while (list->path && list->path[++i])
	{
		tmp = ft_strjoin(list->path[i], cmd);
		if (!cmd)
			break ;
		if (access(tmp, X_OK) == 0)
		{
			free (tmp);
			return (1);
		}
		free (tmp);
	}
	return (127);
}