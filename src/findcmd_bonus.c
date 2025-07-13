/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   findcmd_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 19:03:49 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/13 23:59:01 by kaisuzuk         ###   ########.fr       */
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

// 権限がなくてもそもまま返す
// 権限エラーはエラーハンドリングで行う
// toctouの原則をちょっと調べてみようね

static char	*check_absolute_program(char *arg)
{
	if (access(arg, F_OK))
		return (NULL);
	// if (access(arg, X_OK))
	// {
	// 	ft_dprintf(STDERR_FILENO, "pipex: permission denied: %s\n", arg);
	// 	return (NULL);
	// }
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

// 実行権限がなかったのか、ファイルが存在しなかったのかがわからないね
// ビットフラグ使ってみるか
// 全体的にt_bool型依頼可能性出てきたな
static int	file_status(char *full_path)
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

static char *savestring(char *str)
{
	char *res;

	res = ft_strdup(str);
	if (!res)
	{
		sys_error("cannot malloc")
		exit(1);
	}
	return (res);
}

// 実行権限がない場合は、次のパスを調べるが、実行権限がなかったものも保持しておかないといけない
static char	*find_user_command_in_path(char *arg, char **path_list, char *file_to_lose_on)
{
	char	*full_path;
	int		i;

	i = 0;
	while (path_list[i])
	{
		full_path = join_path_element(path_list[i], arg);
		if (!full_path)
		{
			sys_error("cannot malloc");
			exit(1);
		}
		if (file_status(full_path))
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

// 対処不可なエラーはその場で落とす
// nullのケース -> 絶対パスのアクセス権限とコマンドがなかったとき
// -> アクセス権限がなかった場合は最初のパスのアクセス権限がなかったものをreturnする
// nullで帰るのはファイルがなかったときのみに絞る
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
	return (NULL);
}