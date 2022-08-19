/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/19 10:57:40 by thbierne          #+#    #+#             */
/*   Updated: 2022/08/19 12:13:06 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	check_pipe2(int i, int y, char *line_read)
{
	if (y == -1)
		return (-4);
	while (line_read[++i])
	{
		if (line_read[i] == '|')
			return (-4);
		if (line_read[i] != ' ')
			break ;
	}
	if (!line_read[i])
		return (-4);
	return (--i);
}

char	*return_join(char *join, char *read)
{
	char	*tmp;

	if (!join)
		join = ft_strjoin(read, "\n");
	else
	{
		tmp = ft_strjoin(join, read);
		free (join);
		join = ft_strjoin(tmp, "\n");
		free (tmp);
	}
	free(read);
	return (join);
}

char	*check_eof(char *join, char *read, char *eof, int fd[2])
{
	int		i;

	i = 0;
	while (read[i] == eof[i])
	{
		if (!read[i] && !eof[i])
		{
			free(read);
			write(fd[1], join, len(join));
			close(fd[1]);
			free(eof);
			free(join);
			exit (EXIT_SUCCESS);
		}
		i++;
	}
	return (return_join(join, read));
}

int	count_redir(t_cmd *cmd)
{
	int		x;
	t_arg	*tmp;

	x = 0;
	tmp = cmd->next_arg;
	if (cmd->nbr == -1 || cmd->nbr == -2)
		x++;
	while (tmp)
	{
		if (tmp->nbr == -1 || tmp->nbr == -2)
			x++;
		tmp = tmp->next_arg;
	}
	return (x);
}
