/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_llist_env.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/31 13:51:12 by thbierne          #+#    #+#             */
/*   Updated: 2022/06/13 14:19:02 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft/libft.h"

int		ft_strchr2(char *str, char c)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == c)
			return (i);
		i++;
	}
	if (c == '\0')
		return (i);
	return (-1);
}

t_env	*delete_first_t_env(t_env *list)
{
	t_env	*cp;

	if (list != NULL)
	{
		cp = list->next_env;
		free(list->name);
		free(list->var);
		free(list);
		return (cp);
	}
	return (NULL);
}

t_env	*add_var(t_env *new, char *str, int i)
{
	int	y;

	y = -1;
	while (++y <= i)
		new->name[y] = str[y];
	new->name[y] = '\0';
	while (str[i])
		i++;
	if (i == y)
	{
		new->var = NULL;
		return (new);
	}
	new->var = (char *)malloc(sizeof(char) * (i - y + 1));
	i = y;
	y = 0;
	while (str[i])
	{
		new->var[y] = str[i];
		y++;
		i++;
	}
	new->var[y] = '\0';
	return (new);
}

t_env	*add_t_env(t_env *list, char *str)
{
	int		i;
	t_env	*new;
	t_env	*tmp;

	new = (t_env *)malloc(sizeof(t_env));
	new->next_env = NULL;
	i = ft_strchr2(str, '=');
	new->name = (char *)malloc(sizeof(char) * (i + 2));
	new = add_var(new, str, i);
	if (list == NULL)
		return (new);
	tmp = list;
	while (tmp->next_env != NULL)
		tmp = tmp->next_env;
	tmp->next_env = new;
	return (list);
}

t_env	*alloc_t_env(char **envp, t_env *list)
{
	int	y;

	y = 1;
	list = add_t_env(list, envp[0]);
	while (envp[y])
	{
		list = add_t_env(list, envp[y]);
		y++;
	}
	return (list);
}

void	ft_set_base_env(t_env *envl)
{
	envl->name = NULL;
	envl->var = NULL;
	envl->next_env = NULL;
	add_t_env(envl, "PWD=");
	add_t_env(envl, "SHLVL=1");
	add_t_env(envl, "_=usr/bin/env");
}
