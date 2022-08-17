/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/01 15:00:08 by thbierne          #+#    #+#             */
/*   Updated: 2022/08/17 11:37:29 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	len(char *str)
{
	int	i;

	if (!str)
		return (0);
	i = 0;
	while (str[i])
		i++;
	return (i);
}

void	print_tab(char **split)
{
	int	i;

	i = 0;
	while (split[i][0] != '\0')
	{
		printf("%s\n", split[i]);
		i++;
	}
}

void	print_t_exe(t_exe *list)
{
	t_exe	*tmp;

	tmp = list;
	while (tmp)
	{
		printf("%s\n", tmp->name_exe);
		tmp = tmp->next_exe;
	}
}

void	print_t_env(t_env *list)
{
	t_env	*tmp;

	tmp = list;
	while (tmp)
	{
		printf("%s%s\n", tmp->name, tmp->var);
		tmp = tmp->next_env;
	}
}

void	print_t_cmd(t_cmd *list)
{
	t_cmd	*tmp;
	t_arg	*cpy;

	tmp = list;
	while (tmp)
	{
		printf("cmd:%i=%s ", tmp->nbr, tmp->cmd);
		cpy = tmp->next_arg;
		while (cpy)
		{
			printf("arg:%i=%s ", cpy->nbr, cpy->arg);
			if (cpy->next_arg == NULL)
				break ;
			cpy = cpy->next_arg;
		}
		printf("\n");
		if (tmp->next_cmd == NULL)
			break ;
		tmp = tmp->next_cmd;
	}
}
