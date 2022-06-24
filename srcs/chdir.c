/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:18:06 by avillar           #+#    #+#             */
/*   Updated: 2022/06/24 12:34:42 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	ft_cd(t_llist *list)
{
	char	*dest;

	dest = list->first_cmd->next_arg->arg;
	if (strcmp(dest, "-") == 0 && list->lastpos)
		dest = list->lastpos;
	list->lastpos = NULL;
	list->lastpos = getcwd(list->lastpos, 0);
	if (chdir(dest) == -1)
	{
		write(2, list->first_cmd->cmd, ft_strlen(list->first_cmd->cmd));
		write(2, ": ", 2);
		write(2, dest, ft_strlen(dest));
		write(2, ": ", 2);
		perror("");
		return (-1);
	}
	return (0);
}