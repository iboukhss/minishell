/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vdprintf.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 20:46:47 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/03 16:36:44 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "printf_core.h"

#include <unistd.h>

/*
 * We don't bother checking for partial writes.
 */
static int	fd_flush(t_file *f)
{
	if (write(f->fd, f->data, f->len) == -1)
	{
		return (-1);
	}
	f->len = 0;
	return (0);
}

static int	fd_write(t_file *f, const void *src, int n)
{
	while (n > 0)
	{
		if (f->len >= f->cap)
		{
			if (fd_flush(f) == -1)
			{
				return (-1);
			}
		}
		f->data[f->len++] = *(const char *)src++;
		f->count++;
		n--;
	}
	return (0);
}

/*
 * 80 characters is the standard terminal width.
 */
int	ft_vdprintf(int fd, const char *fmt, va_list ap)
{
	t_file	f;
	char	buf[80];

	f.fd = fd;
	f.data = buf;
	f.len = 0;
	f.cap = 80;
	f.count = 0;
	f.write = fd_write;
	f.flush = fd_flush;
	return (printf_core(&f, fmt, ap));
}
