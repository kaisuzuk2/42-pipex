/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_split_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kaisuzuk <kaisuzuk@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/23 15:16:42 by kaisuzuk          #+#    #+#             */
/*   Updated: 2025/07/23 22:56:01 by kaisuzuk         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#define TRIM_WORD_SIZE 4

int	count_remove_char(char const *s, char const *set)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (ft_strchr(set, *s))
			count++;
		s++;
	}
	return (count);
}

char	*ft_strtrim_all(char const *s1, char const *set)
{
	const int	size = (ft_strlen(s1) - count_remove_char(s1, set)) + 1;
	char		*res;
	int			i;

	res = (char *)malloc(sizeof(char) * size);
	if (!res)
		return (NULL);
	i = 0;
	while (*s1)
	{
		if (!ft_strchr(set, *s1))
			res[i++] = *s1;
		s1++;
	}
	res[i] = '\0';
	return (res);
}

char	*get_trim_string(char *str)
{
	char	*trimw;

	trimw = ft_calloc(sizeof(char), TRIM_WORD_SIZE);
	if (ft_strchr(str, '\''))
		ft_strlcat(trimw, "\'", TRIM_WORD_SIZE);
	if (ft_strchr(str, '\"'))
		ft_strlcat(trimw, "\"", TRIM_WORD_SIZE);
	if (ft_strchr(str, '\\'))
		ft_strlcat(str, "\\", TRIM_WORD_SIZE);
	return (trimw);
}
