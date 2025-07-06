/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:08:48 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/05 23:49:26 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf.h"
# include <fcntl.h>
# include <stdio.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef int	t_bool;
# define TRUE 1
# define FALSE 0

# define stderr_fd 2

typedef struct s_command
{
	char	*prog_name;
	char	**cmdv;
	int		cmd_start;
	int		cmd_end;
	int		cmd_size;
}			t_command;

typedef struct s_pipefd
{
	int pipe_in;
	int pipe_out;
} t_pipefd;

// utils_bonus.c
t_bool		is_builtin(char *cmd);

char		**make_command(char *arg);
char		*search_for_command(char *arg, char *envp[]);

#endif