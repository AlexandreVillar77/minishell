/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:17:02 by avillar           #+#    #+#             */
/*   Updated: 2022/08/17 11:24:58 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_err_path(void)
{
	write(2, "pwd: error retrieving current directory: ", 42);
	perror("getcwd: cannot access parent directories: ");
}

void	pwd_redir(t_arg *tmp, char *str)
{
	int		fd;
	char	*path;

	fd = check_redir(tmp);
	path = ft_strjoin(str, "\n");
	if (fd == -1)
		ft_redirection(path, recup_argx(*(del_redir(tmp))));
	else if (fd == -2)
		ft_redirection_appen(path, recup_argx(*(del_redir(tmp))));
}
