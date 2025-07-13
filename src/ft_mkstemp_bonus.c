/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_mkstemp_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/11 17:17:38 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/12 14:12:25 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static t_bool is_noexist(char *filename)
{
	const int res = access(filename, F_OK);
	if (res == 0)
		return (FALSE);
	return (TRUE);
}

int ft_mkstemp(char *template)
{
	int i;
	char *filename;
	char *addnum;

	i = 0;
	while (i < 100)
	{
		addnum = ft_itoa(i);
		filename = ft_strjoin(template, addnum);
		if (is_noexist(filename))
		{
			template = filename;
			return (open(filename, O_RDWR|O_CREAT|O_EXCL, 0600));
		} // なんでrdwrなんかよくわからん　書き込みだけでよくね？
		free(addnum);
		free(filename);
		i++;			
	}
	free(template);
	template = NULL;
	return (-1);
}