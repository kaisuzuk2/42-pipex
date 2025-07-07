/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:05:07 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/06 14:20:02 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static pid_t	wait_for(pid_t lastpid, int child_num)
{
	int		i;
	int		status;
	int		last_status;
	pid_t	wpid;

	i = 0;
	while (i < child_num)
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
	dup2(pipe_in, 0);
	close(pipe_in);
	dup2(pipe_out, 1);
	close(pipe_out);
}


static void	execute_disk_command(t_command cmd, char *envp[], int current)
{
	char	**cmd_info;
	char	*cmd_path;

	cmd_info = make_command(cmd.cmdv[current]);
	if (!cmd_info)
	{
		ft_dprintf(stderr_fd, "%s: cannot malloc\n", cmd.prog_name);
		exit(1);
	}
	cmd_path = search_for_command(cmd_info[0], envp);
	if (!cmd_path)
		exit(1);
	execve(cmd_path, &cmd_info[0], envp);
	perror("execve");
	exit(1);
}

// biltin or user function or disk command check
static pid_t	execute_simple_command(t_pipefd pipefd, t_command cmd,
		char *envp[], int current)
{
	t_bool	builtin;
	pid_t	pid;

	builtin = is_builtin(cmd.cmdv[current]);
	pid = fork();
	if (pid == 0)
	{
		do_piping(pipefd.pipe_in, pipefd.pipe_out);
		if (builtin)
		{
			ft_dprintf(stderr_fd,
				"%s: '%s' is a shell built-in and is not supported.\n",
				cmd.prog_name, cmd.cmdv[current]);
			exit(1);
		}
		else
			execute_disk_command(cmd, envp, current);
	}
	return (pid);
}

int	execute_pipeline(t_command cmd, char *envp[], int pipe_in, int pipe_out)
{
	int			fildes[2];
	t_pipefd	pipefd;
	pid_t		lastpid;
	const int	child_num = cmd.cmd_end - cmd.cmd_start + 1;
	int			i;

	i = cmd.cmd_start;
	pipefd.pipe_in = pipe_in;
	while (i <= cmd.cmd_end)
	{
		if (i < cmd.cmd_end)
			pipe(fildes);
		if (i == cmd.cmd_end)
			pipefd.pipe_out = pipe_out;
		else
			pipefd.pipe_out = fildes[1];
		lastpid = execute_simple_command(pipefd, cmd, envp, i);
		close(pipefd.pipe_out);
		close(pipefd.pipe_in);
		pipefd.pipe_in = fildes[0];
		i++;
	}
	return (wait_for(lastpid, child_num));
}
