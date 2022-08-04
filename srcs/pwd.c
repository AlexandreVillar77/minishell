/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:19:50 by avillar           #+#    #+#             */
/*   Updated: 2022/08/02 11:08:39 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_pwdexist(t_llist *list)
{
	t_env	*tmp;

	tmp = list->first_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "PWD=", ft_strlen(tmp->name)) == 0)
			return (1);
		tmp = tmp->next_env;
	}
	return (0);
}

void 	ft_update_PWD(t_llist **list)
{
	t_env	*tmp;
	char	*str;

	ft_update_OLDPWD(list);
	str = NULL;
	str = getcwd(str, 0);
	tmp = (*list)->first_env;
	if (check_pwdexist(*list) == 0)
		return ;
	while (tmp && ft_strncmp(tmp->name, "PWD=", ft_strlen(tmp->name)) != 0)
		tmp = tmp->next_env;
	tmp->var = ft_strdup(str);
	if (str)
		free(str);
}

int	check_oldpwdexist(t_llist *list)
{
	t_env		*tmp;
	static	int	i;

	i++;
	tmp = list->first_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "OLDPWD=", ft_strlen(tmp->name)) == 0)
			return (1);
		tmp = tmp->next_env;
	}
	if (i == 1)
		return (1);
	return (0);
}

void 	ft_update_OLDPWD(t_llist **list)
{
	t_env		*tmp;

	tmp = (*list)->first_env;
	if (check_oldpwdexist(*list) == 0)
		return ;
	while (tmp && ft_strncmp(tmp->name, "OLDPWD=", ft_strlen(tmp->name)) != 0)
		tmp = tmp->next_env;
	tmp->var = ft_strdup((*list)->lastpos);
}

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
	if (!(path))
	{
		write(2, "pwd: error retrieving current directory: ", 42);
		perror("getcwd: cannot access parent directories: ");
	}
	else if (tmp)
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