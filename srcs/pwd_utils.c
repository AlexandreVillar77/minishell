/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:17:02 by avillar           #+#    #+#             */
/*   Updated: 2022/08/18 09:47:39 by avillar          ###   ########.fr       */
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
	char	*filename;

	filename = get_fd_name(tmp);
	fd = check_redir(tmp);
	path = ft_strjoin(str, "\n");
	if (fd == -1)
		ft_redirection(path, filename);
	else if (fd == -2)
		ft_redirection_appen(path, filename);
	free (path);
}
