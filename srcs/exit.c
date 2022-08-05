/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/20 11:51:38 by avillar           #+#    #+#             */
/*   Updated: 2022/08/05 10:29:18 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	if_tmpdelete(t_llist *list)
{
	int		fd;
	char	**str;
	int		i;
	//char	*cmd;
	
	i = -1;
	write(2, "re\n", 3);
	str = malloc(sizeof(char *) * 2);
	if (!str)
		exit (EXIT_FAILURE);
	str[0] = ft_strdup("./.tmp");
	str[1] = NULL;
	i++;
	fd = open("./.tmp", O_RDONLY);
	if (fd < 1)
		return ;
	if (access("/usr/bin/rm", X_OK) == 0)
		execve("/usr/bin/rm", str, list->env);
	/*else
	{
		while (list->path[++i][0] && list->path != NULL)
		{
			cmd = ft_strjoin(list->path[i], "rm");
			if (!cmd)
			exit (EXIT_FAILURE);
			if (access(cmd, X_OK) == 0)
				execve(cmd, str, list->env);
			free(cmd);
		}
	}*/
	close (fd);
	free (str);
}

int	ft_exit(t_llist *list)
{
	free_llist_cmd(list);
	free_llist(list, NULL);
	exit (0);
}