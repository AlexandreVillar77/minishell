/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avillar <avillar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:27:38 by avillar           #+#    #+#             */
/*   Updated: 2022/06/22 16:08:33 by avillar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../includes/libft/include/libft.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdarg.h>
# include <pthread.h>
# include <sys/time.h>
# include <sys/types.h>
# include <fcntl.h>
# include <sys/stat.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <curses.h>
# include <term.h>
# include <sys/wait.h>
# include <signal.h>

//dans la llist_arg:
// arg = > 0;
// >  =  -1;
// >> =  -2;
// <  =  -3;
// << =  -4;
// |  =  -5;

typedef struct s_llist t_llist;
typedef struct s_arg t_arg;
typedef struct s_exe t_exe;
typedef struct s_env t_env;
typedef struct s_cmd t_cmd;

struct s_arg
{
	int			nbr;
	char 		*arg;
	t_arg		*next_arg;
};

struct s_cmd
{
	int 		nbr;
	char		*cmd;
	t_cmd		*next_cmd;
	t_arg		*next_arg;
};

struct s_env
{
	char		*name;
	char		*var;
	t_env		*next_env;
};

struct s_exe
{
	char		*name_exe;
	t_exe 		*next_exe;
};

struct s_llist
{
	int			index;
	int			new_cmd;
	t_cmd		*first_cmd;
	t_env		*first_env;
	t_exe		*first_exe;
	char 		**path;
	char		**env;
};

t_llist		*alloc_arg(t_llist *list, char *read_line);

/* teste les commandes recu et debut parsing */

t_llist		*list_cmd(t_llist *list, char *read_line, int count, char *str);
t_llist		*check_cmd(t_llist *list, char *line_read, char *str);
t_llist		*alloc_cmd(t_llist *list, char *line_read);
t_llist		*alloc_str(t_llist *list, char *read_line);
char		*alloc_find_str(char *read_line, int y, int *index, char *str);
char		*alloc_find_str2(char *str, char *cpy);
char		*find_str(t_llist *list, char *read_line, char *str, int y);

t_llist		*ft_case_cmd_found(t_llist *list, char *cmd);
t_llist		*ft_check_cmd_path(t_llist *list, char *cpy);

/* ajoute ou supprime maillon de la liste pour les commandes et arguments */

t_cmd		*add_first_t_cmd(char *str, int nbr);
t_cmd		*add_last_t_cmd(t_cmd *list, char *str, int nbr);
t_cmd		*delete_first_t_cmd(t_cmd *list);
t_arg		*add_first_t_arg(char *str, int nbr);
t_arg		*add_last_t_arg(t_arg *list, char *str, int nbr);
void		larg_del_one(t_arg *arg, int id);
void		larg_del_first(t_arg *arg);
void		del_redir(t_arg *arg);

/* check syntaxe */

int			check_quote(char *line_read, int i, char c);
int			check_red(char *line_read, int i, char c);
int			check_pipe(char *line_read, int i, char c);
int			check_pipe_dir(char *line_read);
int			check_syntaxe(char *line_read);

/* fonction qui alloue echo */

t_llist		*alloc_flags_echo3(char *read_line, t_llist *list, int *z, t_cmd *tmp);
t_llist		*alloc_flags_echo2(char *read_line, t_llist *list, int *z);
t_llist		*alloc_flags_echo(char *read_line, t_llist *list);
t_llist		*ft_case_echo(t_llist *list, char *read_line);

/* free */

t_llist		*free_llist_exe(t_llist *list);
t_llist		*free_llist_env(t_llist *list);
t_llist		*free_llist_tab(t_llist *list, int i);
t_llist		*free_llist_cmd(t_llist *list);
void		free_llist(t_llist *list, char *line_read);

/* initialisation de la liste chaine */

t_exe		*add_first_t_exe(char *str);
t_exe		*add_last_t_exe(t_exe *list, char *str);
t_exe		*delete_first_t_exe(t_exe *list);
t_llist		*init_llist(char **envp);

t_env		*delete_first_t_env(t_env *list);
t_env		*add_var(t_env *new, char *str, int i);
t_env		*add_t_env(t_env *list, char *str);
t_env		*alloc_t_env(char **envp, t_env *list);

char		*rl_gets(char *line_read);
int			main();

/* remplace le dollar */

char		*join_line_read1(char *line_read, t_env *tmp, int i);
char		*join_line_read2(t_env *tmp, char *cpy, int *i, int *y);
char		*join_line_read(char *line_read, t_env *tmp, int i);
char		*replace_dollar(char *line_read, t_env *first_env, int mode);
t_env		*check_dollar_t_env(char *line_read, t_env *first_env, int i);

/* fonction qui join pour creer le chemin absolue des commandes a ne pas coder */

char		*split_path_into_tab2(char *str, char *split, int *i, int *y);
char		**split_path_into_tab(char **split, char *str, int i, int count);
t_llist		*split_path(char *str, char c, t_llist *list);
t_llist		*alloc_path(t_llist *list);
char		*test_cmd(t_llist *list, char *read);

/* suppression des quotes */

char		*remove_quote(t_llist *list, char *read_line);
char		*delete_quote(char *str);

t_llist		*alloc_pipe(t_llist *list);

char		*alloc_redi_cpy(t_llist *list, char *read_line, int *nb);
t_llist		*alloc_redi_cmd(t_llist *list, char *read_line);
t_llist		*alloc_redi_arg(t_llist *list, char *read_line);

/* fichier utils 1, 2 */

t_arg		*delete_first_t_arg(t_arg *list);
int			test_check(char *line_read, int i);
t_llist		*malloc_llist_to_tab_env(t_llist *list);
t_llist		*llist_to_tab_env(t_llist *list);

int			len(char *str);
void		print_tab(char **split);
void		print_t_exe(t_exe *list);
void		print_t_env(t_env *list);
void		print_t_cmd(t_cmd *list);

char		*heredoc(char *eof);
char		*case_heredoc(char *eof);

int			ft_redirection(char *str, char *fd);
int			ft_redirection_appen(char *str, char *fd);
char		*join_char(char *str, char c);

t_llist		*sort_redi(t_llist *list);
t_llist		*sort_llist_redi(t_llist *list, t_cmd *t_cmd);
t_llist		*delete_pipe(t_llist *list);

void		ft_set_base_env(t_env *envl);

/* builtins */

// echo.c
int			ft_echo(t_cmd *cmd);

//fctnl_manager.c
int			fctnl_manager(t_llist *list);
int			check_redir(t_arg *arg);

//exit.c
int			ft_exit(t_llist *list);

//env.c
int			ft_penv(t_llist *list);

//pwd.c
int			ft_pwd(t_llist *list);

//ft_make_file.c
char		*recup_argx(t_arg *arg, int id);
int			ft_make_file(char *filename);

# endif