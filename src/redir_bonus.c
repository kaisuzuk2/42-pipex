/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redir_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 21:49:09 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/02 00:20:43 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "pipex.h"

t_bool do_redirection(int *pipe_in, int *pipe_out, char *infile, char *outfile)
{
	*pipe_in = open(infile, O_RDONLY);
	if (*pipe_in == -1)
		return (FALSE);
	*pipe_out = open(outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (*pipe_out == -1)
	{
		close(*pipe_in);
		return (FALSE);
	}
	return (TRUE);
	
}