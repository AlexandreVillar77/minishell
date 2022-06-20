/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   alloc_redi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/25 13:03:40 by thbierne          #+#    #+#             */
/*   Updated: 2022/06/13 14:04:08 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft/libft.h"

char	*alloc_redi_cpy(t_llist *list, char *read_line, int *nb)
{
	char	*cpy;

	if (read_line[list->index] == '<' && read_line[list->index + 1] == '<')
	{
		cpy = ft_strdup("<<");
		*nb = -4;
	}
	else if (read_line[list->index] == '>' && read_line[list->index + 1] == '>')
	{
		cpy = ft_strdup(">>");
		*nb = -2;
	}
	else if (read_line[list->index] == '<')
	{
		cpy = ft_strdup("<");
		*nb = -3;
	}
	else
	{
		cpy = ft_strdup(">");
		*nb = -1;
	}
	return (cpy);
}

t_llist	*alloc_redi_cmd(t_llist *list, char *read_line)
{
	char	*cpy;
	int		nb;

	list->new_cmd = 0;
	cpy = alloc_redi_cpy(list, read_line, &nb);
	if (nb == -2 || nb == -4)
		list->index = list->index + 2;
	else
		list->index = list->index + 1;
	if (!list->first_cmd)
		list->first_cmd = add_first_t_cmd(cpy, nb);
	else
		list->first_cmd = add_last_t_cmd(list->first_cmd, cpy, nb);
	free(cpy);
	return (list);
}

t_llist	*alloc_redi_arg(t_llist *list, char *read_line)
{
	char	*cpy; 
	t_cmd	*cmd;
	int		nb;

	cpy = alloc_redi_cpy(list, read_line, &nb);
	if (nb == -2 || nb == -4)
		list->index = list->index + 2;
	else
		list->index = list->index + 1;
	cmd = list->first_cmd;
	while (cmd->next_cmd)
		cmd = cmd->next_cmd;
	if (!cmd->next_arg)
		cmd->next_arg = add_first_t_arg(cpy, nb);
	else
		cmd->next_arg = add_last_t_arg(cmd->next_arg, cpy, nb);
	free(cpy);
	return (list);
}
