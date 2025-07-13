/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:45:31 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/12 14:06:55 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_bool	is_here_doc(char *cmd)
{
	return (ft_strcmp(cmd, "here_doc") == 0);
}

t_bool	args_check(int argc, char **argv)
{
	if (argc < MIN_ARG)
		return (FALSE);
	if (is_here_doc(argv[1]) && argc < MIN_HEREDOC_ARG)
		return (FALSE);
	return (TRUE);
}

// eofかファイル名か受け取る
static t_command	*first_command(char *prog_name, char **cmdv, char *cmd, char *filename_eof)
{
	t_command *new_cmd;

	new_cmd = cmdnew(prog_name, cmd);
	if (!new_cmd)
		return (NULL);
	if (is_here_doc(cmdv[1]))
	{
		if (!set_redirect(new_cmd, e_reading_until,	filename_eof))
			return (NULL);
	}
	else
	{
		if (!set_redirect(new_cmd, e_input_direction, filename_eof))
			return (NULL);
	}
	return (new_cmd);
}

static t_command	*middle_command(char *prog_name, char *cmd)
{
	t_command *new_cmd;

	new_cmd = cmdnew(prog_name, cmd);
	if (!new_cmd)
		return (NULL);
	return (new_cmd);
	
}

static t_command	*last_command(char *prog_name, char *cmd, char *filename)
{
	t_command *new_cmd;

	new_cmd = cmdnew(prog_name, cmd);
	if (!new_cmd)
		return (NULL);
	if (!set_redirect(new_cmd, e_output_direction, filename))
		return (NULL);
	return (new_cmd);
	
}

t_command	*parse(int argc, char **argv)
{
	const int	end = argc - 1;
	int			i;
	t_command	*cmd_head;
	t_command	*cmd;

	i = 2;
	if (is_here_doc(argv[1]))
		i += 1;
	cmd_head = first_command(argv[0], argv, argv[i], argv[i - 1]);
	if (!cmd_head)
		return (NULL);
	i++;
	while (i < end)
	{
		if (i != (end - 1))
			cmd = middle_command(argv[0], argv[i]);
		else
			cmd = last_command(argv[0], argv[i], argv[i + 1]);
		if (!cmd)
			return (NULL);
		cmdlst_add_back(cmd_head, cmd);
		i++;
	}
	return (cmd_head);
}
