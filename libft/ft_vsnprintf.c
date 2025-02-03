/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_vsnprintf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iboukhss <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 20:47:53 by iboukhss          #+#    #+#             */
/*   Updated: 2025/02/03 16:40:40 by iboukhss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

#include "printf_core.h"

/*
 * These functions can never fail, except when s is NULL and n is non-zero.
 * That is considered undefined behavior as per snprintf manual.
 */
static int	sn_flush(t_file *f)
{
	if (f->cap > 0)
	{
		f->data[f->len] = '\0';
	}
	return (0);
}

static int	sn_write(t_file *f, const void *src, int n)
{
	while (n > 0)
	{
		if (f->len < f->cap - 1)
		{
			f->data[f->len++] = *(const char *)src++;
		}
		f->count++;
		n--;
	}
	return (0);
}

/*
 * Maybe we should be more careful about size_t to int conversion?
 */
int	ft_vsnprintf(char *s, size_t n, const char *fmt, va_list ap)
{
	t_file	f;

	f.fd = -1;
	f.data = s;
	f.len = 0;
	f.cap = n;
	f.count = 0;
	f.write = sn_write;
	f.flush = sn_flush;
	return (printf_core(&f, fmt, ap));
}
