/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:05:07 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/15 19:55:32 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// execute_pipeline_utils_bonus.c
void			do_piping(int pipe_in, int pipe_out);
void			close_pipe(t_pipefd *pipefd);
int				open_pipe(t_pipefd *pipefd, int *fildes);

static pid_t	wait_for(pid_t lastpid)
{
	int		i;
	int		status;
	int		last_status;
	pid_t	wpid;

	i = 0;
	while (1)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == -1)
			break ;
		if (wpid == lastpid)
			last_status = status;
		i++;
	}
	if (lastpid < 0)
		return (EXECUTION_FAILURE);
	return (last_status);
}

static int	shell_execve(char *prog_name, char *command, char **args,
		char **envp)
{
	int	i;

	execve(command, args, envp);
	i = errno;
	internal_error(prog_name, command, strerror(i));
	return (i);
}

static void	execute_disk_command(t_command *cmd, char *envp[])
{
	char	*cmd_path;

	if (cmd->redirect && do_redirections(cmd->prog_name, cmd->redirect) != 0)
		exit(EXECUTION_FAILURE);
	cmd_path = search_for_command(cmd->cmdv[0], envp);
	if (!cmd_path)
	{
		internal_error(cmd->prog_name, cmd_path, NOTFOUND_STR);
		exit(EX_NOTFOUND);
	}
	exit(shell_execve(cmd->prog_name, cmd_path, &cmd->cmdv[0], envp));
}

// biltin or user function or disk command check
static pid_t	execute_simple_command(t_pipefd pipefd, t_command *cmd,
		char *envp[])
{
	t_bool	builtin;
	pid_t	pid;

	builtin = is_builtin(cmd->cmdv[0]);
	pid = fork();
	if (pid < 0)
	{
		sys_error("fork");
		return (-1);
	}
	if (pid == 0)
	{
		do_piping(pipefd.pipe_in, pipefd.pipe_out);
		if (builtin)
		{
			internal_error(cmd->prog_name,
				"shell built-in command is not supported", cmd->cmdv[0]);
			exit(-1);
		}
		else
			execute_disk_command(cmd, envp);
	}
	return (pid);
}

int	execute_pipeline(t_command *cmd, char *envp[])
{
	int fildes[2];
	t_pipefd pipefd;
	pid_t lastpid;
	t_command *cur_cmd;

	cur_cmd = cmd;
	pipefd.pipe_in = -1;
	while (cur_cmd)
	{
		if (cur_cmd->next)
		{
			if (open_pipe(&pipefd, fildes))
			{
				if (pipefd.pipe_in != -1)
					close(pipefd.pipe_in);
				return (wait_for(-1), EXECUTION_FAILURE);
			}
			pipefd.pipe_out = fildes[1];
		}
		else
			pipefd.pipe_out = -1;
		lastpid = execute_simple_command(pipefd, cur_cmd, envp);
		close_pipe(&pipefd);
		cur_cmd = cur_cmd->next;
		if (cur_cmd->next)
			pipefd.pipe_in = fildes[0];
	}
	return (wait_for(lastpid));
}