/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findcmd_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:03:49 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/06 14:12:19 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	free_path(char **path)
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

static int	absolute_program(char *arg)
{
	return (ft_strchr(arg, '/') != NULL);
}

static char	*check_absolute_program(char *arg)
{
	if (access(arg, F_OK))
	{
		ft_dprintf(stderr_fd, "pipex: command not found\n");
		return (NULL);
	}
	if (access(arg, X_OK))
	{
		ft_dprintf(stderr_fd, "pipex: permission denied: %s\n", arg);
		return (NULL);
	}
	return (arg);
}

static char	*join_path_element(char *dir, char *arg)
{
	char	*full_path;
	char	*tmp;

	tmp = ft_strjoin(dir, "/");
	if (!tmp)
		return (NULL);
	full_path = ft_strjoin(tmp, arg);
	free(tmp);
	if (!full_path)
		return (NULL);
	return (full_path);
}

static char	*get_path_line(char *envp[])
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

t_bool	executable_file(char *full_path)
{
	if (!access(full_path, F_OK))
	{
		if (!access(full_path, X_OK))
			return (TRUE);
		else
			return (FALSE);
	}
	return (FALSE);
}

static char *find_user_command_in_path(char *arg, char *envp[],
		const char **path)
{
	char *full_path;
	int	i;

	i = 0;
	while (path[i])
	{
		full_path = join_path_element(path[i], arg);
		if (!full_path)
		{
			ft_dprintf(stderr_fd, "pipex: cannot malloc\n")
			break;
		}
		if (executable_file(full_path))
			break ;
		else
		{
			free(full_path);
			full_path = NULL;
		}
		i++;
	}
	return (full_path);
}

char	*search_for_command(char *arg, char *envp[])
{
	const char **path = ft_split(get_path_line(envp), ':');
	int i;
	char *full_path;

	if (absolute_program(arg))
		return (check_absolute_program(arg));
	if (!path)
		return (ft_dprintf(stderr_fd, "%s: cannot malloc\n", arg), NULL);
	i = 0;
	full_path = find_user_command_in_path(arg, envp, path);
	free_path(path);
	if (full_path)
		return (full_path);
	ft_dprintf(stderr_fd, "%s: command not found", arg);
	return (NULL);
}