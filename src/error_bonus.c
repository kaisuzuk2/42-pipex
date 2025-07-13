/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/12 14:12:44 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/13 16:10:28 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"


// error for system call function
void sys_error(char *err_txt)
{
	int e;

	e = errno;
	// ft_dprintf(STDERR_FILENO, "%s", prog_name);
	ft_dprintf(STDERR_FILENO, "%s", err_txt);
	ft_dprintf(STDERR_FILENO, ": %s\n", strerror(e));
}

// error for internal function
void internal_error(char *prog_name, char *text, char *errno_text)
{
	ft_dprintf(STDERR_FILENO, "%s", prog_name);
	ft_dprintf(STDERR_FILENO, ": %s", errno_text);
	ft_dprintf(STDERR_FILENO, ": %s", text);
}