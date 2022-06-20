/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_syntaxe.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/29 10:41:06 by thbierne          #+#    #+#             */
/*   Updated: 2022/06/13 14:04:08 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft/libft.h"

int	check_quote(char *line_read, int i, char c)
{
	i++;
	while (line_read[i] != c && line_read[i])
		i++;
	if (!line_read[i])
	{
		if (c == 34)
			return (-1);
		else
			return (-2);
	}
	return (i);
}

int	check_red(char *line_read, int i, char c)
{
	int	y;

	y = 0;
	if ((line_read[i] == '>' && line_read[i + 1] == '<')
		|| (line_read[i] == '<' && line_read[i + 1] == '>'))
		return (-3);
	if (line_read[++i] == c)
	{
		y++;
		i++;
		if (line_read[i] == '<' || line_read[i] == '>')
			return (-3);
	}
	if (y == 1 && line_read[i] == '|')
		return (-3);
	while (line_read[i] == ' ')
		i++;
	if (!line_read[i])
		return (-3);
	else if (line_read[i] == '|' && y == 1)
		return (-3);
	else if (line_read[i] == '|' && y == 0 && line_read[i - 1] == ' ')
		return (-3);
	return (i);
}

int	check_pipe(char *line_read, int i, char c)
{
	int	y;

	y = i;
	y--;
	while (y >= 0)
	{
		if (line_read[y] == '>' && line_read[y - 1] != '>' && (y + 1) == i)
			break ;
		else if (line_read[y] == '>' && line_read[y - 1]
			== '>' && (y + 1) == i)
			return (-4);
		else if (line_read[y] == c)
			return (-4);
		while (line_read[y] == ' ' && y >= 0)
			y--;
		if (line_read[y] == '|')
			return (-4);
		else if (line_read[y] == 34 || line_read[y] == 39
			|| (line_read[y] >= '!' && line_read[y] <= '~'))
			break ;
	}
	if (y == -1)
		return (-4);
	while (line_read[++i])
	{
		if (line_read[i] == '|')
			return (-4);
		if (line_read[i] != ' ')
			break;
	}
	if (!line_read[i])
		return (-4);
	return (--i);
}

int	check_pipe_dir(char *line_read)
{
	int	i;

	i = 0;
	while (line_read[i])
	{
		while (line_read[i] == ' ' && line_read[i])
			i++;
		i = test_check(line_read, i);
		if (i < 0)
			return (i);
		i++;
	}
	return (i);
}

int	check_syntaxe(char *line_read)
{
	int	check;

	check = check_pipe_dir(line_read);
	if (check == -1)
		printf("quote not close\n");
	else if (check == -2)
		printf("quote not close\n");
	else if (check == -3)
		printf("wrond token near '<' or '>'\n");
	else if (check == -4)
		printf("wrong token near '|'\n");
	if (check < 0)
		return (-1);
	return (1);
}
