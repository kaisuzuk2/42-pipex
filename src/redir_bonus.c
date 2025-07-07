/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:49:09 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/06 15:32:09 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

static int here_document_to_fd()

t_bool do_redirection(int *pipe_in, int *pipe_out, const char *infile, const char *outfile)
{
	*pipe_in = open(infile, O_RDONLY);
	if (*pipe_in == -1)
	{
		ft_dprintf(stderr_fd, "pipex: no such file or directory: %s", infile);
		return (FALSE);
	}
	*pipe_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*pipe_out == -1)
	{
		close(*pipe_in);
		ft_dprintf(stderr_fd, "pipex: no such file or directory: %s", outfile);
		return (FALSE);
	}
	return (TRUE);
}