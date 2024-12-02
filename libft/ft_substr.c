/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:58:32 by dheck             #+#    #+#             */
/*   Updated: 2024/12/01 18:59:02 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	strlen;
	char	*substr;

	i = 0;
	if (!s)
		return (NULL);
	strlen = ft_strlen(s);
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
