/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute_pipeline_utils_bonus.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 19:54:27 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/22 21:52:17 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_bool	open_pipe(t_pipefd *pipefd, int *fildes)
{
	if (pipe(fildes) < 0)
	{
		sys_error("pipe_error");
		if (pipefd->pipe_in != -1)
			close(pipefd->pipe_in);
		return (FALSE);
	}
	return (TRUE);
}

void	close_pipe(t_pipefd *pipefd)
{
	if (pipefd->pipe_in != -1)
		close(pipefd->pipe_in);
	if (pipefd->pipe_out != -1)
		close(pipefd->pipe_out);
}

t_bool	do_piping(int pipe_in, int pipe_out)
{
	if (pipe_in != -1)
	{
		if (dup2(pipe_in, 0) < 0)
			return (FALSE);
		close(pipe_in);
	}
	if (pipe_out != -1)
	{
		if (dup2(pipe_out, 1) < 0)
			return (FALSE);
		close(pipe_out);
	}
	return (TRUE);
}

t_bool	execute_pipe_internal(t_pipefd *pipefd, int *fildes)
{
	if (!open_pipe(pipefd, fildes))
	{
		if (pipefd->pipe_in != -1)
			close(pipefd->pipe_in);
		wait_for(-1);
		return (FALSE);
	}
	pipefd->pipe_out = fildes[1];
	return (TRUE);
}
