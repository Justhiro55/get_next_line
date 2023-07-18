/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hhagiwar <hhagiwar@student.42Tokyo.jp>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/17 16:29:17 by hhagiwar          #+#    #+#             */
/*   Updated: 2023/06/28 20:13:10 by hhagiwar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if (*s == '\0' && c == '\0')
		return ((char *)s);
	return (0);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (s == NULL)
		return (len);
	while (s[len] != '\0')
		len++;
	return (len);
}

char	*ft_free(char **str)
{
	free(*str);
	*str = NULL;
	return (NULL);
}

char	*my_strjoin(char *s1, char const *s2)
{
	int		i;
	int		j;
	char	*str;

	i = 0;
	j = 0;
	str = (char *)malloc((ft_strlen((char *)s1) + ft_strlen((char *)s2) + 2));
	if (str == NULL)
		return (ft_free(&s1));
	while (s1 != NULL && s1[i] != '\0')
	{
		str[i] = s1[i];
		i++;
	}
	while (s2[j] != '\0')
	{
		str[i + j] = s2[j];
		j++;
	}
	str[i + j] = '\0';
	free(s1);
	s1 = NULL;
	return (str);
}
