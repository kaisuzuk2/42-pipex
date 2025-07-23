/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   make_cmd_utils_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 19:32:57 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/23 23:07:21 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static int	get_varlen(char *str)
{
	int	res;

	res = 0;
	while (*str)
	{
		if (!(ft_isalnum(*str)) && !(*str == '_'))
			break ;
		res++;
		str++;
	}
	return (res);
}

static char	*get_varvalue(char *doll_ptr, char **envp)
{
	char	*varname;
	char	*varvalue;

	varvalue = NULL;
	varname = ft_substr(doll_ptr + 1, 0, get_varlen(doll_ptr + 1));
	if (!varname)
		return (NULL);
	varvalue = find_variable_tempenv(envp, varname);
	free(varname);
	if (!varvalue)
		return ("");
	return (varvalue);
}

static char	*append_remainder(char *document, char *remainder)
{
	char	*res;

	if (!remainder)
		return (document);
	res = ft_strjoin(document, remainder);
	free(document);
	return (res);
}

static char	*join_string_until_varvalue(char *res, char **document)
{
	char	*doll_ptr;
	char	*tmp;
	char	*res_tmp;

	doll_ptr = ft_strchr(*document, '$');
	tmp = ft_substr(*document, 0, (doll_ptr - *document));
	if (!tmp)
		return (NULL);
	res_tmp = ft_strjoin(res, tmp);
	free(res);
	free(tmp);
	*document = doll_ptr + 1 + get_varlen(doll_ptr + 1);
	return (res_tmp);
}

char	*expand_string_to_string(char *document, char **envp)
{
	char	*res_tmp;
	char	*res;
	char	*varvalue;
	char	*document_ptr;

	res = ft_strdup("");
	if (!res)
		return (NULL);
	document_ptr = document;
	while (ft_strchr(document_ptr, '$'))
	{
		varvalue = get_varvalue(ft_strchr(document_ptr, '$'), envp);
		if (!varvalue)
			return (NULL);
		res = join_string_until_varvalue(res, &document_ptr);
		if (!res)
			return (NULL);
		res_tmp = ft_strjoin(res, varvalue);
		free(res);
		if (!res_tmp)
			return (NULL);
		res = res_tmp;
	}
	res = append_remainder(res, document_ptr);
	return (free(document), res);
}
