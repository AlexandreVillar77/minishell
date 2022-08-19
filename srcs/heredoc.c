/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:01:35 by thbierne          #+#    #+#             */
/*   Updated: 2022/08/19 11:49:31 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	inthandler(int pid)
{
	(void)pid;
	exit (EXIT_SUCCESS);
}

char	*join_char(char *str, char c)
{
	char	*join;
	int		i;

	i = 0;
	while (str[i])
		i++;
	join = (char *)malloc(sizeof(char) * (i + 2));
	i = 0;
	while (str[i])
	{
		join[i] = str[i];
		i++;
	}
	join[i++] = c;
	join[i] = '\0';
	free(str);
	return (join);
}

void	write_heredoc(int fd[2], char *eof)
{
	char	*read;
	char	*join;

	signal(SIGINT, inthandler);
	join = NULL;
	close(fd[0]);
	while (1)
	{
		read = readline("> ");
		if (!read)
		{
			printf("using 'ctrl + d' as a delimiter\n");
			write(fd[1], join, len(join));
			close(fd[1]);
			free(eof);
			exit (EXIT_SUCCESS);
		}
		join = check_eof(join, read, eof, fd);
	}
	exit (EXIT_SUCCESS);
}

void	l_kid(char *eof, char *line_read, t_llist *list, int fd[2])
{
	char	*join;

	join = ft_strdup(eof);
	list = free_llist_cmd(list);
	free_llist(list, line_read);
	write_heredoc(fd, join);
}

char	*heredoc(char *eof, t_llist *list, char *line_read)
{
	pid_t	pid;
	int		fd[2];
	char	tmp;
	char	*join;

	signal(SIGQUIT, SIG_IGN);
	join = NULL;
	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
		l_kid(eof, line_read, list, fd);
	else
	{
		wait(NULL);
		join = (char *)malloc(sizeof(char) * 1);
		join[0] = '\0';
		close(fd[1]);
		while (read(fd[0], &tmp, 1) > 0)
			join = join_char(join, tmp);
		close(fd[0]);
		return (join);
	}
	exit (EXIT_SUCCESS);
}
