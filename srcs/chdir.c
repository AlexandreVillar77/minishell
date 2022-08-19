/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:18:06 by avillar           #+#    #+#             */
/*   Updated: 2022/08/19 11:05:45 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*getlsp(t_llist *list)
{
	if (!list->lastpos)
	{
		write(2, "cd: OLDPWD not set\n", 20);
		return (NULL);
	}
	else
	{
		printf("%s\n", list->lastpos);
		return (list->lastpos);
	}
}

int	cd_alone(t_llist *list)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = list->first_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "HOME=", ft_strlen(tmp->name)) == 0)
		{
			i = 1;
			break ;
		}
		tmp = tmp->next_env;
	}
	if (i == 1)
	{
		chdir(tmp->var);
		free(list->lastpos);
		list->lastpos = ft_strdup(get_pwd(list));
		ft_update_pwd(&list);
	}
	else
		write (2, "cd: HOME not set\n", 17);
	return (i);
}

int	ft_cd(t_llist *list, t_cmd *cmd)
{
	char	*dest;
	char	*tmp;

	if (!cmd->next_arg)
		return (cd_alone(list));
	dest = cmd->next_arg->arg;
	if (ft_strncmp(dest, "-", ft_strlen(dest)) == 0)
		dest = getlsp(list);
	if (dest == NULL)
		return (0);
	tmp = NULL;
	tmp = getcwd(tmp, 0);
	if (tmp == NULL && ft_strncmp(dest, "..", ft_strlen(dest)) == 0)
		write(2, "cd: ..: No such file or directory\n", 35);
	else if (chdir(dest) == -1)
		return (rtn_print_errchdir(dest, tmp, cmd));
	else
	{
		free(list->lastpos);
		list->lastpos = ft_strdup(get_pwd(list));
		ft_update_pwd(&list);
	}
	if (tmp)
		free(tmp);
	return (0);
}
