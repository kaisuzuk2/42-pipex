/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findcmd_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 19:58:15 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/15 22:42:13 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

int	absolute_program(char *arg)
{
	return (ft_strchr(arg, '/') != NULL);
}

void	free_path(char **path)
{
	int	i;

	i = 0;
	while (path[i])
	{
		free(path[i]);
		i++;
	}
	free(path);
}

char	*get_path_line(char *envp[])
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
			return (envp[i] + 5);
		i++;
	}
	return (NULL);
}

char *savestring(char *str)
{
	char *res;

	res = ft_strdup(str);
	if (!res)
	{
		sys_error("cannot malloc");
		exit(EXECUTION_FAILURE);
	}
	return (res);
}