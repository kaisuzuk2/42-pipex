/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:11:09 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/09 22:59:55 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include <stdio.h>

// int	main(int argc, char *argv[], char *envp[])
// {
// 	int			pipe_in;
// 	int			pipe_out;
// 	t_command	command;
// 	const char	*infile = argv[1];
// 	const char	*outfile = argv[argc - 1];

// 	// if (!parse_bonus(argc, argv))
// 	// 	return (1);  // なにか出力させよう
// 	cmd_init(&command, argc, argv);
// 	if (!do_redirection(&pipe_in, &pipe_out, infile, outfile))
// 		return (1);
// 	execute_pipeline(command, envp, pipe_in, pipe_out);
// }


int main(int argc, char *argv[], char *envp[])
{
	t_command *cmd;
	int res;
	
	cmd = parse(argc, argv);
	if (!cmd)
		return (1); // エラー処理しようね
	res = execute_pipeline(cmd, envp);
	dispose_command(cmd);
	return (res);
}