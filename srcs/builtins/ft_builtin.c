/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/09 09:51:33 by thbierne          #+#    #+#             */
/*   Updated: 2022/07/14 17:03:07 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/libft/libft.h"

int	ret_value;

int	ft_check(char *arg, char *str)
{
	int	i;

	i = 0;
	while (arg[i] && str[i])
	{
		if (arg[i] != str[i])
			return (0);
		i++;
	}
	if (arg[i] != str[i])
		return (0);
	else
		return (1);
}

int	ft_builtin(int ac, char **arg, t_env *envl)
{
	if (ft_check(arg[1], "cd"))
	{
		ft_cd(ac, &arg[1], envl);
		return (1);
	}
	else if (ft_check(arg[1], "echo"))
	{
		ret_value = ft_echo(ac, &arg[2]);
		return (1);
	}
	else if (ft_check(arg[1], "pwd"))
	{
		ft_pwd();
		return (1);
	}
	else if (ft_check(arg[1], "export"))
	{
		ret_value = ft_export(ac, &arg[2], envl);
		return (1);
	}
	else if (ft_check(arg[1], "unset"))
	{
		ft_unset(&arg[2], envl);
		return (1);
	}
	else if (ft_check(arg[1], "env"))
	{
		ft_print_envl(envl);
		return (1);
	}
	else if (ft_check(arg[1], "exit"))
	{
		if (arg[2] != NULL)
			ft_exit(atoi(arg[2]), envl, arg);
		ft_exit(0, envl, arg);
		return (1);
	}
	else
		return (0);
}

int	ft_execution(int ac, char **arg, t_llist *core)
{
	int		pid;
	char	**envp;
	int		i;

	i = -1;
	envp = NULL;
	if (ac == 0)
		return (0);
	if (ft_builtin(ac, arg, core->first_env))
		;
	else
	{
		arg[1] = ft_test_cmd(core, arg[1]);
		pid = fork();
		if (pid < 0)
			return (1);
		if (pid == 0)
		{
			envp = ft_envl_to_envp(core->first_env);
			execve(arg[1], &arg[1], envp);
			printf("%s: command not found\n", arg[1]);
			ft_free_envp(envp);
			ft_exit(0, core->first_env, arg);
		}
		waitpid(pid, NULL, 0);
	}
	return (ret_value);
}

void	ft_exit(int nbr, t_env *envl, char **arg)
{
	ft_free_envl(envl);
	clear_history();
	free(arg);
	exit(nbr);
	return ;
}