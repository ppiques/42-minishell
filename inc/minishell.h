/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ppiques <ppiques@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/10 03:23:11 by cferrari          #+#    #+#             */
/*   Updated: 2022/05/01 05:46:32 by ppiques          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/inc/libft.h"
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>

typedef enum e_redirtype
{
	redir_in,
	redir_out,
	redir_heredoc,
	redir_append
}	t_redirtype;

typedef enum e_syntaxerror
{
	error_ok,
	error_next,
	error_pipe,
	error_newline,
	error_infile,
	error_heredoc,
	error_outfile,
	error_append
}	t_syntaxerror;

typedef struct s_var
{
	char	*name;
	char	*value;
}			t_var;

typedef struct s_redir
{
	char		*data;
	t_redirtype	type;
	int			is_ambiguous;
}				t_redir;

/* A cmd structure, where :
data is the raw text between pipes,
need_to_erase is a int* indicating the chars that correspond to redirs
redir_list is a chained list of redirections
str_count stores the result of a call to str_counter()
str_extractor is the result of a split that takes quotes and vars into account
split_extracted is the result of a split executed on the strs above
args is the char** that will be given to execve, created by create_args
*/
typedef struct s_cmd
{
	char	*data;
	int		*need_to_erase;
	t_list	**redir_list;
	int		str_count;
	char	**extracted;
	char	***split_extracted;
	char	**args;
	int		cmd_ind;
	int		fd_in;
	int		fd_out;
}			t_cmd;

typedef struct s_box
{
	const char	**envp;
	char		*prompt;
	char		*input;
	int			history_size;
	int			*pipes;
	int			nb_of_cmds;
	t_cmd		**line;
	pid_t		*pid_tab;
	t_list		**env_list;
}			t_box;

extern unsigned int	g_exit_code;
# define CODE_STD 0
# define CODE_EXEC 1
# define CODE_HEREDOC 2
# define CODE_MAINHEREDOC 3
# define CODE_SIGINT 130

// builtin.c
int				cd(t_cmd *cmd);
int				pwd(t_box *box, t_cmd *cmd);
int				ft_env(t_box *box, t_cmd *cmd);

// builtin_utils.c
void			print_var_export(void *var);
int				print_invalid(char *cmd_name, char *arg);
char			*ft_concat(char *ref, char *val);
t_var			*get_envvar(t_list **list, char *name);
int				add_front_var(char *name, char *value, t_list **list);

// cmd_create_args.c
int				create_args(t_cmd *cmd);

// cmd_parser.c
int				parse_cmds(t_box *box);

// cmd_redirs_utils.c
int				ft_infile(char *s, int i, t_cmd *cmd);
int				ft_heredoc(char *s, int i, t_cmd *cmd);
int				ft_outfile(char *s, int i, t_cmd *cmd);
int				ft_append(char *s, int i, t_cmd *cmd);

// cmd_redirs_utils.c
int				redir_size(char const *s);
void			need_to_erase_loop(t_cmd *cmd, int c, int i);

// cmd_redirs.c
int				ft_addredir(char *data, t_redirtype type, t_list **list);
int				redirs(t_cmd *cmd);
int				remove_chevron(t_cmd *cmd);

// cmd_smart_split.c
char			**smart_split(char const *s);

// echo.c
int				ft_echo(t_cmd *cmd, t_box *box);

// envp_utils.c
int				magical_free(char *s1, char *s2, t_list **list);
int				ind_equal(const char *s);
void			print_var(void *var);

// envp.c
t_var			*create_var(char *name, char *value);
int				add_var(char *name, char *value, t_list **list);
int				create_envp_list(const char **envp, t_box *box);
void			print_var(void *var);

// exit.c
int				ft_exit(t_box *box, t_cmd *cmd);

// export.c
int				ft_export(t_box *box, t_cmd *cmd);
int				print_invalid(char *cmd_name, char *arg);

// export2.c
char			*extract_export_name(char *arg);

