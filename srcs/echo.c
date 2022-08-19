/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:11:09 by avillar           #+#    #+#             */
/*   Updated: 2022/08/18 09:40:21 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	print_echo0(t_arg *arg, int n)
{
	t_arg	*tmp;

	tmp = arg;
	while (tmp)
	{
		write(1, tmp->arg, ft_strlen(tmp->arg));
		if (tmp->next_arg)
			write(1, " ", 1);
		tmp = tmp->next_arg;
	}
	if (n == 0)
		write(1, "\n", 1);
	return (0);
}

int	args_size(t_arg *arg)
{
	int		size;
	t_arg	*tmp;

	size = 0;
	tmp = arg;
	while (tmp)
	{
		if (tmp->nbr < 0)
			break ;
		size += ft_strlen(tmp->arg);
		tmp = tmp->next_arg;
	}
	return (size);
}

char	*add_space(char *str, char *add)
{
	char	*rtn;

	rtn = ft_strjoin(str, add);
	free (str);
	return (rtn);
}

int	print_echo_fd(t_arg *arg, char *filename, int n, int red)
{
	char	*content;

	content = malloc(sizeof(char) * (args_size(arg) + 1));
	if (!content)
		exit (1);
	content[0] = '\0';
	while (arg)
	{
		if (arg->nbr < 0)
			break ;
		content = add_space(content, arg->arg);
		if (arg->next_arg && arg->next_arg->nbr > 0)
			content = ft_strjoin(content, " ");
		arg = arg->next_arg;
	}
	if (n == 0)
		content = add_space(content, "\n");
	if (red == -1)
		ft_redirection(content, filename);
	else if (red == -2)
		ft_redirection_appen(content, filename);
	free(content);
	return (0);
}

void	echo_manage(t_arg *arg, char *filename, int n, int fd)
{
	if (fd < 0)
		print_echo_fd(arg, filename, n, fd);
	else
		print_echo0(arg, n);
}
