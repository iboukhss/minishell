/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xvasprintf.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:27:21 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/04 12:34:09 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_xvasprintf(const char *fmt, va_list ap)
{
	va_list	ap2;
	int		len;
	char	*str;

	va_copy(ap2, ap);
	len = ft_vsnprintf(NULL, 0, fmt, ap2);
	va_end(ap2);
	str = ft_xmalloc((len + 1) * sizeof(*str));
	ft_vsnprintf(str, len + 1, fmt, ap);
	return (str);
}
