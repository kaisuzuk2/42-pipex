/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/29 16:08:48 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/02 13:48:07 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include "ft_printf.h"
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>
#include <stdio.h>

typedef int	t_bool;
# define TRUE 1
# define FALSE 0

// utils_bonus.c
char		**make_command(char *arg);
char		*search_for_command(char *arg, char *envp[]);

#endif