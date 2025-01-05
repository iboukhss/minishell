/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 16:00:39 by dheck             #+#    #+#             */
/*   Updated: 2024/03/15 13:29:08 by dheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

static void		ft_strappend(char *str, const char *append, size_t pos);

char	*ft_strjoin(char const *s1, char const *s2)
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

static void	ft_strappend(char *str, const char *append, size_t pos)
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
