/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findcmd_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:03:49 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/15 20:02:12 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// findcmd_utils_bonus.c
int			absolute_program(char *arg);
void		free_path(char **path);
char		*get_path_line(char *envp[]);
char		*savestring(char *str);

static char	*check_absolute_program(char *arg)
{
	if (access(arg, F_OK))
		return (NULL);
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

static int	file_status(char *full_path, char *file_to_lose_on)
{
	if (!access(full_path, F_OK))
	{
		if (!access(full_path, X_OK))
			return (TRUE);
		else
		{
			if (!file_to_lose_on)
				savestring(file_to_lose_on);
			return (FALSE);
		}
	}
	return (FALSE);
}

static char	*find_user_command_in_path(char *arg, char **path_list,
		char *file_to_lose_on)
{
	char	*full_path;
	int		i;

	i = 0;
	while (path_list[i])
	{
		full_path = join_path_element(path_list[i], arg);
		if (!full_path)
		{
			sys_error("cannnot malloc");
			free(path_list);
			exit(EXECUTION_FAILURE);
		}
		if (file_status(full_path, file_to_lose_on))
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

char	*search_for_command(char *prog_name, char *arg, char *envp[])
{
	char **path_list;
	int i;
	char *full_path;
	char *file_to_lose_on;

	if (absolute_program(arg))
		return (check_absolute_program(arg));
	path = ft_split(get_path_line(envp), ':');
	if (!path)
	{
		sys_error("cannot malloc");
		exit(1);
	}
	i = 0;
	file_to_lose_on = NULL;
	full_path = find_user_command_in_path(arg, path_list, file_to_lose_on);
	free_path(path);
	if (full_path)
		return (full_path);
	if (file_to_lose_on)
		return (file_to_lose_on);
	return (NULL);
}