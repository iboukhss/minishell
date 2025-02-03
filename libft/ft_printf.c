/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/25 17:28:56 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/02 20:45:00 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include <unistd.h>

int	ft_printf(const char *fmt, ...)
{
	va_list	ap;
	int		ret;

	va_start(ap, fmt);
	ret = ft_vdprintf(STDOUT_FILENO, fmt, ap);
	va_end(ap);
	return (ret);
}

/*
#include <stdio.h>

int	main(void)
{
	int		ret;
	char	buf[80];

	ret = ft_printf("Hello, world!\n");
	printf("ret: %d\n", ret);
	puts("");
	ret = printf("Hello, world!\n");
	printf("ret: %d\n", ret);
	puts("");
	ret = ft_snprintf(buf, 80, "Hello, %s!\n", "world");
	printf("%s", buf);
	printf("ret: %d\n", ret);
	puts("");
	ret = snprintf(buf, 80, "Hello, %s!\n", "world");
	printf("%s", buf);
	printf("ret: %d\n", ret);
	return (0);
}
*/
