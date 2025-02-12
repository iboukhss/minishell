/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/04 19:28:34 by dheck             #+#    #+#             */
/*   Updated: 2024/06/04 19:28:37 by dheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	strlen;
	char	*substr;

	i = 0;
	strlen = ft_strlen(s);
	if (!s)
		return (NULL);
	if (strlen < start)
		return (ft_strdup("\0"));
	if (strlen - start < len)
		len = strlen - start;
	substr = malloc(sizeof(char) * (len + 1));
	if (substr == NULL)
		return (NULL);
	while ((i < len) && s[start] != '\0')
	{
		substr[i] = s[start];
		i++;
		start++;
	}
	substr[len] = '\0';
	return (substr);
}

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	if (!s)
		return (0);
	while (s[len] != '\0')
	{
		len++;
	}
	return (len);
}

char	*ft_strdup(const char *s)
{
	char	*new_s;
	size_t	i;
	size_t	strlen;

	i = 0;
	strlen = ft_strlen(s);
	new_s = malloc(sizeof(char) * (strlen + 1));
	if (new_s == NULL)
		return (NULL);
	while (s[i] != '\0')
	{
		new_s[i] = s[i];
		i++;
	}
	new_s[i] = '\0';
	return (new_s);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*strjoin;
	size_t	total_len;
	size_t	len1;

	len1 = ft_strlen(s1);
	total_len = len1 + ft_strlen(s2) + 1;
	strjoin = malloc(sizeof(char) * (total_len));
	if (strjoin == NULL)
		return (NULL);
	ft_strappend(strjoin, s1, 0);
	ft_strappend(strjoin, s2, len1);
	strjoin[total_len - 1] = '\0';
	return (strjoin);
}

void	ft_strappend(char *str, const char *append, size_t pos)
{
	size_t	i;

	i = 0;
	while (append[i] != '\0')
	{
		str[pos] = append[i];
		i++;
		pos++;
	}
}
