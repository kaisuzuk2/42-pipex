/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/01 13:45:31 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/09 22:41:33 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_bool	check_args(int argc)
{
	if (argc < 5)
		return (FALSE);
	return (TRUE);
}

t_bool	is_here_doc(char *cmd)
{
	return (ft_strcmp(cmd, "here_doc") == 0);
}

t_command	*parse(int argc, char **argv)
{
	int			cmd_num;
	t_bool		here_doc;
	int			i;
	t_command	*cmd_head;
	t_command	*cmd;
	int			start;

	if (!check_args(argc))
		return (NULL); // 注意ね
	here_doc = is_here_doc(argv[1]);
	cmd_num = argc - 3;
	start = 2;
	if (here_doc)
	{
		start++;
		cmd_num--;
	}
	i = start;
	cmd_head = NULL;
	while (i < (start + cmd_num))
	{
		if (!cmd_head)
		{
			cmd_head = cmdlstnew(argv[0], argv[i]);
			if (!cmd_head)
				return (NULL);
			if (here_doc)
			{
				if (!set_redirect(cmd_head, e_reading_until, argv[i - 1], NULL))
					return (NULL);
			}
			else
			{
				if (!set_redirect(cmd_head, e_input_direction, NULL, argv[i - 1]))
					return (NULL);
			}
		}
		else
		{
			cmd = cmdlstnew(argv[0], argv[i]);
			if (!cmd)
				return (NULL);
			if (i == (start + cmd_num) - 1)
			{
				if (!set_redirect(cmd, e_output_direction, NULL, argv[i + 1]))
					return (NULL);
			}
			else
				cmd->redirect = NULL;
			cmdlst_add_back(cmd_head, cmd);
		}
		i++;
	}
	return (cmd_head);
}
