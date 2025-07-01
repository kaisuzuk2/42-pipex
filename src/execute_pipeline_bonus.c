/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 14:05:07 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/01 22:02:48 by kaisuzuk         ###   ########.fr       */
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
		if (cmd_start != cmd_end)
			pid = fork();
		if (pid == 0)
		{
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
			if (prev_fd == -1)
			{
				dup2(pipe_in, 0);
				close(pipe_in);
			}
			else
			{
				dup2(prev_fd, 0);
			}
			close(fd[1]);
			cmd = make_command(argv[cmd_start]);
			execve(cmd[0], &cmd[0], envp);			
		}
		
		cmd_start++;
	}
	return (1); // とりあえずね
}