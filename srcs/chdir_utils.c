/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   chdir_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:02:38 by avillar           #+#    #+#             */
/*   Updated: 2022/08/19 11:05:36 by avillar          ###   ########.fr       */
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
	t_env		*tmp;
	static int	x;
	char		*rtn;

	x++;
	tmp = list->first_env;
	rtn = NULL;
	while (tmp)
	{
		if (ft_strncmp(tmp->name, "OLDPWD=", ft_strlen(tmp->name)) == 0)
		{
			rtn = malloc(sizeof(char) * (ft_strlen(tmp->var) + 1));
			ft_strlcpy(rtn, tmp->var, ft_strlen(tmp->var) + 1);
			return (rtn);
		}
		tmp = tmp->next_env;
	}
	if (x > 1)
		write(2, "cd: OLDPWD not set\n", 20);
	return (NULL);
}

int	rtn_print_errchdir(char *dest, char *tofree, t_cmd *cmd)
{
	write(2, cmd->cmd, ft_strlen(cmd->cmd));
	write(2, ": ", 2);
	write(2, dest, ft_strlen(dest));
	write(2, ": ", 2);
	perror("");
	free(tofree);
	LOL = 1;
	return (1);
}
