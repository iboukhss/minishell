/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_xasprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/04 12:11:21 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/04 12:29:14 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_xasprintf(const char *fmt, ...)
{
	va_list	ap;
	char	*str;

	va_start(ap, fmt);
	str = ft_xvasprintf(fmt, ap);
	va_end(ap);
	return (str);
}
