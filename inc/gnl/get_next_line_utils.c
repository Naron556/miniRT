/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamohamm <yasnaadli21@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:39:39 by yamohamm          #+#    #+#             */
/*   Updated: 2026/02/09 09:29:13 by yamohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*gnl_join(char *s1, char *s2)
{
	int		len;
	char	*ret;
	int		j;
	int		i;

	if (!s1 && !s2)
		return (NULL);
	else if (!s1 && s2)
		return (gnl_strdup(s2));
	else if (!s2 && s1)
		return (gnl_strdup(s1));
	len = gnl_strlen(s1) + gnl_strlen(s2);
	ret = malloc(len + 1);
	if (!ret)
		return (free (s1), NULL);
	i = -1;
	while (s1[++i])
		ret[i] = s1[i];
	j = 0;
	while (s2[j])
		ret[i++] = s2[j++];
	ret[i] = '\0';
	return (free(s1), ret);
}

int	gnl_strlen(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*gnl_sub_helper(char *s, char *ret, int line, int i)
{
	int	j;

	j = 0;
	while (j < i)
	{
		ret[j] = s[j];
		j++;
	}
	if (line)
	{
		ret[i] = '\n';
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*gnl_strdup(char *s)
{
	char	*ret;
	int		i;

	if (!s)
		return (NULL);
	ret = malloc(gnl_strlen(s) + 1);
	if (!ret)
		return (NULL);
	i = -1;
	while (s[++i])
		ret[i] = s[i];
	ret[i] = '\0';
	return (ret);
}

char	*gnl_sub(char *s)
{
	char	*ret;
	int		i;
	int		new_line;
	int		j;

	if (!s || !*s)
		return (NULL);
	i = 0;
	j = 1;
	new_line = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\n')
	{
		new_line = 1;
		j = 2;
	}
	ret = malloc(i + j);
	if (!ret)
		return (NULL);
	return (gnl_sub_helper(s, ret, new_line, i));
}
