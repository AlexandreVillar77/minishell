/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_h_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/17 10:27:00 by avillar           #+#    #+#             */
/*   Updated: 2022/08/17 10:27:51 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	largest(char *s1, char *s2)
{
	int	i;
	int	x;

	i = 0;
	x = 0;
	while (s1[i] && s1[i] != '=' && s1[i] != '+')
		i++;
	while (s2[x] && s2[x] != '=' && s2[x] != '+')
		x++;
	if (i > x)
		return (i);
	else
		return (x);
}

char	*before_eq(char *str)
{
	int		i;
	char	*rtn;

	i = 0;
	if (check_ifeq(str) == 0)
		return (str);
	while (str[i] && str[i] != '=')
		i++;
	rtn = malloc(sizeof(char) * i + 1);
	if (!rtn)
		exit (EXIT_FAILURE);
	i = 0;
	while (str[i] && str[i] != '=')
	{
		rtn[i] = str[i];
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}

int	exist_on_ex(char *name, char **env)
{
	int		i;

	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], name, largest(env[i], name)) == 0)
			return (i);
		i++;
	}
	return (-1);
}

char	*remove_p(char *str)
{
	int		i;
	char	*rtn;

	i = 1;
	if (str[0] != '+')
		return (str);
	rtn = malloc(sizeof(char) * (ft_strlen(str) - 1));
	while (str[i])
	{
		rtn[i - 1] = str[i];
		i++;
	}
	rtn[i] = '\0';
	return (rtn);
}
