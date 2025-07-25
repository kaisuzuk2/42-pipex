/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:11:09 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/22 23:21:40 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_usage(char *argv)
{
	ft_dprintf(STDERR_FILENO, "Usage: \
%s infile \"cmd1\" \"cmd2\" ... outfile\n",
		argv);
	ft_dprintf(STDERR_FILENO, "Usage: \
%s here_doc  LIMITER \"cmd1\" \"cmd2\"... outfile\n", argv);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_command	*cmd;
	int			res;

	if (!args_check(argc, argv))
	{
		print_usage(argv[0]);
		return (EXECUTION_FAILURE);
	}
	cmd = parse(argc, argv);
	if (!cmd)
	{
		sys_error(MALLOC_STR);
		return (EXECUTION_FAILURE);
	}
	res = execute_pipeline(cmd, envp);
	dispose_command(cmd);
	return (res);
}
