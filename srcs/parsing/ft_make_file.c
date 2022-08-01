/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_make_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 15:18:43 by avillar           #+#    #+#             */
/*   Updated: 2022/06/23 15:00:22 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*recup_argx(t_arg *arg)
{
	t_arg	*tmp;

	tmp = arg;
	return (tmp->next_arg->arg);
}

int	ft_make_file(char *filename)
{
	int	file;

	if (!filename)
		return (-1);
	if (access(filename, R_OK | W_OK) != 0)
		file = open(filename, O_CREAT | O_WRONLY);
	else
		file = open(filename, O_RDONLY | O_WRONLY | O_TRUNC);
	if (file == -1)
		return (-1);
	close(file);
	return (0);
}