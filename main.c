/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/28 21:30:22 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/31 19:15:26 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	print_usage(char *argv)
{
	ft_dprintf(STDERR_FILENO, "Usage: %s infile \"cmd1\" \"cmd2\"  outfile\n", \
		argv);
}

t_bool	args_check_mandatory(int argc)
{
	if (argc != 5)
		return (FALSE);
	return (TRUE);
}

int	main(int argc, char *argv[], char *envp[])
{
	t_command	*cmd;
	int			res;

	if (!args_check_mandatory(argc))
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
