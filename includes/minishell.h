/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thbierne <thbierne@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/22 13:27:38 by avillar           #+#    #+#             */
/*   Updated: 2022/08/19 11:49:20 by thbierne         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

extern int LOL;

# include "../libft/include/libft.h"
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
# include <errno.h>

//dans la llist_arg:
// arg = > 0;
// >  =  -1;
// >> =  -2;
// <  =  -3;
// << =  -4;
// |  =  -5;
// .tmp = -6

typedef struct s_llist t_llist;
typedef struct s_arg t_arg;
typedef struct s_exe t_exe;
typedef struct s_env t_env;
typedef struct s_cmd t_cmd;
typedef	struct s_pipe t_pipe;

struct s_pipe
{
	int			*end;
	int			fd;
	char		*cmd;
	int			x;
	int			npip;
};

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
	char		*lastpos;
	int			index;
	int			new_cmd;
	t_pipe		*pip;
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
void		larg_del_next(t_arg **arg);
void		larg_del_first(t_arg **arg);
t_cmd		*larg_del_f(t_cmd *cmd);
t_arg		*larg_del_n(t_arg *arg, char **output);
t_llist      *del_redirection(t_llist *list);

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
int			ft_strchr2(char *str, char c);

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

char		*heredoc(char *eof, t_llist *list, char *line_read);
char		*case_heredoc(char *eof);

int			ft_redirection(char *str, char *fd);
int			ft_redirection_appen(char *str, char *fd);
char		*join_char(char *str, char c);

t_llist		*sort_redi(t_llist *list);
t_llist		*sort_llist_redi(t_llist *list, t_cmd *t_cmd);
t_llist		*delete_pipe(t_llist *list);

t_env		*ft_set_base_env();

t_llist		*create_redi(t_llist *list);
void		check_files(char *filename, int mode);
char		*replace_home(t_env *first_env, char *line_read);

t_llist		*check_and_add_last_redi(t_llist *list);
t_llist		*add_cmd_to_last_arg(t_llist *list, t_cmd *cmd_cpy, int *count);
int			count_redi(t_cmd *cmd, int count);

char		*read_line();
void		write_line_read(int fd[2]);

int			count_heredoc(t_cmd *cmd);
t_llist		*alloc_heredoc(t_llist *list, char *line_read);
t_llist		*del_heredoc(t_llist *list);
t_llist		*found_cat(t_cmd *cpy_cmd, t_llist *list, int count);

t_env		*change_shell_lev(t_env *env);

t_llist		*delete_empty_redi(t_llist *list);
int			check_full_redi(t_cmd *cmd);
t_cmd		*clear_cmd(t_cmd *cmd);

t_cmd		*del_cmd_for_redi(t_cmd *cmd, char **output);
t_arg		*del_arg_for_redi(t_arg *arg, char **output);
t_llist		*manage_redi(t_llist *list);
t_cmd		*alloc_output(t_cmd *cmd, char **output, int *i);
t_cmd		*alloc_input(t_cmd *cmd, char **input);
int			count_redir(t_cmd *cmd);
t_cmd		*put_redi_for_cmd(t_cmd *cmd, char **input, char **output);
char		*return_question(char* line_read, int i);
void		handler(int num);
t_llist*	test_cmd_utils(t_env *tmp, t_llist *list);
char		*replace_dollar2(char *line_read, t_env *first_env, int *i);
int			check_pipe2(int i, int y, char *line_read);
char		*check_eof(char *join, char *read, char *eof, int fd[2]);
char		*return_join(char *join, char *read);

/* builtins */

//echo_utils.c

int			echo_noarg(t_cmd *cmd);
int			check_echo_args(t_cmd *cmd);
int			ft_echo(t_cmd *cmd, int fd, int n);

// echo.c
int			args_size(t_arg *arg);
void		echo_manage(t_arg *arg, char *filename, int n, int fd);

//fctnl_manager.c
int			count_cmds(t_llist *list);
int			fctnl_manager(t_llist *list);
int			check_redir(t_arg *arg);
char		*get_fd_name(t_arg *arg);

//exit.c
int			ft_exit(t_llist *list);

