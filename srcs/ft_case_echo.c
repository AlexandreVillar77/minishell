/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_case_echo.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/12 14:13:36 by thbierne          #+#    #+#             */
/*   Updated: 2022/06/13 14:03:56 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft/libft.h"

t_llist	*alloc_flags_echo3(char *read_line, t_llist *list, int *z, t_cmd *tmp)
{
	int	y;

	y = list->index;
	y++;
	while (read_line[y] == 'n')
		y++;
	if (read_line[y] == ' ' || read_line[y] == '|' || read_line[y] == '<'
		|| read_line[y] == '>' || !read_line[y])
	{
		if (!tmp->next_arg)
			tmp->next_arg = add_first_t_arg("-n", 0);
		list->index = y;
	}
	else
		*z = -1;
	return (list);
}

t_llist	*alloc_flags_echo2(char *read_line, t_llist *list, int *z)
{
	t_cmd	*tmp;

	tmp = list->first_cmd;
	while (tmp->next_cmd)
		tmp = tmp->next_cmd;
	while (read_line[list->index] == ' ')
			list->index++;
	if (read_line[list->index] == '-' && read_line[list->index + 1] == 'n')
		list = alloc_flags_echo3(read_line, list, z, tmp);
	else
		*z = -1;
	return (list);
}

t_llist	*alloc_flags_echo(char *read_line, t_llist *list)
{
	int		y;
	t_cmd	*tmp;

	y = 0;
	tmp = list->first_cmd;
	while (tmp->next_cmd)
		tmp = tmp->next_cmd;
	while (read_line[list->index] != '|' && read_line[list->index] != '<'
		&& read_line[list->index] != '>' && read_line[list->index])
	{
		list = alloc_flags_echo2(read_line, list, &y);
		if (y == -1)
			break ;
	}
	return (list);
}

t_llist	*ft_case_echo(t_llist *list, char *read_line)
{
	t_cmd	*tmp;

	if (!list->first_cmd)
		list->first_cmd = add_first_t_cmd("echo", 0);
	else
		list->first_cmd = add_last_t_cmd(list->first_cmd, "echo", 0);
	tmp = list->first_cmd;
	while (tmp->next_cmd)
		tmp = tmp->next_cmd;
	while (read_line[list->index] == ' ')
		list->index++;
	if (read_line[list->index] == '-' && read_line[list->index + 1] == 'n'
		&& !tmp->next_arg)
		list = alloc_flags_echo(read_line, list);
	return (list);
}
