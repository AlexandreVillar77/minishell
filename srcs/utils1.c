/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/19 14:52:04 by thbierne          #+#    #+#             */
/*   Updated: 2022/06/13 14:04:58 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft/libft.h"

t_arg	*delete_first_t_arg(t_arg *list)
{
	t_arg	*cp;

	if (list != NULL)
	{
		cp = list->next_arg;
		free(list->arg);
		free(list);
		return (cp);
	}
	return (NULL);
}

int	test_check(char *line_read, int i)
{
	if (line_read[i] == '\'' || line_read[i] == '\"')
	{
		i = check_quote(line_read, i, line_read[i]);
		if (i == -1 || i == -2)
			return (i);
	}
	else if (line_read[i] == '<' || line_read[i] == '>')
	{
		i = check_red(line_read, i, line_read[i]);
		if (i == -3)
			return (i);
	}
	else if (line_read[i] == '|')
	{
		i = check_pipe(line_read, i, line_read[i]);
		if (i == -4)
			return (i);
	}
	return (i);
}

t_llist	*malloc_llist_to_tab_env(t_llist *list)
{
	t_env	*tmp;
	int		i;

	if (list->env)
		free(list->env);
	tmp = list->first_env;
	i = 1;
	while (tmp->next_env)
	{
		i++;
		tmp = tmp->next_env;
	}
	list->env = (char **)malloc(sizeof(char *) * (i + 1));
	return (list);
}

t_llist	*llist_to_tab_env(t_llist *list)
{
	char	*join;
	t_env	*tmp;
	int		i;

	list = malloc_llist_to_tab_env(list);
	if (!list->env)
		return (NULL);
	tmp = list->first_env;
	i = 0;
	while (tmp)
	{
		join = ft_strjoin(tmp->name, tmp->var);
		list->env[i++] = ft_strdup(join);
		free (join);
		tmp = tmp->next_env;
	}
	list->env[i] = (char *)malloc(sizeof(char) * 1);
	list->env[i][0] = '\0';
	return (list);
}
