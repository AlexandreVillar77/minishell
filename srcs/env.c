/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 12:04:32 by avillar           #+#    #+#             */
/*   Updated: 2022/08/17 10:14:22 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	print_env0(t_env *tmp)
{
	while (tmp)
	{
		write(1, tmp->name, ft_strlen(tmp->name));
		write(1, tmp->var, ft_strlen(tmp->var));
		write(1, "\n", 1);
		tmp = tmp->next_env;
	}
}

int	env_size(t_env *env)
{
	t_env	*tmp;
	int		i;

	i = 0;
	tmp = env;
	while (tmp)
	{
		i += ft_strlen(tmp->name);
		i += ft_strlen(tmp->var);
		i += 2;
		tmp = tmp->next_env;
	}
	return (i);
}

void	print_env_fd(t_env *tmp, char *filename, int red)
{
	int		size;
	char	*content;

	size = env_size(tmp);
	content = malloc(sizeof(char) * (size + 1));
	if (!content)
		exit (1);
	while (tmp)
	{
		content = ft_strjoin(content, tmp->name);
		content = ft_strjoin(content, tmp->var);
		content = ft_strjoin(content, "\n");
		tmp = tmp->next_env;
	}
	if (red == -1)
		ft_redirection(content, filename);
	else if (red == -2)
		ft_redirection_appen(content, filename);
	free(content);
}

int	ft_penv(t_llist *list)
{
	int		fd;
	t_env	*tmp;
	t_arg	*filename;

	fd = 0;
	if (list->first_cmd->next_arg)
	{
		filename = list->first_cmd->next_arg;
		fd = check_redir(list->first_cmd->next_arg);
		if (fd < 0)
		{
			while (filename->nbr > 0)
				filename = filename->next_arg;
			filename = filename->next_arg;
		}
	}
	tmp = list->first_env;
	if (fd == 0)
		print_env0(tmp);
	else
		print_env_fd(tmp, filename->arg, fd);
	return (0);
}