// forks.c
void			megadup(t_cmd *cmd, t_box *box);
int				execute_cmd(t_cmd *cmd, t_box *box);
pid_t			*create_processes(int nb, t_box *box);
int				wait_all_processes(pid_t *pid_tab);

// heredoc_utils.c
char			*heredoc_name(int i);
void			eof_warning(char *delim, t_box *box);
int				heredoc_compare(char *line, char *delim, int quoted);
int				heredoc_var_expander(char **line_addr, t_box *box, int quoted);

// heredoc_utils2.c
int				special_write(int fd, char *line);
int				heredoc_freeonwriteerror(char *line, int fd);

// heredoc.c
int				heredoc_handler(t_box *box);
int				heredoc_deleter(t_box *box);

// list_var_handler_util.c
int				right_ambiguous(char *value);
int				left_ambiguous(char *value);
int				ft_delete(char **addr, int pos);

// list_var_handler.c
int				cmd_redir_expander(t_box *box);

// memfree2.c
int				cmd_free(t_cmd *cmd, int flag);

// memfree.c
void			free_split(char **tab);
void			free_var(void *var);
void			free_var_list(t_list **list);
void			free_for_new_line(t_box *box);
void			free_box(t_box *box, int flag);

// minishell.c
int				command_loop(t_box *box);

// nopipe.c
void			minidup(t_cmd *cmd);
int				execute_single_cmd(t_cmd *cmd, t_box *box);
int				faitout_single(t_cmd *cmd, t_box *box);

// open_redirs.c
int				open_list(t_cmd *cmd);

// pipe_handler.c
int				pipe_closer(int i, int *pipes, int max);
void			pipe_full_close(int *pipes, int max);
int				pipe_handler(t_box *box);

// pipe_split_utils.c
int				next_pipe(const char *s);
char			*extract_str(char *base, char quote);
int				skip_first_char(const char *s);
int				count_cmds(const char *s);

// pipe_split.c
t_cmd			**pipe_split(const char *s, int nb_of_cmds);

// prompt.c
char			*cut_str(const char *haystack, const char *needle);
char			*get_prompt(char *name);
char			*get_hostname(void);

// safe_atol.c
long int		safe_atol(char *s);

// special_chars.c
int				is_varchar(char c);
int				ft_isspace(char c);
int				ft_isquote(char c);
int				ft_isredir(char c);
int				ft_ismeta(char c);

// str_counter.c
int				skip_quote(t_cmd *cmd, int i);
int				skip_dollar(t_cmd *cmd, int i);
int				skip_text(t_cmd *cmd, int i);
int				skip_space(t_cmd *cmd, int i);
int				str_counter(t_cmd *cmd);

// str_extractor_utils.c
int				add_text(t_cmd *cmd, int i, int j, int space);
int				add_dollar(t_cmd *cmd, int i, int j, t_box *box);
int				add_quote(t_cmd *cmd, int i, int j, t_box *box);

// str_extractor.c
int				str_extractor(t_cmd *cmd, t_box *box);

// str_utils.c
char			*ft_pathjoin(char const *s1, char const *s2);
char			*create_absolute_path(char *basename);

// syntax_checker.c
t_syntaxerror	syntax_checker(t_box *box);
void			print_syntaxerror(t_syntaxerror err);

// tryexec.c
char			**get_paths(t_list **env);
void			tryexec(char **paths, char **args, t_cmd *cmd, t_box *box);
int				faitout(t_cmd *cmd, t_box *box);

// unset.c
int				ft_unset(t_box *box, t_cmd *cmd);

// utils.c
int				save_exitcode(t_list **env_list, int n);
void			treat_sig(int sig);
int				exec(t_box *box, t_cmd *cmd);
int				is_builtin(char *str);

// utils2.c
int				print_memerror_return(void);
t_box			*init_box(void);
void			print_memerror_exit(void);
int				is_only_spaces(char *s);
int				has_quotes(char *s);

// var_utils.c
char			*get_value(t_list **list, char *name);
char			*extract_varname(char *s);
int				replace_var(char *base, int start, \
t_list **env_list, char **addr);
int				check_varname(char *s);

#endif
