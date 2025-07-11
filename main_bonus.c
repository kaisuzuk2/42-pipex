/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:11:09 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/11 23:33:38 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_command *cmd;
	int res;

	if (!args_check(argc, argv))
	{
		ft_dprintf(STDERR_FILENO, "Usage: \
			%s infile \"cmd1\" \"cmd2\" ... outfile\n", argv[0]);
		ft_dprintf(STDERR_FILENO, "Usage: \
			%s here_doc  LIMITER \"cmd1\" \"cmd2\"... outfile\n",
			argv[0]);
		return (1);
	}
	cmd = parse(argc, argv);
	if (!cmd)
	{
		ft_dprintf(STDERR_FILENO, "%s: cannnot malloc\n", argv[0]);
		return (1);
	}
	res = execute_pipeline(cmd, envp);
	dispose_command(cmd);
	return (res);
}