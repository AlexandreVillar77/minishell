/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:53:32 by thbierne          #+#    #+#             */
/*   Updated: 2022/08/16 11:53:26 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_arg	**del_redir(t_arg *arg)
{
	t_arg *tmp;
	int		i;
	t_arg	**rtn;

	//i = count_redir(arg);
	tmp = arg;
	rtn = &tmp;
	while (i > 1 && (tmp->nbr == -1 || tmp->nbr == -2))
	{
		larg_del_first(&tmp);
		larg_del_first(&tmp);
		i--;
	}
	while (tmp->next_arg && i > 1)
	{
		if (tmp->next_arg->nbr == -1 || tmp->next_arg->nbr == -2)
		{
			larg_del_next(&tmp);
			larg_del_next(&tmp);
			i--;
		}
		else
			tmp = tmp->next_arg;
	}
	return (rtn);
}

int		ft_redirection(char *str, char *filename)
{
	int	file;

	if (!filename)
		return (-1);
	if (access(filename, R_OK | W_OK) != 0)
		file = open(filename, O_CREAT | O_RDWR);
	else
		file = open(filename, O_RDWR | O_TRUNC);
	if (file == -1)
		return (-1);
	write(file, str, len(str));
	close(file);
	return (0);
}

int		ft_redirection_appen(char *str, char *filename)
{
	int		file;

	if (!filename)
		return (-1);
	if (access(filename, R_OK | W_OK) != 0)
	{
		ft_redirection(str, filename);
		return (0);
	}
	else
		file = open(filename, O_RDWR | O_APPEND);
	if (file == -1)
		return (-1);
	write(file, str, ft_strlen(str));
	close(file);
	return (0);
}