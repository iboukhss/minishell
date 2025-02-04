/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vasprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:11:04 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/04 16:14:56 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <stdlib.h>

/*
 * ft_vsnprintf can actually return -1 on format specifier error, maybe this
 * is unnecessary.
 */
int	ft_vasprintf(char **strp, const char *fmt, va_list ap)
{
	va_list	ap2;
	int		len;

	va_copy(ap2, ap);
	len = ft_vsnprintf(NULL, 0, fmt, ap2);
	va_end(ap2);
	*strp = malloc((len + 1) * sizeof(**strp));
	if (*strp == NULL)
	{
		return (-1);
	}
	return (ft_vsnprintf(*strp, len + 1, fmt, ap));
}
