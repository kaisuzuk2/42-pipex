/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline_utils_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 19:54:27 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/15 19:55:41 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	open_pipe(t_pipefd *pipefd, int *fildes)
{
	if (pipe(fildes) < 0)
	{
		sys_error("pipe_error");
		if (pipefd->pipe_in != -1)
			close(pipefd->pipe_in);
		return (EXECUTION_FAILURE);
	}
	return (EXECUTION_SUCCESS);
}

void	close_pipe(t_pipefd *pipefd)
{
	if (pipefd->pipe_in != -1)
		close(pipefd->pipe_in);
	if (pipefd->pipe_out != -1)
		close(pipefd->pipe_out);
}

void	do_piping(int pipe_in, int pipe_out)
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