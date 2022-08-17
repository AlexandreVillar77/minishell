/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 11:29:33 by avillar           #+#    #+#             */
/*   Updated: 2022/08/17 13:36:18 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fulltriche(t_llist **list, int x, int size)
{
	char	*tmp;

	if (x == (size - 1))
	{
		free ((*list)->env[size]);
		free ((*list)->env[size - 1]);
		(*list)->env[size - 1] = NULL;
	}
	else
	{
		tmp = ft_strdup((*list)->env[x]);
		free ((*list)->env[x]);
		(*list)->env[x] = ft_strdup((*list)->env[size - 1]);
		free ((*list)->env[size - 1]);
		free ((*list)->env[size]);
		free (tmp);
		(*list)->env[size - 1] = NULL;
	}
}

void	unset_export(t_llist *list, int x, int size)
{
	fulltriche(&list, x, size);
	if (!(list->env))
		exit (EXIT_FAILURE);
}

int	nameeq(char *str, char *name)
{
	int	i;

	i = 0;
	while (str[i] != '=' && str[i] && name[i])
	{
		if (str[i] != name[i])
			return (-1);
		i++;
	}
	return (0);
}

void	on_export(t_llist *list, t_arg *arg)
{
	int		i;
	char	*name;

	i = -1;
	name = recup_name(arg);
	while (list->env[++i])
	{
		if (((nameeq(list->env[i], name)) == 0))
		{
			unset_export(list, i, ft_tablen(list->env));
			break ;
		}
	}
	free (name);
}

int	is_target(t_env *tmp, t_llist **list, t_arg *arg, int x)
{
	int			i;

	i = 0;
	if (ft_strncmp(tmp->name, arg->arg, ft_strlen(tmp->name) - 1) == 0)
	{
		if (x == 0)
			*list = del_env(*list, 0);
		else
			*list = delete_lenv(x, *list, 0);
		i = 1;
	}
	return (i);
}
