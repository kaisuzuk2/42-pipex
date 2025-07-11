/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:05:07 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/12 00:34:05 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

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
	return (last_status);
}

static void	do_piping(int pipe_in, int pipe_out)
{
	if (pipe_in != -1)
	{
		dup2(pipe_in, 0);
		close(pipe_in);
	}
	if (pipe_out != -1)
	{
		dup2(pipe_out, 1);
		close(pipe_out);
	}
}

// do external command
static void	execute_disk_command(t_command *cmd, char *envp[])
{
	char	*cmd_path;

	cmd_path = search_for_command(cmd->cmdv[0], envp);
	if (!cmd_path)
		exit(1);
	execve(cmd_path, &cmd->cmdv[0], envp);
	perror("execve");
	exit(1);
}

// biltin or user function or disk command check
static pid_t	execute_simple_command(t_pipefd pipefd, t_command *cmd,
		char *envp[])
{
	t_bool	builtin;
	pid_t	pid;
	int here_fd;

	builtin = is_builtin(cmd->cmdv[0]);
	pid = fork();
	if (pid == 0)
	{
		do_piping(pipefd.pipe_in, pipefd.pipe_out);
		if (cmd->redirect)
		{
			if (cmd->redirect->instruction == e_input_direction
				|| cmd->redirect->instruction == e_output_direction)
				if (!do_redirection(cmd->redirect))
					exit(99);
			if (cmd->redirect->instruction == e_reading_until)
			{
				here_fd = here_document_to_fd(cmd->redirect);
				if (here_fd == -1)
					exit(99);
				dup2(here_fd, 0);
			}
		}
		if (builtin)
		{
			ft_dprintf(STDERR_FILENO,
				"%s: '%s' is a shell built-in and is not supported.\n",
				cmd->prog_name, cmd->cmdv[0]);
			exit(1);
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
			pipe(fildes);
			pipefd.pipe_out = fildes[1];
		}
		else
			pipefd.pipe_out = -1;
		lastpid = execute_simple_command(pipefd, cur_cmd, envp);

		if (pipefd.pipe_in != -1)
			close(pipefd.pipe_in);
		if (pipefd.pipe_out != -1)
			close(pipefd.pipe_out);
		if (cur_cmd->next)
			pipefd.pipe_in = fildes[0];
		cur_cmd = cur_cmd->next;
	}
	return (wait_for(lastpid));
}