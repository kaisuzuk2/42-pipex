/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:05:07 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/02 13:49:28 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int execute_pipeline(char *argv[], char *envp[], int cmd_start, int cmd_end, int pipe_in, int pipe_out)
{
	pid_t pid;
	int fd[2];
	char **cmd;
	int prev_fd;

	dup2(pipe_in, 0);
	close(pipe_in);
	prev_fd = -1;
	while (cmd_start <= cmd_end)
	{
		if (cmd_start < cmd_end)
			pipe(fd);
		pid = fork();
		if (pid == 0)
		{
			if (prev_fd != -1)
			{
				dup2(prev_fd, 0);
				close(prev_fd);
			}
			if (cmd_start == cmd_end)
			{
				dup2(pipe_out, 1);
				close(pipe_out);
			}
			else
			{
				dup2(fd[1], 1);
				close(fd[1]);	
			}
			prev_fd = fd[0];
			cmd = make_command(argv[cmd_start]);
			execve(search_for_command(cmd[0], envp), &cmd[0], envp);	
			perror("execve");
			exit(1);	
		}
		cmd_start++;
	}
	return (1); // とりあえずね
}