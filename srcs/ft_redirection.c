/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redirection.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/19 13:53:32 by thbierne          #+#    #+#             */
/*   Updated: 2022/06/13 14:03:49 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/libft/libft.h"

int		ft_redirection(char *str, char *filename)
{
	int	file;

	if (!filename)
		return (-1);
	if (access(filename, R_OK | W_OK) != 0)
		file = open(filename, O_CREAT | O_WRONLY);
	else
		file = open(filename, O_RDONLY | O_WRONLY | O_TRUNC);
	if (file == -1)
		return (-1);
	write(file, str, len(str));
	close(file);
	return (0);
}

int		ft_redirection_appen(char *str, char *filename)
{
	char	tmp;
	char	*join;
	char	*cpy;
	int		file;

	if (!filename)
		return (-1);
	if (access(filename, R_OK | W_OK) != 0)
	{
		ft_redirection(str, filename);
		return (0);
	}
	else
		file = open(filename, O_RDWR);
	if (file == -1)
		return (-1);
	join = NULL;
	while (read(file, &tmp, 1) > 0)
		{
			if (!join)
			{
				join = (char *)malloc(sizeof(char) * 2);
				join[0] = tmp;
				join[1] = '\0';
			}
			else
				join = join_char(join, tmp);
		}
	close(file);
	file = open(filename,O_RDONLY | O_WRONLY | O_TRUNC);
	cpy = ft_strjoin(join, "\n");
	free(join);
	join = ft_strjoin(cpy, str);
	free (cpy);
	write(file, join, len(join));
	free(join);
	close(file);
	return (0);
}

char	*ft_redirection_out(char *filename)
{
	int		file;
	char	*join;
	char	tmp;

	if (!filename)
		return (NULL);
	if (access(filename, R_OK) != 0)
		return (NULL);
	file = open(filename, O_RDWR);
	if (file == -1)
		return (NULL);
	join = NULL;
	while (read(file, &tmp, 1) > 0)
		{
			if (!join)
			{
				join = (char *)malloc(sizeof(char) * 2);
				join[0] = tmp;
				join[1] = '\0';
			}
			else
				join = join_char(join, tmp);
		}
	close(file);
	return (join);
}