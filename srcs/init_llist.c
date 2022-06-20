/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_llist.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/30 13:41:04 by thbierne          #+#    #+#             */
/*   Updated: 2022/06/13 14:05:39 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft/libft.h"

t_exe	*add_first_t_exe(char *str)
{
	t_exe	*new;

	new = (t_exe *)malloc(sizeof(t_exe));
	if (!new)
		return (NULL);
	new->name_exe = ft_strdup(str);
	new->next_exe = NULL;
	return (new);
}

t_exe	*add_last_t_exe(t_exe *list, char *str)
{
	t_exe	*new;
	t_exe	*tmp;

	new = (t_exe *)malloc(sizeof(t_exe));
	if (!new)
		return (NULL);
	new->name_exe = ft_strdup(str);
	new->next_exe = NULL;
	tmp = list;
	while (tmp->next_exe != NULL)
		tmp = tmp->next_exe;
	tmp->next_exe = new;
	return (list);
}

t_exe	*delete_first_t_exe(t_exe *list)
{
	t_exe	*cp;

	if (list != NULL)
	{
		cp = list->next_exe;
		free(list->name_exe);
		free(list);
		return (cp);
	}
	return (NULL);
}

/* 	alloue les cmd a coder ainsi que l'env	*/

t_llist	*init_llist(char **envp)
{
	t_llist	*list;

	list = (t_llist *)malloc(sizeof(t_llist));
	list->index = 0;
	list->new_cmd = 1;
	list->first_cmd = NULL;
	list->first_env = NULL;
	list->path = NULL;
	list->env = NULL;
	list->first_exe = add_first_t_exe("echo");
	list->first_exe = add_last_t_exe(list->first_exe, "cd");
	list->first_exe = add_last_t_exe(list->first_exe, "pwd");
	list->first_exe = add_last_t_exe(list->first_exe, "export");
	list->first_exe = add_last_t_exe(list->first_exe, "unset");
	list->first_exe = add_last_t_exe(list->first_exe, "env");
	list->first_exe = add_last_t_exe(list->first_exe, "exit");
	list->first_env = alloc_t_env(envp, list->first_env);
	list = alloc_path(list);
	list = llist_to_tab_env(list);
	return (list);
}
