/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:11:09 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/06 00:02:27 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

t_bool		parse_bonus(int argc, char *argv[]);

t_bool		do_redirection(int *pipe_in, int *pipe_out, const char *infile,
				const char *outfile);
int			execute_pipeline(t_command cmd, char *envp[], int pipe_in,
				int pipe_out);

static void	cmd_init(t_command *cmd, int argc, char **argv)
{
	cmd->prog_name = argv[0];
	cmd->cmdv = argv;
	cmd->cmd_start = 2;
	cmd->cmd_end = argc - 2;
	cmd->cmd_size = cmd->cmd_end - cmd->cmd_start + 1;
}

int	main(int argc, char *argv[], char *envp[])
{
	int			pipe_in;
	int			pipe_out;
	t_command	command;
	const char	*infile = argv[1];
	const char	*outfile = argv[argc - 1];

	// if (!parse_bonus(argc, argv))
	// 	return (1);  // なにか出力させよう
	cmd_init(&command, argc, argv);
	if (!do_redirection(&pipe_in, &pipe_out, infile, outfile))
		return (1);
	execute_pipeline(command, envp, pipe_in, pipe_out);
}
