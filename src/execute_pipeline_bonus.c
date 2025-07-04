/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:05:07 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/05 00:37:27 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void do_piping(int pipe_in, int pipe_out)
{
	dup2(pipe_in, 0);
	close(pipe_in);
	dup2(pipe_out, 1);
	close(pipe_out);
}

static void	execute_disk_command(int pipe_in, int pipe_out, char *argv[], char *envp[], int cmd_start)
{
	pid_t	pid;
	char	**cmd;
	char	*cmd_path;

	pid = fork();
	if (!pid)
	{
		do_piping(pipe_in, pipe_out);
		cmd = make_command(argv[cmd_start]);
		if (!cmd)
		{
			ft_printf("%s: cannot malloc\n", argv[0]); // fprintf作ろうね
			exit(1);
		}
		cmd_path = search_for_command(cmd[0], envp);
		if (!cmd_path)
			exit(1);
		execve(cmd_path, &cmd[0], envp);
		perror("execve");
		exit(1);
	}
}

// ビルトインか、ユーザー関数か、外部コマンドか調べる
static int	execute_simple_command(int pipe_in, int pipe_out, char *argv[], char *envp[], int cmd_start)
{
	if (is_builtin(argv[cmd_start]))
	{
		ft_printf("%s: '%s' is a shell built-in and is not supported.\n");
		return (-1);
	}
	execute_disk_command(pipe_in, pipe_out, argv, envp, cmd_start);
	return (0);
}

//  コマンドを左から右へ実行していく

int	execute_pipeline(char *argv[], char *envp[], int cmd_start, int cmd_end,
		int pipe_in, int pipe_out)
{
	int		fildes[2];
	int		prev_fd;

	prev_fd = pipe_in;
	while (cmd_start <= cmd_end)
	{
		if (cmd_start < cmd_end)
			pipe(fildes);
		if (cmd_start == cmd_end)
		{
			execute_simple_command(prev_fd, pipe_out, argv, envp, cmd_start);
			close(pipe_out);
			close(prev_fd);
		}
		else
		{
			execute_simple_command(prev_fd, fildes[1], argv, envp, cmd_start);
			close(fildes[1]);
			close(prev_fd);
		}
		prev_fd = fildes[0];
		cmd_start++;
	}
	wait(NULL);
	return (1); // とりあえずね
}

// int execute_pipeline(char *argv[], char *envp[], int cmd_start, int cmd_end,
	// int pipe_in, int pipe_out)
// {
// 	pid_t pid;
// 	int fd[2];
// 	char **cmd;
// 	char *cmd_path;
// 	int prev_fd;

// 	dup2(pipe_in, 0);
// 	close(pipe_in);
// 	prev_fd = -1;
// 	while (cmd_start <= cmd_end)
// 	{
// 		if (cmd_start < cmd_end)
// 			pipe(fd);
// 		pid = fork();
// 		if (pid == 0)
// 		{
// 			if (prev_fd != -1)
// 			{
// 				dup2(prev_fd, 0);
// 				close(prev_fd);
// 			}
// 			if (cmd_start == cmd_end)
// 			{
// 				dup2(pipe_out, 1);
// 				close(pipe_out);
// 			}
// 			else
// 			{
// 				dup2(fd[1], 1);
// 				close(fd[1]);
// 			}
// 			cmd = make_command(argv[cmd_start]);
// 			if (!cmd)
// 			{
// 				ft_printf("%s: cannot malloc\n", argv[0]); // fprintf作ろうね
// 				exit(1);
// 			}
// 			cmd_path = search_for_command(cmd[0], envp);
// 			if (!cmd_path)
// 				exit(1);
// 			execve(search_for_command(cmd[0], envp), &cmd[0], envp);
// 			perror("execve");
// 			exit(1);
// 		}
// 		if (cmd_start != cmd_end)
// 			close(fd[1]);
// 		prev_fd = fd[0];
// 		cmd_start++;
// 	}
// 	wait(NULL);
// 	return (1); // とりあえずね
// }