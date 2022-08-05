/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:18:06 by avillar           #+#    #+#             */
/*   Updated: 2022/08/05 10:42:24 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

char	*get_pwd(t_llist *list)
{
	t_env	*tmp;

	tmp = list->first_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "PWD=", ft_strlen(tmp->name)) == 0)
			return (tmp->var);
		tmp = tmp->next_env;
	}
	return (NULL);
}

char	*get_afeq(char *str)
{
	int		i;
	int		x;
	char	*rtn;

	i = 0;
	x = 0;
	while (str[i] != '=')
		i++;
	i++;
	rtn = malloc(sizeof(char) * (ft_strlen(str) - i + 1));
	if (!rtn)
		exit (1);
	while (str[i])
	{
		rtn[x] = str[i];
		x++;
		i++;
	}
	rtn[x] = '\0';
	return (rtn);
}

char	*get_oldpwd(t_llist *list)
{
	t_env	*tmp;

	tmp = list->first_env;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "OLDPWD=", ft_strlen(tmp->name)) == 0)
			return (tmp->var);
		tmp = tmp->next_env;
	}
	write(2, "cd: OLDPWD not set\n", 20);
	return (NULL);
}

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

int	ft_cd(t_llist *list)
{
	char	*dest;
	char	*tmp;

	if (!list->first_cmd->next_arg)
		return (0);
	dest = list->first_cmd->next_arg->arg;
	if (ft_strncmp(dest, "-", ft_strlen(dest)) == 0)
		dest = getlsp(list);
	if (dest == NULL)
		return (0);
	tmp = NULL;
	tmp = getcwd(tmp, 0);
	if (tmp == NULL && ft_strncmp(dest, "..", ft_strlen(dest)) == 0)
		write(2, "cd: ..: No such file or directory\n", 35);
	else if (chdir(dest) == -1)
	{
		write(2, list->first_cmd->cmd, ft_strlen(list->first_cmd->cmd));
		write(2, ": ", 2);
		write(2, dest, ft_strlen(dest));
		write(2, ": ", 2);
		perror("");
		return (-1);
	}
	else
	{
		list->lastpos = ft_strdup(get_pwd(list));
		ft_update_PWD(&list);
	}
	if (tmp)
		free(tmp);
	return (0);
}