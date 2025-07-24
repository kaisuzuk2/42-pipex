/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findcmd_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/15 19:58:15 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/25 00:18:17 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_bool	is_absolute_program(char *arg)
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

// +1 envp -> NAME=
char	*find_variable_tempenv(char *envp[], char *name)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(envp[i], name, ft_strlen(name)) == 0)
			return (envp[i] + (ft_strlen(name) + 1));
		i++;
	}
	return (NULL);
}

char	*savestring(char *str)
{
	char	*res;

	res = ft_strdup(str);
	if (!res)
		return (NULL);
	return (res);
}
