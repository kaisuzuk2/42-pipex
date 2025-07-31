/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmdlst_utils_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:05:19 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/31 19:16:52 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

// malloc error		:	NULL
// success			:	char *
char	*string_quote_removal(char *string)
{
	char	set[2];
	char	quote;

	set[1] = '\0';
	quote = 0;
	if (ft_strchr(string, '\''))
		quote = '\'';
	else if (ft_strchr(string, '\"'))
		quote = '\"';
	if (quote == 0)
		return (ft_strdup(string));
	set[0] = quote;
	return (ft_strtrim(string, set));
}

int	make_redirection(enum e_instruction inst)
{
	if (inst == e_input_direction)
		return (O_RDONLY);
	else if (inst == e_output_direction)
		return (O_TRUNC | O_WRONLY | O_CREAT);
	else if (inst == e_appending_to)
		return (O_APPEND | O_WRONLY | O_CREAT);
	else
		return (0);
}
