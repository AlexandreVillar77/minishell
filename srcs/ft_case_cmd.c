/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_case_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/18 15:51:33 by thbierne          #+#    #+#             */
/*   Updated: 2022/06/13 14:03:56 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft/libft.h"

t_llist	*ft_case_cmd_found(t_llist *list, char *cmd)
{
	if (!list->first_cmd)
		list->first_cmd = add_first_t_cmd(cmd, 0);
	else
		list->first_cmd = add_last_t_cmd(list->first_cmd, cmd, 0);
	return (list);
}

t_llist	*ft_check_cmd_path(t_llist *list, char *cpy)
{
	char	*tmp;

	tmp = NULL;
	if (!cpy[0])
	{
		list = ft_case_cmd_found(list, cpy);
		return (list);
	}
	tmp = ft_strdup(cpy);
	cpy = test_cmd(list, cpy);
	if (cpy == NULL)
	{
		list = ft_case_cmd_found(list, tmp);
		if (tmp)
			free(tmp);
		return (list);
	}
	free(tmp);
	list = ft_case_cmd_found(list, cpy);
	free(cpy);
	return (list);
}

t_llist	*list_cmd(t_llist *list, char *read_line, int count, char *str)
{
	if (count == 0)
		list = ft_case_echo(list, read_line);
	else if (count == 1)
		list = ft_case_cmd_found(list, "cd");
	else if (count == 2)
		list = ft_case_cmd_found(list, "pwd");
	else if (count == 3)
		list = ft_case_cmd_found(list, "export");
	else if (count == 4)
		list = ft_case_cmd_found(list, "unset");
	else if (count == 5)
		list = ft_case_cmd_found(list, "env");
	else if (count == 6)
		list = ft_case_cmd_found(list, "exit");
	else
		ft_check_cmd_path(list, str);
	return (list);
}

t_llist	*check_cmd(t_llist *list, char *line_read, char *str)
{
	t_exe	*tmp;
	int		count;
	int		y;

	tmp = list->first_exe;
	list->new_cmd = 0;
	count = 0;
	while (tmp)
	{
		y = 0;
		while (tmp->name_exe[y] == str[y] && tmp->name_exe[y])
			y++;
		if (!tmp->name_exe[y] && !str[y])
			break ;
		else
		{
			count++;
			tmp = tmp->next_exe;
		}
	}
	if (count >= 0 && count <= 6)
		free(str);
	list = list_cmd(list, line_read, count, str);
	return (list);
}
