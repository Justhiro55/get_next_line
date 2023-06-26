/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/22 16:53:24 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/06/26 18:29:22 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

char	*rememo(char *memo)
{
	size_t	i;
	size_t	j;

	i = 0;
	j = 0;
	while (memo[i] != '\n' && memo[i] != '\0')
		i++;
	if (memo[i] == '\0')
	{
		free(memo);
		return (NULL);
	}
	if (memo[i] == '\n')
		i++;
	while (memo[i] != '\0')
	{
		memo[j] = memo[i];
		j++;
		i++;
	}
	memo[j] = '\0';
	return (memo);
}

char	*get_ans(char *memo)
{
	size_t	i;
	size_t	j;
	char	*ans;

	i = 0;
	j = 0;
	if (memo[0] == '\0')
		printf("aaaaaaamemo[0]:%c", memo[0]);
	if (!memo[i])
		return (NULL);
	while (memo[i] != '\n' && memo[i] != '\0')
		i++;
	ans = (char *)malloc((i + 2) * sizeof(char));
	if (ans == NULL)
		return (NULL);
	if (memo[0] == '\n')
	{
		ans[0] = '\n';
		ans[1] = '\0';
		return (ans);
	}
	while (j < i && memo[j] && memo[j] != '\n')
	{
		ans[j] = memo[j];
		j++;
	}
	if (memo[j] && memo[i] == '\n')
	{
		ans[j] = '\n';
		j++;
	}
	ans[j] = '\0';
	return (ans);
}

char	*get_memo(int fd, char *memo)
{
	char	*buf;
	ssize_t	done;

	done = 1;
	buf = (char *)malloc((BUFFER_SIZE + 2) * sizeof(char));
	if (buf == NULL)
		return (NULL);
	while (done > 0 && ft_strchr(memo, '\n') == 0)
	{
		done = read(fd, buf, BUFFER_SIZE);
		printf("buf[0]%c", buf[0]);
		if (done == -1 || buf[0] == '\0')
		{
			free(buf);
			free(memo);
			return (NULL);
		}
		if (buf[0] == '\0')
			printf("fffffffff\n");
		else
			printf("buf[0]%c", buf[0]);
		buf[done] = '\0';
		if (buf[0] == '\0')
			printf("eeeeeeee\n");
		memo = my_strjoin(memo, buf);
	}
	free(buf);
	buf = NULL;
	return (memo);
}

char	*get_next_line(int fd)
{
	static char	*memo[OPEN_MAX];
	char		*ans;

	if (BUFFER_SIZE <= 0 || fd < 0 || read(fd, 0, 0) < 0)
		return (NULL);
	if (memo[fd] == NULL)
		memo[fd] = (char *)malloc(sizeof(char));
	if (memo[fd] == NULL)
		return (NULL);
	memo[fd] = get_memo(fd, memo[fd]);
	if (memo[0] == NULL)
		printf("bbbbbb\n");
	if (memo[fd] == NULL)
		return (NULL);
	ans = get_ans(memo[fd]);
	printf("ans:%s\n", ans);
	memo[fd] = rememo(memo[fd]);
	return (ans);
}
