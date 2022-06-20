/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/02 13:01:35 by thbierne          #+#    #+#             */
/*   Updated: 2022/06/13 14:03:47 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft/libft.h"

void	inthandler(int pid)
{
	(void)pid;
	kill(getppid(), SIGKILL);
	exit (EXIT_SUCCESS);
}

char	*join_char(char *str, char c)
{
	char *join;
	int i;

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
	char	*tmp;
	int		i;

	join = NULL;
	close(fd[0]);
	while (1)
	{
		printf("> ");
		read = readline(NULL);
		if (!read)
		{
			printf("using 'ctrl + d' as a delimiter\n");
			write(fd[1], join, len(join));
			close(fd[1]);
			exit (EXIT_SUCCESS);
		}
		i = 0;
		while (read[i] == eof[i])
		{
			if (!read[i] && !eof[i])
			{
				free(read);
				write(fd[1], join, len(join));
				close(fd[1]);
				exit (EXIT_SUCCESS);
			}
			i++;
		}
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
	}
	exit (EXIT_SUCCESS);
}

char	*heredoc(char *eof)
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
		write_heredoc(fd, eof);
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