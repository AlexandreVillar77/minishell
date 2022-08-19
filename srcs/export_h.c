/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_h.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/10 14:51:36 by avillar           #+#    #+#             */
/*   Updated: 2022/08/19 10:48:21 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_for_update(t_llist **list, t_arg *arg, char *name)
{
	int		i;
	t_arg	*tmp;
	char	*v;
	char	*j;

	tmp = arg;
	i = exist_on_ex(name, (*list)->env);
	if (i < 0)
		return (1);
	v = remove_p(get_var(tmp));
	if (export_checker(tmp) == 1)
	{
		free ((*list)->env[i]);
		(*list)->env[i] = ft_strdup(tmp->arg);
	}
	else
	{
		j = ft_strjoin((*list)->env[i], v);
		free ((*list)->env[i]);
		(*list)->env[i] = ft_strdup(j);
		free (j);
	}
	if (v)
		free (v);
	return (0);
}

int	ft_tablen(char **src)
{
	int	i;

	i = 0;
	while (src[i])
		i++;
	return (i);
}

char	**remalloc_export(char **src, int size, int i)
{
	int		x;
	char	**dst;

	x = 0;
	dst = malloc(sizeof(char *) * (size + i));
	if (!dst)
		exit (EXIT_FAILURE);
	while (x < size)
	{
		dst[x] = ft_strdup(src[x]);
		x++;
	}
	while (x < size + i)
	{
		dst[x] = NULL;
		x++;
	}
	x = 0;
	while (x < size)
	{
		free(src[x]);
		x++;
	}
	free(src);
	return (dst);
}

char	**ft_ex_on_h(char **list, t_arg *arg, char *name)
{
	static int	x;

	x = 0;
	if (exist_on_ex(name, list) > -1)
		return (list);
	if (x == 0)
		x = ft_tablen(list);
	list = remalloc_export(list, x, 2);
	if (list[x])
		free (list[x]);
	list[x] = ft_strdup(arg->arg);
	if (!list[x])
		exit (EXIT_FAILURE);
	list[x + 1] = NULL;
	if (x != 0)
		x += 2;
	return (list);
}

int	print_export(t_llist *list, t_cmd *cmd)
{
	int	x;
	int	fd;

	x = -1;
	if (check_redir(cmd->next_arg) == -1)
	{
		fd = open(get_fd_name(cmd->next_arg), O_RDWR);
		if (fd < 0)
			exit (EXIT_FAILURE);
	}
	else if (check_redir(cmd->next_arg) == -2)
	{
		fd = open(get_fd_name(cmd->next_arg), O_RDWR | O_APPEND);
		if (fd < 0)
			exit (EXIT_FAILURE);
	}
	else
		fd = 1;
	while (list->env[++x])
	{
		write(fd, "export ", 7);
		write(fd, list->env[x], ft_strlen(list->env[x]));
		write(fd, "\n", 1);
	}
	return (0);
}
