/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dheck <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/05 15:19:02 by dheck             #+#    #+#             */
/*   Updated: 2024/03/12 13:38:46 by dheck            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	const char	*p_s;

	p_s = s;
	if (c < 0 || c > 255)
		return ((char *) s);
	while (*p_s != '\0')
	{
		if (*p_s == c)
			return ((char *)p_s);
		p_s++;
	}
	if (c == '\0')
		return ((char *)p_s);
	return (NULL);
}