//env.c
int			ft_penv(t_llist *list);

//pwd_tuils.c
void		print_err_path(void);
void		pwd_redir(t_arg *tmp, char *str);

//pwd.c
void 		ft_update_pwd(t_llist **list);
void 		ft_update_oldpwd(t_llist **list);
int			ft_pwd(t_llist *list);

//ft_make_file.c
char		*recup_argx(t_arg *arg);
int			ft_make_file(char *filename);

//chdir.c
char		*get_oldpwd(t_llist *list);
int			ft_cd(t_llist *list);
char		*get_pwd(t_llist *list);
char		*get_afeq(char *str);
int			rtn_print_errchdir(t_llist *list, char *dest, char *tofree);

//unset_utils.c
void 		fulltriche(t_llist **list, int x, int size);
void		unset_export(t_llist *list, int x, int size);
int			nameeq(char *str, char *name);
void		on_export(t_llist *list, t_arg *arg);
int			is_target(t_env *tmp, t_llist **list, t_arg *arg, int x);

//unset.c
t_llist		*del_env(t_llist *list, int m);
t_llist		*delete_lenv(int x, t_llist *list, int m);
int			ft_unset(t_llist *list);

//export_h_utils.c
int			largest(char *s1, char *s2);
char		*before_eq(char *str);
int			exist_on_ex(char *name, char **env);
char		*remove_p(char *str);

//export_h.c
int			check_for_update(t_llist **list, t_arg *arg, char *name);
int			ft_tablen(char **src);
char		**remalloc_export(char **src, int size, int i);
char		**ft_ex_on_h(char **list, t_arg *arg, char *name);
int			print_export(t_llist *list);

//export_utils.c
int			print_experror(t_arg *arg, int er);
int			rtn_checker(t_llist *list);
int			export_fullchecker(t_llist *list, int x, t_arg *arg);
int			ft_fullexport(t_llist **list);

//export_utils2.c
char		*recup_name(t_arg *arg);
char		*delete_equal(t_arg *arg, int i, int x);
int			check_ifeq(char *str);
int			export_checker(t_arg *arg);
int			export_redir_check(t_llist *list);

//ft_export.c
char		*get_var(t_arg *arg);
int			ft_export(t_llist **list, t_arg  **tmp, char *name);

//del_rag.c
t_llist		*del_arg(t_llist *list);
t_llist		*delete_larg(int x, t_llist *list);

//ft_exec_other_utils.c
int			get_fd(t_arg *arg);
int			get_nbarg(t_arg *arg);
char		*ft_cpy(char *src);
void		exec_path_p1(t_llist *list, char **arg_tab, char *cmd);

//ft_exec_other.c
char		**make_arg_tab(t_arg *arg, char *cmd, int i, int x);
char		*get_cmd_name(char *str);
int			ft_exec_others(t_llist *list);

//ft_pipex_utils.c
void		ft_closing_end(t_pipe *pip);
int			our_built(t_llist *list, t_pipe *pip);
void		ft_cmdnotf(char *str, char *name);
void		ft_cmdnotf2(char *str, char *s2);

//child_manager.c
int			exec_bypath(t_llist *list, t_pipe *pip, char **arg_tab);
void		childpro1_bonus(t_llist *list, t_pipe *pip, char **arg_tab);
void		childpro2_bonus(t_llist *list, t_pipe *pip, char **arg_tab, int j);
void    	childpro_bonus(t_llist *list, t_pipe *pip, char **arg_tab, int j);
void		child_manager(t_llist *list, int j, t_pipe *pip, char **arg_tab);

//pip_utils.c
void		init_pipe(t_pipe *pip);
int			count_pipe(t_llist *list);
t_pipe		*pip_init(t_llist *list);
void		err_exit();
void		free_arg_tab(char **arg_tab);

//free_pip.c
void		crash_freed(t_llist **list, t_pipe *pip, char **arg_tab);

//ft_pipex.c
int			check_redir_pipe(t_llist *list, t_pipe *pip);
int			pipex_redir(t_cmd *cmd);
void		pipex(t_llist *list, t_pipe *pip, int j, pid_t pid);
int			main_pip(t_llist *list);

# endif
