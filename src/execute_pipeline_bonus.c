/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:05:07 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/08/01 11:45:13 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/*
1) fork ()
2) connect pipes
3) look up the command
4) do redirections
5) execve ()
6) If the execve failed, see if the file has executable mode set.
   If so, and it isn't a directory, then execute its contents as
   a shell script.
*/

// execute_pipeline_utils_bonus.c
t_bool			do_piping(int pipe_in, int pipe_out);
void			close_pipe(t_pipefd *pipefd);
int				open_pipe(t_pipefd *pipefd, int *fildes);
int				execute_pipe_internal(t_pipefd *pipefd, int *fildes);

pid_t	wait_for(pid_t lastpid)
{
	int		status;
	int		last_status;
	pid_t	wpid;

	last_status = -1;
	while (1)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid < 0)
			break ;
		if (wpid == lastpid)
			last_status = status;
	}
	if (lastpid < 0)
		return (EXECUTION_FAILURE);
	if (WIFEXITED(last_status))
		return (WEXITSTATUS(last_status));
	else
		return (EXECUTION_FAILURE);
}

// ENOEXEC		:	when no binary and shellscript, re execve
static int	shell_execve(t_command *cmd, char *command, char **args,
		char **envp)
{
	int		i;
	char	*re_args[3];

	execve(command, args, envp);
	i = errno;
	if (i == ENOEXEC)
	{
		re_args[0] = "/bin/bash";
		re_args[1] = command;
		re_args[2] = NULL;
		execve(re_args[0], re_args, envp);
		i = errno;
	}
	internal_error(cmd->prog_name, command, strerror(i));
	dispose_command(cmd->head);
	free(command);
	return (i);
}

static void	execute_disk_command(t_command *cmd, char *envp[])
{
	char	*cmd_path;

	if (cmd->redirect && do_redirections(cmd->prog_name, cmd->redirect,
			envp) != 0)
	{
		dispose_command(cmd->head);
		exit(EXECUTION_FAILURE);
	}
	if (cmd->cmdv[0] == NULL)
	{
		internal_error(cmd->prog_name, "", NOTFOUND_STR);
		dispose_command(cmd->head);
		exit(EX_NOTFOUND);
	}
	cmd_path = search_for_command(cmd, envp);
	if (!cmd_path)
	{
		internal_error(cmd->prog_name, cmd->cmdv[0], NOTFOUND_STR);
		dispose_command(cmd->head);
		exit(EX_NOTFOUND);
	}
	exit(shell_execve(cmd, cmd_path, &cmd->cmdv[0], envp));
}

// biltin or user function or disk command check
static pid_t	execute_simple_command(t_pipefd pipefd, t_command *cmd,
		char *envp[], int close_fd)
{
	const t_bool	builtin = is_builtin(cmd->cmdv[0]);
	const pid_t		pid = fork();

	if (pid < 0)
		return (dispose_command(cmd->head), sys_error("fork error"), -1);
	if (pid == 0)
	{
		if (close_fd != -1)
			close(close_fd);
		if (!do_piping(pipefd.pipe_in, pipefd.pipe_out))
		{
			dispose_command(cmd->head);
			sys_error("dup error");
			exit(EXECUTION_FAILURE);
		}
		if (builtin)
		{
			internal_error(cmd->prog_name, BUILTIN_STR, cmd->cmdv[0]);
			dispose_command(cmd->head);
			exit(EXECUTION_FAILURE);
		}
		else
			execute_disk_command(cmd, envp);
	}
	return (pid);
}

int	execute_pipeline(t_command *cmd, char *envp[])
{
	int			fildes[2];
	t_pipefd	pipefd;
	pid_t		lastpid;
	t_command	*cur_cmd;

	cur_cmd = cmd;
	pipefd.pipe_in = -1;
	while (cur_cmd)
	{
		pipefd.pipe_out = -1;
		if (cur_cmd->next)
		{
			if (!execute_pipe_internal(&pipefd, fildes))
				return (dispose_command(cmd->head), sys_error("pipe error"),
					EXECUTION_FAILURE);
		}
		else
			fildes[0] = -1;
		lastpid = execute_simple_command(pipefd, cur_cmd, envp, fildes[0]);
		close_pipe(&pipefd);
		if (cur_cmd->next)
			pipefd.pipe_in = fildes[0];
		cur_cmd = cur_cmd->next;
	}
	return (wait_for(lastpid));
}
