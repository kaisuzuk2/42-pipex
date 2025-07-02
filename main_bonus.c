/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:11:09 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/02 13:15:36 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


#include <stdio.h>

t_bool	parse_bonus(int argc, char *argv[]);
int		execute_pipeline(char *argv[], char *envp[], int cmd_start,
			int cmd_end, int pipe_in, int pipe_out);
t_bool	do_redirection(int *pipe_in, int *pipe_out, char *infile,
			char *outfile);

int	main(int argc, char *argv[], char *envp[])
{
	int	pipe_in;
	int	pipe_out;

	if (!parse_bonus(argc, argv))
		return (1); // エラーメッセージ考える
	do_redirection(&pipe_in, &pipe_out, argv[1], argv[argc - 1]);
	execute_pipeline(argv, envp, 2, argc -2, pipe_in, pipe_out);
}
