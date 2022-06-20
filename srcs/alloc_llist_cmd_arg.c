/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_llist_cmd_arg.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 15:38:25 by thbierne          #+#    #+#             */
/*   Updated: 2022/06/13 14:04:03 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft/libft.h"

t_cmd	*add_first_t_cmd(char *str, int nbr)
{
	t_cmd	*new;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->nbr = nbr;
	new->cmd = ft_strdup(str);
	new->next_cmd = NULL;
	new->next_arg = NULL;
	return (new);
}

t_cmd	*add_last_t_cmd(t_cmd *list, char *str, int nbr)
{
	t_cmd	*new;
	t_cmd	*tmp;

	new = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new)
		return (NULL);
	new->nbr = nbr;
	new->cmd = ft_strdup(str);
	new->next_cmd = NULL;
	new->next_arg = NULL;
	tmp = list;
	while (tmp->next_cmd != NULL)
		tmp = tmp->next_cmd;
	tmp->next_cmd = new;
	return (list);
}

t_cmd	*delete_first_t_cmd(t_cmd *list)
{
	t_cmd	*cp;

	if (list != NULL)
	{
		cp = list->next_cmd;
		free(list->cmd);
		free(list);
		return (cp);
	}
	return (NULL);
}

t_arg	*add_first_t_arg(char *str, int nbr)
{
	t_arg	*new;

	new = (t_arg *)malloc(sizeof(t_arg));
	if (!new)
		return (NULL);
	if (nbr >= 0)
		nbr++;
	new->nbr = nbr;
	new->arg = ft_strdup(str);
	new->next_arg = NULL;
	return (new);
}

t_arg	*add_last_t_arg(t_arg *list, char *str, int nbr)
{
	t_arg	*new;
	t_arg	*tmp;
	int		type;

	new = (t_arg *)malloc(sizeof(t_arg));
	if (!new)
		return (NULL);
	type = nbr + 2;
	new->arg = ft_strdup(str);
	new->next_arg = NULL;
	tmp = list;
	while (tmp->next_arg != NULL)
	{
		tmp = tmp->next_arg;
		type++;
	}
	if (nbr < 0)
		new->nbr = nbr;
	else
		new->nbr = type;
	tmp->next_arg = new;
	return (list);
}
