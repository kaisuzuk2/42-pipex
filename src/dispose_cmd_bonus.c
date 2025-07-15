/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dispose_cmd_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/09 22:50:59 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/16 00:29:13 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void dispose_cmdv(char **cmdv)
{
	int i;

	i = 0;
	while (cmdv[i])
	{
		free(cmdv[i]);
		i++;
	}
	free(cmdv);
}

static void dispose_redirect(t_redirect *redirect)
{
	t_redirect *cur;
	t_redirect *tmp;

	cur = redirect;
	while (cur)
	{
		tmp = cur->next;
		if (cur->document)
			free(cur->document);
		free(cur);
		cur = tmp;
	}
}

void dispose_command(t_command *command)
{
	t_command *cur;
	t_command *tmp;
	
	cur = command;	
	while (cur)
	{
		tmp = cur->next;
		dispose_redirect(cur->redirect);
		dispose_cmdv(cur->cmdv);
		free(cur);
		cur = tmp;
	}
}