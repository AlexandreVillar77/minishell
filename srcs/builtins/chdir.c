/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 14:18:06 by avillar           #+#    #+#             */
/*   Updated: 2022/08/01 11:21:54 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

/*void	update_pwd(t_llist *list)
{
	
}*/

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
	int		i;

	i = 0;
	while (list->env[i])
	{
		printf("list->env = %s\n", list->env[i]);
		if (ft_strncmp(list->env[i], "OLDPWD", 6) == 0)
			return (get_afeq(list->env[i]));
		i++;
	}
	write(2, "cd: OLDPWD not set\n", 20);
	return (NULL);
}

int	ft_cd(t_llist *list)
{
	char	*dest;
	char	*tmp;

	dest = list->first_cmd->next_arg->arg;
	if (ft_strncmp(dest, "-", ft_strlen(dest)) == 0 && list->lastpos)
		dest = get_oldpwd(list);
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
	if (tmp)
	{
		list->lastpos = ft_strdup(tmp);
		free(tmp);
	}
	return (0);
}