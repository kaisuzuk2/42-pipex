/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:08:48 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/13 23:25:07 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf.h"
# include "get_next_line.h"
# include <fcntl.h>
# include <limits.h>
# include <string.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
#include <errno.h>


# ifndef HEREDOC_PIPESIZE
#  ifdef PIPE_BUF
#   define HEREDOC_PIPESIZE PIPE_BUF
#  else
#   define HEREDOC_PIPESIZE 4096
#  endif
# endif

# define EXECUTION_FAILURE 1
# define EXECUTION_SUCCESS 0

# define EX_NOEXEC 126
# define EX_NOTFOUND 127

# define NOTFOUND_STR "command not found"

# define MIN_ARG 5
# define MIN_HEREDOC_ARG 6

typedef int				t_bool;
# define TRUE 1
# define FALSE 0

enum					e_instruction
{
	e_output_direction,
	e_input_direction,
	e_reading_until
};

typedef struct s_redirect
{
	struct s_redirect	*next;
	enum e_instruction	instruction;
	char				*filename;
	char				*here_doc_eof;
	char				*document;
}						t_redirect;

typedef struct s_command
{
	struct s_command	*next;
	char				*prog_name;
	char				**cmdv;
	t_redirect			*redirect;
}						t_command;

typedef struct s_pipefd
{
	int					pipe_in;
	int					pipe_out;
}						t_pipefd;

// typedef struct s_redirect {
// 	char *word;
// 	char *here_doc_eof;

// } t_redirect;

// ft_mkstemp.c
int						ft_mkstemp(char *template);

// parse_bonus.c
t_command				*parse(int argc, char **argv);
t_bool					args_check(int argc, char **argv);

// utils_bonus.c
t_bool					is_builtin(char *cmd);

char					**make_command(char *arg);
char					*search_for_command(char *prog_name, char *arg, char *envp[]);

// redir_bonus.c
int						do_redirections(char *prog_name, t_redirect *redirect);
int						here_document_to_fd(t_redirect *r);

// make_cmd_bonus.c
char					*make_here_document(char *here_doc_eof);
void					heredoc_expand(t_redirect *r, size_t *lenp);

// cmdlst_bonus.c
t_command				*cmdnew(char *prog_name, char *cmds);
t_command				*set_redirect(t_command *c, enum e_instruction inst,
							char *filename_eof);
void					cmdlst_add_back(t_command *head, t_command *new);

// execute_pipeline_bonus.c
int						execute_pipeline(t_command *cmd, char *envp[]);

// dispose_cmd_bonus.c
void					dispose_command(t_command *command);

// error_bonus.c
void					sys_error(char *err_txt);
void					internal_error(char *prog_name, char *text,
							char *errno_text);
#endif