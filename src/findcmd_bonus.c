/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findcmd_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:03:49 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/25 00:09:33 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// findcmd_utils_bonus.c
t_bool			is_absolute_program(char *arg);
void			free_path(char **path);
char			*savestring(char *str);

static char	*savestring_absolute_program(t_command *cmd)
{
	char	*arg;

	arg = savestring(cmd->cmdv[0]);
	if (!arg)
	{
		dispose_command(cmd);
		sys_error(MALLOC_STR);
		exit(EXECUTION_FAILURE);
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

static t_bool	file_status(char *full_path, char *file_to_lose_on,
		t_command *cmd)
{
	if (!access(full_path, F_OK))
	{
		if (!access(full_path, X_OK))
			return (TRUE);
		else
		{
			file_to_lose_on = savestring(full_path);
			if (!file_to_lose_on)
			{
				dispose_command(cmd->head);
				sys_error(MALLOC_STR);
				exit(EXECUTION_FAILURE);
			}
			return (FALSE);
		}
	}
	return (FALSE);
}

static char	*find_user_command_in_path(t_command *cmd, char **path_list,
		char *file_to_lose_on)
{
	char	*full_path;
	int		i;

	i = 0;
	while (path_list[i])
	{
		full_path = join_path_element(path_list[i], cmd->cmdv[0]);
		if (!full_path)
		{
			dispose_command(cmd->head);
			sys_error(MALLOC_STR);
			free(path_list);
			exit(EXECUTION_FAILURE);
		}
		if (file_status(full_path, file_to_lose_on, cmd))
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

char	*search_for_command(t_command *cmd, char *envp[])
{
	char	**path_list;
	char	*path;
	char	*full_path;
	char	*file_to_lose_on;

	if (is_absolute_program(cmd->cmdv[0]))
		return (savestring_absolute_program(cmd));
	path = find_variable_tempenv(envp, "PATH");
	if (!path)
		return (cmd->cmdv[0]);
	path_list = ft_split(path, ':');
	if (!path_list)
	{
		dispose_command(cmd->head);
		sys_error(MALLOC_STR);
		exit(EXECUTION_FAILURE);
	}
	file_to_lose_on = NULL;
	full_path = find_user_command_in_path(cmd, path_list, file_to_lose_on);
	free_path(path_list);
	if (full_path)
		return (free(file_to_lose_on), full_path);
	if (file_to_lose_on)
		return (file_to_lose_on);
	return (NULL);
}
