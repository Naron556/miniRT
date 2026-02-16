/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yamohamm <yasnaadli21@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/12 16:38:02 by yamohamm          #+#    #+#             */
/*   Updated: 2026/02/09 09:36:48 by yamohamm         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*gnl_nextline(char *s)
{
	int		i;
	char	*ret;
	int		len;
	int		j;

	if (!s)
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n')
		i++;
	if (s[i] == '\0')
		return (free(s), NULL);
	len = gnl_strlen(s) - i;
	ret = malloc(len + 1);
	if (!ret)
		return (free(s), NULL);
	i++;
	j = 0;
	while (s[i])
		ret[j++] = s[i++];
	ret[j] = '\0';
	return (free(s), ret);
}

static int	check(char *s)
{
	int	i;

	if (!s)
		return (0);
	i = 0;
	while (s[i])
	{
		if (s[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

static char	*gnl_read(char *s, char *buffer, int fd)
{
	int	readed;

	readed = 1;
	while (readed > 0)
	{
		readed = read(fd, buffer, BUFFER_SIZE);
		if (readed <= 0)
			break ;
		buffer[readed] = '\0';
		s = gnl_join(s, buffer);
		if (!s)
			return (free(buffer), NULL);
		if (check(s))
			break ;
	}
	return (s);
}

char	*get_next_line(int fd)
{
	static char	*s;
	char		*buffer;

	if (BUFFER_SIZE <= 0 || read(fd, NULL, 0) < 0)
		return (free(s), s = NULL);
	buffer = malloc(BUFFER_SIZE + 1 * sizeof(char));
	if (!buffer)
		return (free(s), NULL);
	s = gnl_read(s, buffer, fd);
	free(buffer);
	buffer = s;
	buffer = gnl_sub(buffer);
	s = gnl_nextline(s);
	return (buffer);
}

// int main(void)
// {
// 	int fd;
// 	char *next_line;
// 	int count;
// 	fd = open("1char.txt", O_RDONLY);
// 	count = 0;
// 	while ((next_line = get_next_line(fd)))
// 	{
// 		count++;
// 		printf("[%d]:%s", count, next_line);
// 		free(next_line);
// 	}
// 	close(fd);
// 	return (0);
// }