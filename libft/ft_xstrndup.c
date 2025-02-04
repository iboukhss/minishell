/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xstrndup.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 17:37:56 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/04 17:46:00 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_xstrndup(const char *s, size_t n)
{
	char	*dup;
	size_t	len;

	len = ft_strlen(s);
	if (n > len)
	{
		n = len;
	}
	dup = ft_xmalloc(n + 1);
	ft_memcpy(dup, s, n);
	dup[n] = '\0';
	return (dup);
}
