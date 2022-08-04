/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rl_get.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/27 11:52:46 by thbierne          #+#    #+#             */
/*   Updated: 2022/08/01 11:28:18 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	handler(int num)
{
	(void)num;
	write(1, "\n", 1);
	exit (EXIT_SUCCESS);
}

void	write_line_read(int fd[2])
{
	char	*read;

	signal(SIGINT, handler);
	signal(SIGQUIT, SIG_IGN);
	close(fd[0]);
	read = readline("minishell: ");
	if (!read)
	{
		write(1, "exit\n", 5);
		read = ft_strdup("exit");
		write(fd[1], read, ft_strlen("read"));
		close(fd[1]);
		free(read);
		exit (EXIT_SUCCESS);
	}
	write(fd[1], read, ft_strlen(read));
	close(fd[1]);
	free(read);
	exit (EXIT_SUCCESS);
}

char	*read_line()
{
	pid_t	pid;
	int		fd[2];
	char	tmp;
	char	*join;

	join = NULL;
	if (pipe(fd) == -1)
		exit(EXIT_FAILURE);
	pid = fork();
	if (pid == 0)
		write_line_read(fd);
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
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

char	*rl_gets(char *line_read)
{
	if (line_read)
	{
		free(line_read);
		line_read = NULL;
	}
	line_read = read_line();
	if (!line_read)
	{
		printf("exit\n");
		line_read = ft_strdup("exit");
		return(line_read);
	}
	if (line_read && *line_read)
		add_history(line_read);
	return (line_read);
}
