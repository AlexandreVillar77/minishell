/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:19:50 by avillar           #+#    #+#             */
/*   Updated: 2022/08/19 11:09:25 by avillar          ###   ########.fr       */
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

void	ft_update_pwd(t_llist **list)
{
	t_env	*tmp;
	char	*str;

	ft_update_oldpwd(list);
	str = NULL;
	str = getcwd(str, 0);
	tmp = (*list)->first_env;
	if (check_pwdexist(*list) == 0)
		return ;
	while (tmp && ft_strncmp(tmp->name, "PWD=", ft_strlen(tmp->name)) != 0)
		tmp = tmp->next_env;
	free(tmp->var);
	tmp->var = ft_strdup(str);
	if (str)
		free(str);
}

int	check_oldpwdexist(t_llist *list)
{
	t_env		*tmp;
	static int	i;

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

void	ft_update_oldpwd(t_llist **list)
{
	t_env		*tmp;

	tmp = (*list)->first_env;
	if (check_oldpwdexist(*list) == 0)
		return ;
	while (tmp && ft_strncmp(tmp->name, "OLDPWD=", ft_strlen(tmp->name)) != 0)
		tmp = tmp->next_env;
	if (tmp)
	{
		if (tmp->var)
			free(tmp->var);
		tmp->var = ft_strdup((*list)->lastpos);
	}
}

int	ft_pwd(t_cmd *cmd)
{
	char	*path;
	t_arg	*tmp;

	if (cmd->next_arg)
		tmp = cmd->next_arg;
	else
		tmp = NULL;
	path = NULL;
	path = getcwd(path, 0);
	if (!(path))
		print_err_path();
	else if ((check_redir(tmp)) == -1 || (check_redir(tmp)) == -2)
		pwd_redir(tmp, path);
	else
		printf("%s\n", path);
	if (path)
		free(path);
	return (0);
}
